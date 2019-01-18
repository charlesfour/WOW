#coding=utf-8

'''
Build a tweet sentiment analyzer
'''
from collections import OrderedDict
import cPickle as pkl
import sys
import time

import gzip

import numpy
import theano
from theano import config
import theano.tensor as tensor
from theano.sandbox.rng_mrg import MRG_RandomStreams as RandomStreams

import imdb

datasets = {'imdb': (imdb.load_data, imdb.prepare_data)}

# Set the random number generators' seeds for consistency
SEED = 123
numpy.random.seed(SEED)

def numpy_floatX(data):
    return numpy.asarray(data, dtype=config.floatX)

#对所有句子，按照batch_size，划分出 (n//batch_size)+1个列表。
def get_minibatches_idx(n, minibatch_size, shuffle=False):
    """
    Used to shuffle the dataset at each iteration.
    """

    idx_list = numpy.arange(n, dtype="int32")

    if shuffle:
        numpy.random.shuffle(idx_list)

    minibatches = []
    minibatch_start = 0
    for i in range(n // minibatch_size):
        minibatches.append(idx_list[minibatch_start:
                                    minibatch_start + minibatch_size])
        minibatch_start += minibatch_size

    if (minibatch_start != n):
        # Make a minibatch out of what is left
        minibatches.append(idx_list[minibatch_start:])

    return zip(range(len(minibatches)), minibatches)


def get_dataset(name):
    return datasets[name][0], datasets[name][1]


def zipp(params, tparams):
    """
    When we reload the model. Needed for the GPU stuff.
    """
    for kk, vv in params.iteritems():
        tparams[kk].set_value(vv)


def unzip(zipped):
    """
    When we pickle the model. Needed for the GPU stuff.
    """
    new_params = OrderedDict()
    for kk, vv in zipped.iteritems():
        new_params[kk] = vv.get_value()
    return new_params

#50%的Dropout，开了之后千万不要加Weght_Decay，两种一叠加，惩罚太重了。  Dropout的实现，利用了Tensor.switch(Bool,Ture Operation,False Operation)来动态实现。
def dropout_layer(state_before, use_noise, trng):
    proj = tensor.switch(use_noise,
                         (state_before *
                          trng.binomial(state_before.shape,
                                        p=0.5, n=1,
                                        dtype=state_before.dtype)),
                         state_before * 0.5)
    return proj


def _p(pp, name):
    return '%s_%s' % (pp, name)

#这部分主要是初始化全部参数。分为两个部分：①初始化Embedding参数、Softmax输出层参数  ②初始化LSTM参数，在下面的 def param_init_lstm()函数中。  ①中参数莫名其妙使用了[0,0.01]的随机值初始化，不知道为什么不用负值。

#初始化词向量的空间 n_words(10000)*dim_proj(128) 和logistic regression 的参数U（dim_proj*ydim），b（ydim=2）.调用param_init_lstm，初始化了lstm相关的参数

def init_params(options):
    """
    Global (not LSTM) parameter. For the embeding and the classifier.
    """
    params = OrderedDict()  #OrderedDict是dict的子类，它记住了内容添加的顺序。
    # embedding
    randn = numpy.random.rand(options['n_words'],
                              options['dim_proj'])
    params['Wemb'] = (0.01 * randn).astype(config.floatX)
    params = get_layer(options['encoder'])[0](options,
                                              params,
                                              prefix=options['encoder'])
    # classifier
    params['U'] = 0.01 * numpy.random.randn(options['dim_proj'],
                                            options['ydim']).astype(config.floatX)   #正态分布随机数生成，参数为shape。本例中为2维矩阵128*2
    params['b'] = numpy.zeros((options['ydim'],)).astype(config.floatX)

    return params


def load_params(path, params):
    pp = numpy.load(path)
    for kk, vv in params.iteritems():
        if kk not in pp:
            raise Warning('%s is not in the archive' % kk)
        params[kk] = pp[kk]

    return params


#这个函数意义就是一键将Numpy标准的params全部转为Theano.shared标准。替代大量的Theano.shared(......).  启用tparams作为Model的正式params，而原来的params废弃。

def init_tparams(params):
    tparams = OrderedDict()
    for kk, pp in params.iteritems():
        tparams[kk] = theano.shared(params[kk], name=kk)
    return tparams


def get_layer(name):
    fns = layers[name]
    return fns


def ortho_weight(ndim):
    W = numpy.random.randn(ndim, ndim)
    u, s, v = numpy.linalg.svd(W)
    return u.astype(config.floatX)

#这部分用于初始化LSTM参数，W阵、U阵。四个shape相同的矩阵连接在一起。LSTM的初始化值很特殊，先用[0,1]随机数生成矩阵，然后对随机矩阵进行SVD奇异值分解。取正交基矩阵来初始化，即 ortho_weight，原理不明，没有找到相关文献

def param_init_lstm(options, params, prefix='lstm'):
    """
    Init the LSTM parameter:

    :see: init_params
    """
    W = numpy.concatenate([ortho_weight(options['dim_proj']),
                           ortho_weight(options['dim_proj']),
                           ortho_weight(options['dim_proj']),
                           ortho_weight(options['dim_proj'])], axis=1)
    params[_p(prefix, 'W')] = W
    U = numpy.concatenate([ortho_weight(options['dim_proj']),
                           ortho_weight(options['dim_proj']),
                           ortho_weight(options['dim_proj']),
                           ortho_weight(options['dim_proj'])], axis=1)
    params[_p(prefix, 'U')] = U
    b = numpy.zeros((4 * options['dim_proj'],))
    params[_p(prefix, 'b')] = b.astype(config.floatX)

    return params


#LSTM的计算核心。 首先得注意参数state_below，这是个3D矩阵，[n_Step，BatchSize，Emb_Dim]

def lstm_layer(tparams, state_below, options, prefix='lstm', mask=None):
    nsteps = state_below.shape[0]
    if state_below.ndim == 3:
        n_samples = state_below.shape[1]
    else:
        n_samples = 1

    assert mask is not None

    def _slice(_x, n, dim):
        if _x.ndim == 3:
            return _x[:, :, n * dim:(n + 1) * dim]
        return _x[:, n * dim:(n + 1) * dim]

    def _step(m_, x_, h_, c_):
        preact = tensor.dot(h_, tparams[_p(prefix, 'U')])   #注意前面U实际上是4个矩阵的连接，所以在此需要用切片分开
        preact += x_      #将前一时序h′h′与4倍化UU阵并行计算，并加上4倍化WxWx的预计算
        
        #分离计算，按照LSTM结构定义，分别计算InputGateInputGate、ForgetGateForgetGate、OutoutGateOutoutGate Cell~Cell~、CellCell、h

        i = tensor.nnet.sigmoid(_slice(preact, 0, options['dim_proj']))
        f = tensor.nnet.sigmoid(_slice(preact, 1, options['dim_proj']))
        o = tensor.nnet.sigmoid(_slice(preact, 2, options['dim_proj']))
        c = tensor.tanh(_slice(preact, 3, options['dim_proj']))

        c = f * c_ + i * c
        c = m_[:, None] * c + (1. - m_)[:, None] * c_   #每个句子长度是不同的，为了便于并行矩阵计算，必须选定最长句子，最大化矩阵。句子词较少的，用0填充。而在实际LSTM计算中，这个0填充则成了麻烦，因为你不能让标记为0的Padding参与递归网络计算，需要剔除。这时候就需要Mask矩阵。m_是mask矩阵.由于mask矩阵也在sequence中，所以m_被降成了1D，通过Numpy的第二维None扩充，可以和c（[batch_size,dim_proj])进行点乘(不是矩阵乘法)。
        
        
         #在step_函数中，c = m_[:, None] * c + (1. - m_)[:, None] * c_    该语句中 m_[:,None],slicing with None对array m_来说增加了一个维度，因为这里c是一个[dim_proj,batch] 的矩阵，而m_是一个向量（同一time step 不同batch sample的mask），m_[:,None]扩展到了[dim_proj,batch] 另外，这个递推公式，保证了当m_中为0时，第一项为0，c会一直保持前面时刻（句子的最后一个词）c的状态， 当m_中元素为1，c保持计算的结果不变。意思就是，对于长度小于maxlen的句子，会补零，但是在这些0位置处， memory cell的状态采用了句子的最后一个单词计算的状态memory cell c进行填充。

        h = o * tensor.tanh(c)
        h = m_[:, None] * h + (1. - m_)[:, None] * h_

        return h, c

    state_below = (tensor.dot(state_below, tparams[_p(prefix, 'W')]) +
                   tparams[_p(prefix, 'b')])

    dim_proj = options['dim_proj']
    
    #进入scan函数过程，每一个Step：I、将前一时序h′h′与4倍化UU阵并行计算，并加上4倍化WxWx的预计算  II、分离计算，按照LSTM结构定义，分别计算InputGateInputGate、ForgetGateForgetGate、OutoutGateOutoutGate Cell~Cell~、CellCell、h .  每个Step里，h结果是一个2D矩阵，[BatchSize，Emb_Dim]

   #scan函数的使用. scan的计算过程会将参数sequences中的矩阵，按照axis=0（第一维度，纵向）进行切片，每次只取一个 time step 的序列数据，即不同句子的相同位置（time step）的单词进行运算。序列维度为 [step,batch，dim_proj],具体的参考上面的流程图。关于theano中scan函数的详细用法，参考文末的链接。
   
    #scan函数的返回值有两个，第一个是_step的返回值（多个time step组成的），还有一个updates，updates的作用是来更新_step中返回的shared variable，但是_setp没有这样的变量返回，故这个东西在此处没有用处。
    
    #函数scan是Theano中迭代的一般形式，所以可以用于类似循环(looping)的场景。 scan在计算的时候，可以访问以前n步的输出结果，所以比较适合RNN网络。sequences就是需要迭代的序列（输入序列），它的值将会传给fn作为前面的参数。
    
    
    rval, updates = theano.scan(_step,
                                sequences=[mask, state_below],
                                outputs_info=[tensor.alloc(numpy_floatX(0.),
                                                           n_samples,
                                                           dim_proj),
                                              tensor.alloc(numpy_floatX(0.),
                                                           n_samples,
                                                           dim_proj)],
                                name=_p(prefix, '_layers'),
                                n_steps=nsteps)
    return rval[0]

#返回rval[0]，即h矩阵。注意，scan函数的输出结果会增加1D。 而rval[0]是一个3D矩阵，[n_Step，BatchSize，Emb_Dim]。后续会对第一维n_Step进行Mean Pooling，之后才能降解成用于Softmax的2D输入。


# ff: Feed Forward (normal neural net), only useful to put after lstm
#     before the classifier.
layers = {'lstm': (param_init_lstm, lstm_layer)}


#下面的三个函数是三个可选梯度更新算法。由于作者想要保持格式一致，所以AdaDelta和RMSProp写的有点啰嗦。官方代码里默认用的是AdaDelta，毕竟有Matthew D. Zeiler的论文详细推导与说明。AdaDelta和RMSProp都是模拟二阶梯度更新，所以可以和Learning Rate这个恶心的超参说Bye~Bye了。值得把玩。


def sgd(lr, tparams, grads, x, mask, y, cost):
    """ Stochastic Gradient Descent

    :note: A more complicated version of sgd then needed.  This is
        done like that for adadelta and rmsprop.

    """
    # New set of shared variable that will contain the gradient
    # for a mini-batch.
    gshared = [theano.shared(p.get_value() * 0., name='%s_grad' % k)
               for k, p in tparams.iteritems()]
    gsup = [(gs, g) for gs, g in zip(gshared, grads)]

    # Function that computes gradients for a mini-batch, but do not
    # updates the weights.
    f_grad_shared = theano.function([x, mask, y], cost, updates=gsup,
                                    name='sgd_f_grad_shared')

    pup = [(p, p - lr * g) for p, g in zip(tparams.values(), gshared)]

    # Function that updates the weights from the previously computed
    # gradient.
    f_update = theano.function([lr], [], updates=pup,
                               name='sgd_f_update')

    return f_grad_shared, f_update

#2010年Duchi et.al 则推出AdaGrad，自适应来调整学习率。

def adadelta(lr, tparams, grads, x, mask, y, cost):
    """
    An adaptive learning rate optimizer

    Parameters
    ----------
    lr : Theano SharedVariable
        Initial learning rate
    tpramas: Theano SharedVariable
        Model parameters
    grads: Theano variable
        Gradients of cost w.r.t to parameres
    x: Theano variable
        Model inputs
    mask: Theano variable
        Sequence mask
    y: Theano variable
        Targets
    cost: Theano variable
        Objective fucntion to minimize

    Notes
    -----
    For more information, see [ADADELTA]_.

    .. [ADADELTA] Matthew D. Zeiler, *ADADELTA: An Adaptive Learning
       Rate Method*, arXiv:1212.5701.
    """

    zipped_grads = [theano.shared(p.get_value() * numpy_floatX(0.),
                                  name='%s_grad' % k)
                    for k, p in tparams.iteritems()]
    running_up2 = [theano.shared(p.get_value() * numpy_floatX(0.),
                                 name='%s_rup2' % k)
                   for k, p in tparams.iteritems()]
    running_grads2 = [theano.shared(p.get_value() * numpy_floatX(0.),
                                    name='%s_rgrad2' % k)
                      for k, p in tparams.iteritems()]

    zgup = [(zg, g) for zg, g in zip(zipped_grads, grads)]
    rg2up = [(rg2, 0.95 * rg2 + 0.05 * (g ** 2))
             for rg2, g in zip(running_grads2, grads)]

    f_grad_shared = theano.function([x, mask, y], cost, updates=zgup + rg2up,
                                    name='adadelta_f_grad_shared')

    updir = [-tensor.sqrt(ru2 + 1e-6) / tensor.sqrt(rg2 + 1e-6) * zg
             for zg, ru2, rg2 in zip(zipped_grads,
                                     running_up2,
                                     running_grads2)]
    ru2up = [(ru2, 0.95 * ru2 + 0.05 * (ud ** 2))
             for ru2, ud in zip(running_up2, updir)]
    param_up = [(p, p + ud) for p, ud in zip(tparams.values(), updir)]

    f_update = theano.function([lr], [], updates=ru2up + param_up,
                               on_unused_input='ignore',
                               name='adadelta_f_update')

    return f_grad_shared, f_update


def rmsprop(lr, tparams, grads, x, mask, y, cost):
    """
    A variant of  SGD that scales the step size by running average of the
    recent step norms.

    Parameters
    ----------
    lr : Theano SharedVariable
        Initial learning rate
    tpramas: Theano SharedVariable
        Model parameters
    grads: Theano variable
        Gradients of cost w.r.t to parameres
    x: Theano variable
        Model inputs
    mask: Theano variable
        Sequence mask
    y: Theano variable
        Targets
    cost: Theano variable
        Objective fucntion to minimize

    Notes
    -----
    For more information, see [Hint2014]_.

    .. [Hint2014] Geoff Hinton, *Neural Networks for Machine Learning*,
       lecture 6a,
       http://cs.toronto.edu/~tijmen/csc321/slides/lecture_slides_lec6.pdf
    """

    zipped_grads = [theano.shared(p.get_value() * numpy_floatX(0.),
                                  name='%s_grad' % k)
                    for k, p in tparams.iteritems()]
    running_grads = [theano.shared(p.get_value() * numpy_floatX(0.),
                                   name='%s_rgrad' % k)
                     for k, p in tparams.iteritems()]
    running_grads2 = [theano.shared(p.get_value() * numpy_floatX(0.),
                                    name='%s_rgrad2' % k)
                      for k, p in tparams.iteritems()]

    zgup = [(zg, g) for zg, g in zip(zipped_grads, grads)]
    rgup = [(rg, 0.95 * rg + 0.05 * g) for rg, g in zip(running_grads, grads)]
    rg2up = [(rg2, 0.95 * rg2 + 0.05 * (g ** 2))
             for rg2, g in zip(running_grads2, grads)]

    f_grad_shared = theano.function([x, mask, y], cost,
                                    updates=zgup + rgup + rg2up,
                                    name='rmsprop_f_grad_shared')

    updir = [theano.shared(p.get_value() * numpy_floatX(0.),
                           name='%s_updir' % k)
             for k, p in tparams.iteritems()]
    updir_new = [(ud, 0.9 * ud - 1e-4 * zg / tensor.sqrt(rg2 - rg ** 2 + 1e-4))
                 for ud, zg, rg, rg2 in zip(updir, zipped_grads, running_grads,
                                            running_grads2)]
    param_up = [(p, p + udn[1])
                for p, udn in zip(tparams.values(), updir_new)]
    f_update = theano.function([lr], [], updates=updir_new + param_up,
                               on_unused_input='ignore',
                               name='rmsprop_f_update')

    return f_grad_shared, f_update


#该部分是联合LSTM和Softmax，构成完整Theano.function的重要部分。

'''
    该部分是联合LSTM和Softmax，构成完整Theano.function的重要部分。
    ①首先是定义几个Tensor量，xx、yy、maskmask。
    ②接着，从tparams['Wemb']中取出Words*Sentences数量的词向量，并且变形为3D矩阵。
    x.flatten()的使用非常巧妙，它将词矩阵拆成1D列表，然后按顺序取出词向量，然后再按顺序变形成3D形态。体现了Python和Numpy的强大之处。
    ③得到3D的输入state_below之后，配合mask，经过LSTM，得到一个3D的h矩阵proj。
    ④对3D的h矩阵，各个时序进行Mean Pooling，得到2D矩阵，有点像Dropout的平均网络。
    ⑤Dropout处理
    ⑥Softmax、构建prob、pred、cost，都是老面孔了。
    特别的是，这里有一个offset，防止prob爆0，造成log溢出。碰到这种情况可能不大。
    
    这个函数里面，难理解的应该就是一数据的一些转换。将索引的矩阵先通过flatten换成1D的向量，再转换
    成词向量矩阵2D，最后reshape成[step,batch,dim_proj]的3D矩阵。调用lstm_layer，得到proj，再通过mean
    pooling运算得到h矩阵。并求得网络的cost
    
'''

def build_model(tparams, options):
    trng = RandomStreams(SEED)

    # Used for dropout.
    use_noise = theano.shared(numpy_floatX(0.))

    x = tensor.matrix('x', dtype='int64')
    mask = tensor.matrix('mask', dtype=config.floatX)
    y = tensor.vector('y', dtype='int64')


    n_timesteps = x.shape[0]
    n_samples = x.shape[1]

    emb = tparams['Wemb'][x.flatten()].reshape([n_timesteps,
                                                n_samples,
                                                options['dim_proj']])
    proj = get_layer(options['encoder'])[1](tparams, emb, options,
                                            prefix=options['encoder'],
                                            mask=mask)
    if options['encoder'] == 'lstm':
        proj = (proj * mask[:, :, None]).sum(axis=0)
        proj = proj / mask.sum(axis=0)[:, None]
    if options['use_dropout']:
        proj = dropout_layer(proj, use_noise, trng)

    pred = tensor.nnet.softmax(tensor.dot(proj, tparams['U']) + tparams['b'])


    f_pred_prob = theano.function([x, mask], pred, name='f_pred_prob')
    f_pred = theano.function([x, mask], pred.argmax(axis=1), name='f_pred')

    
    off = 1e-8
    if pred.dtype == 'float16':
        off = 1e-6

    cost = -tensor.log(pred[tensor.arange(n_samples), y] + off).mean()


    return use_noise, x, mask, y, f_pred_prob, f_pred, cost

#用于预测一些新的example，输出预测结果为[n_sample,y_dim]的矩阵


def pred_probs(f_pred_prob, prepare_data, data, iterator, verbose=False):
    """ If you want to use a trained model, this is useful to compute
    the probabilities of new examples.
    """
    n_samples = len(data[0])
    probs = numpy.zeros((n_samples, 2)).astype(config.floatX)

    n_done = 0

    for _, valid_index in iterator:
        x, mask, y = prepare_data([data[0][t] for t in valid_index],
                                  numpy.array(data[1])[valid_index],
                                  maxlen=None)
        pred_probs = f_pred_prob(x, mask)
        probs[valid_index, :] = pred_probs

        n_done += len(valid_index)
        if verbose:
            print '%d/%d samples classified' % (n_done, n_samples)

    return probs


#计算误差，传入函数的地址作为参数，f_pred（预测的函数,输出结果为一个n_sample的向量）prepare_data ： 补零，加mask
################################################################################
def pred (input,f_pred,prepare_data):
    """
        Just compute the error
        f_pred: Theano fct computing the prediction
        prepare_data: usual prepare_data for that dataset.
        """
    #定义一个字符串
    temp="the food is good and excellent "
    list1=[]
    list1=input.split(' ')
    print list1
    print input.split(' ')

    
    
    #打开词典文件
    print "open dict....."
    path="imdb.dict.pkl"
    if path.endswith(".gz"):
        f = gzip.open(path, 'rb')
    else:
        f = open(path, 'rb')

    worddict = dict()
    worddict = pkl.load(f)
    #for (d,x) in worddict.items():
        #print "key:"+d+",value:"+str(x)
    f.close()


    list2=[] #保存当前上下文单词的id.
    for w in list1:
        if w in worddict and worddict[w]<10000:
            list2.append(worddict[w])
    print list2
    list3=[]
    list3.append(list2)
    list4=[1]

    x, mask, y = prepare_data(list3, list4, maxlen=None)

    print x # x是若干句子的词的id, 进行了转置处理
    print y

    preds = f_pred(x, mask) #预测x的类别
    print "predicting results.***************"
    print preds
    return preds[0]


##############################################################################

#计算误差，传入函数的地址作为参数，f_pred（预测的函数,输出结果为一个n_sample的向量）prepare_data ： 补零，加mask

def pred_error_backup(f_pred, prepare_data, data, iterator, verbose=False):
    """
    Just compute the error
    f_pred: Theano fct computing the prediction
    prepare_data: usual prepare_data for that dataset.
    """
   
    valid_err = 0
    
    for _, valid_index in iterator: #valid_index对应着一组共16个句子。对于每个句子，t是当前句子中的每个词，x和y分别表示当前句子向量及其类别. prepare_data将会转置处理
  
        
        x, mask, y = prepare_data([data[0][t] for t in valid_index],
                                  numpy.array(data[1])[valid_index],
                                  maxlen=None)
        print "one new example is..."
        print valid_index #
        print x # x是若干句子的词的id
        print y

        
        preds = f_pred(x, mask) #预测x的类别
        print "predicting results......................"
        print preds
        
        targets = numpy.array(data[1])[valid_index]  #当前句子的真实类别
        valid_err += (preds == targets).sum()
    
    valid_err = 1. - numpy_floatX(valid_err) / len(data[0])

    return valid_err



##$################################################


#训练过程。Theano代码块中最冗长、最臃肿的部分。

'''
    ①options=locals().copy()是python中的一个小trick。
    它能将函数中所有参数按爬虫下来，保存为一个词典，方便访问。
    ②load_data。定义在imdb.py中，获取train、vaild、test三个数据集
    让人费解的是，既然这里要对test做shuffle，又何必在load_data里把test排序呢？
    ③初始化params，并且build_model，返回theano.function的pred、prob、cost。
    ④WeightDecay。有Dropout之后，必要性不大。
    ⑤利用cost，得到grad。利用tparams、grad，得到theano.function的update。
    这里代码很啰嗦，如cost完全没有必要通过theano.function转化出来，保持Tensor状态是可以带入T.grad
    而前面就没有这么写。代码风格和前面的章节截然不同。
    至此，准备工作完毕，进入mini-batch执行阶段。
    
    ——————————————————————————————————————————————
    ①首先获取vaild和test的zip化minibatch。
    每轮zip返回一个二元组(batch_idx,batch_content_list)，idx实际并不用。
    list是指当前batch中所有句子的idx。然后，对这些离散的idx，拼出实际的1Dxx。
    经过imdb.py下的prepare_data，得到2D的xx，作为Word Embedding的预备输入。
    ②进入max_epochs循环阶段：
    包括early stopping优化，这部分与之前章节大致相同。
    
    这个函数train_lstm中设置了一些参数，例如
    1.隐含层的个数 dim_proj=128  #既是词向量的维度，又是LSTM中Hideden Units的个数
    2.优化方法     optimizer=adadelta
    还有一些其他的训练参数就不一一列举了
    
    options=locals().copy()，它将函数中所有参数复制，保存为一个词典
    利用build_lstm求得cost，再结合tparams，利用tensor.grad求得梯度（Theano这点真的很赞！）
    后面程序的结构，用f_grad_shared传出cost，再用f_update，更新网络。
    这两个函数（f_grad_shared，f_update）都是optimizer函数，即adadelta的输出。
    最后，就是一些很繁琐的数据检查，和利用early_stop训练等等。
'''

def train_lstm(input):

    dim_proj=128 # word embeding dimension and LSTM number of hidden units.
    patience=10  # Number of epoch to wait before early stop if no progress
    max_epochs=5000  # The maximum number of epoch to run
    dispFreq=10  # Display to stdout the training progress every N updates
    decay_c=0.  # Weight decay for the classifier applied to the U weights.
    lrate=0.0001  # Learning rate for sgd (not used for adadelta and rmsprop)
    n_words=10000  # Vocabulary size 如果输入中有超过10000的id的词，会报错。2017.8.22
    optimizer=adadelta  # sgd, adadelta and rmsprop available, sgd very hard to use, not recommanded (probably need momentum and decaying learning rate).
    encoder='lstm'  # TODO: can be removed must be lstm.
    saveto='lstm_model.npz'  # The best model will be saved there
    validFreq=370  # Compute the validation error after this number of update.
    saveFreq=1110  # Save the parameters after every saveFreq updates
    maxlen=100  # Sequence longer then this get ignored
    batch_size=16  # The batch size during training.
    valid_batch_size=64  # The batch size used for validation/test set.
    dataset='imdb'

    # Parameter for extra option
    noise_std=0.
    use_dropout=True  # if False slightly faster, but worst test error
                       # This frequently need a bigger model.
    reload_model=True  # Path to a saved model we want to start from.
    test_size=-1  # If >0, we keep only this number of test example.

    # Model options
    model_options = locals().copy()
    print "model options", model_options


#原始数据集被Bengio组封装过，链接 http://www.iro.umontreal.ca/~lisa/deep/data/imdb.pkl
#cPickle封装的格式如下：
#train_set[0]  ---->  一个包含所有句子的二重列表，列表的每个元素也为一个列表，内容为：
#[词索引1，词索引2，.....，词索引n]，构成一个句子。熟悉文本数据的应该很清楚。
#词索引之前建立了一个词库，实际使用的时候如果要对照索引，获取真实的词，则需要词库：~Link~
#train_set[0][n]指的是第n个句子。
#————————————————————————————————————————————
#train_set[1]  ---->  一个一重列表，每个元素为每个句子的情感标签，0/1。
#test_set格式相同。

    print "begin to get dataset..."
    load_data, prepare_data = get_dataset(dataset)



    ydim=5 #应该是标签的数量加1。这个地方未来可能需要修改
    model_options['ydim'] = ydim
    print "ydim"
    print ydim
    


    print 'Building model'
    # This create the initial parameters as numpy ndarrays.
    # Dict name (string) -> numpy ndarray
    params = init_params(model_options)

    if reload_model:
        print "begin to reload model...."
        load_params('lstm_model.npz', params)
        print "end reload model."

    # This create Theano Shared Variable from the parameters.
    # Dict name (string) -> Theano Tensor Shared Variable
    # params and tparams have different copy of the weights.
    tparams = init_tparams(params)

    # use_noise is for dropout
    (use_noise, x, mask,
     y, f_pred_prob, f_pred, cost) = build_model(tparams, model_options)
    print "build model ended."


    print "begin predicting context"
    result=pred(input,f_pred,prepare_data)

    print "end predict context and result is..."
    print result
    return result


if __name__ == '__main__':
    # See function train for all possible parameter and there definition.
    train_lstm(
        input="Our research is to investigate a machine learning approach in order to build an Indonesian Question Answering System. Based on our experiments result on the question classification task, we choose to use SVM as the machine learning algorithm. Similar with ordinary QA systems, we divide our system into three subcomponents: question classifier, passage retriever and answer finder. The SVM algorithm is employed in the question classifier and answer finder modules.  To overcome the language resource poorness problem of Indonesian language, we introduce a bi-gram frequency attribute extracted from a downloaded newspaper corpus. The comparison among attribute combination is shown in our question classifier experiment.  The West shows that the question shallow parser result attribute joined with bi-gram frequency attribute gives significant improvement compared to the baseline (bag of words). Our question classifier achieves 96% accuracy.  We also compare some attribute combinations in the answer finder module. We find that the join attribute between the expected answer type (EAT) and the attributes of the question classifier gives higher MRR score than using only the EAT attribute or only the attribute of the question classifiers. A machine learning approach for Indonesian question answering system"
		)