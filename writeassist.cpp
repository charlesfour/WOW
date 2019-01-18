#include "writeassist.h"
#include "stdafx.h"
#include<stdlib.h>
#include<map>
#include <set>
#include<vector>

#include <algorithm>
#include <windows.h>
#include <WINSOCK2.H>
#include <stdio.h>
#include <iostream> 
#include <fstream> 
#include <string>
using namespace std; 

 
bool extended=false;// whether use word2vec

ofstream outfile1("writeassist.txt",ios::app);
extern int wordslen;
extern	 int phraseslen;
extern   int phrases_6len;
extern   int  sentences_len;
extern	 std::vector < std::string> vec_sentence;
extern	vector < string>  words;//���ʿ�

extern	 vector < string> phrases;
extern	 vector < string> phrases_6;

extern	vector <string> vec_sentence;
extern	vector < vector < string > > vec_vec;
extern	vector < vector < string > > vec_vec_sentence;

extern string CStringToString(CString cstr);
extern std::vector<std::string> splitWithStl(const std::string &str,const std::string &pattern);

extern int compute(string str, vector<string> &vec_str,	vector<float> & vec_dis );

typedef pair<int, int> PAIR; 


extern const long long max_size = 2000;         // max length of strings
extern const long long N = 40;                  // number of closest words that will be shown
extern const long long max_w = 50;              // max length of vocabulary entries

extern char *vocab;
extern float *M;
extern long long wordsnumber;
extern long long size;


int compute(string str, vector<string> &vec_str, vector<float> & vec_dis ) {

	//for (int b = 0; b <wordsnumber; b++)  cout<<&vocab[b * max_w]<<endl;

  char *bestw[N];
  float  bestd[N];

  char st1[max_size];
 
  char st[100][max_size];
  float dist, len,  vec[max_size];	//dist: distance; len: norm of vector; bestd: best distance
  long long  a, b, c, d, cn, bi[100];
  char ch; 

  //��ʼ�������ƶ�/////////////////////////////////////////////////////////////////////////////////////////	  
	  
   for (a = 0; a < N; a++) bestw[a] = (char *)malloc(max_size * sizeof(char));	//memory alloc, store closest vocabs
  
    for (a = 0; a < N; a++) bestd[a] = 0;
    for (a = 0; a < N; a++) bestw[a][0] = 0;

    a = 0;

	strcpy(st1, str.c_str());
 
    cn = 0;
    b = 0;
    c = 0;
    while (1) {	//multiple wordsnumber separated by BLANK symbol
      st[cn][b] = st1[c];
      b++;
      c++;
      st[cn][b] = 0;	//assign '\0' after the wordsnumber, if new charactor found, this value can be replaced.
      if (st1[c] == 0) break;
      if (st1[c] == ' ') {
        cn++;
        b = 0;
        c++;
      }
    }
    cn++;
    for (a = 0; a < cn; a++) {	//check word position in vocab array.
      for (b = 0; b < wordsnumber; b++) if (!strcmp(&vocab[b * max_w], st[a])) break;	//found it, b store the position
      if (b == wordsnumber) b = -1;	//not found, b = -1
      bi[a] = b;							//position array, store all wordsnumber input this time
      printf("\nWord: %s  Position in vocabulary: %lld\n", st[a], bi[a]);
      if (b == -1) {
        printf("Out of dictionary word!\n");
        break;
      }
    }
	
	//�ҵ��ˣ�ÿ���ʵ�λ��Ҳ������
   // if (b == -1) continue;	//if not found, continue; otherwise, search for closest wordsnumber
    printf("\n                                              Word       Cosine distance\n------------------------------------------------------------------------\n");
    for (a = 0; a < size; a++) vec[a] = 0;
    for (b = 0; b < cn; b++) {
      if (bi[b] == -1) continue;	//if not found, pass it
      for (a = 0; a < size; a++) vec[a] += M[a + bi[b] * size];	//add all vectors of wordsnumber found this time
    }
    len = 0;
    for (a = 0; a < size; a++) len += vec[a] * vec[a];
    len = sqrt(len);	//is it needful? Yes, different vector makes different len value
    for (a = 0; a < size; a++) vec[a] /= len;	//unit vector
    for (a = 0; a < N; a++) bestd[a] = -1;		//best distances, init with -1
    for (a = 0; a < N; a++) bestw[a][0] = 0;	//best wordsnumber, init with '\0'
    for (c = 0; c < wordsnumber; c++) {							//traverse all wordsnumber
      a = 0;
      for (b = 0; b < cn; b++) if (bi[b] == c) a = 1;
      if (a == 1) continue;			//pass wordsnumber in vocab
      dist = 0;
      for (a = 0; a < size; a++) dist += vec[a] * M[a + c * size];
      for (a = 0; a < N; a++) {	//sort dist, Insertion Sort, DESC
        if (dist > bestd[a]) {
          for (d = N - 1; d > a; d--) {
            bestd[d] = bestd[d - 1];
            strcpy(bestw[d], bestw[d - 1]);
          }
          bestd[a] = dist;
          strcpy(bestw[a], &vocab[c * max_w]);
          break;
        }
      }
    }
   // for (a = 0; a < N; a++) printf("%50s\t\t%f\n", bestw[a], bestd[a]);	//display results

	
	for (a = 0; a < N; a++){
		char * s =bestw[a];
		float t=bestd[a];
		
		vec_str.push_back(s );
		vec_dis.push_back(t);	
	}
	cout<<"size nei....."<<vec_str.size()<<endl;
	//for (int a = 0; a < N; a++) cout<<vec_str[a]<<"   "<<vec_dis[a]<<endl;;	//display results
 // }

  return 0;
}



bool cmp_by_value(const PAIR& lhs, const PAIR& rhs) 
	{  
		return lhs.second > rhs.second;  
	}  


UINT GetWordHint_New(LPCSTR lpInStr,char * lpOutStrs[128], UINT iMaxCount)//��ȡ�ʵ���ʾ�����룬��� UINT CCompWindow::UpdateDicBuf()һ�ε���
{
	string words_index(lpInStr);		

	////outfile1<<lpInStr<<"$"<<endl;
	if (lpInStr=="") return 0;	
	for(UINT i=0;i<10;i++)
	{
		 lpOutStrs[i]="*";
		
	}	
	//return 10;
	
	int count=0;
	for(int m = 0;m < wordslen; m++)//wordslen��words.txt��size
	   {
		   if (count>=10) break;
		   else if (words_index.size() > words[m].size() ) continue;
	       else if (words_index == words[m].substr(0, words_index.size() ))//�Ӵʱ���Ҳ��ȡ��ͬ���ȣ��쿴�Ƿ��൱�������ͬs.substr(pos, n) 
		  {
			  //string to const char*
            string s=words[m];
			const int len = s.length();
			char* c;
		    c = new char[len+1];
		    strcpy(c,s.c_str());

            lpOutStrs[count]="*";
 
            lpOutStrs[count]=c;
			//...
	
            count++;
		   }
	   }
	return 10;
	
}

UINT GetPhraseHint_New(LPCSTR lpInStr, LPSTR* lpOutStrs, UINT iMaxCount)//��ȡ������ʾ�����룬��� UINT CCompWindow::UpdateDicBuf()һ�ε���
{	
	string words_index(lpInStr);	
	////outfile1<<lpInStr<<"$"<<endl;
	if (lpInStr=="") return 0;
	////outfile1<<lpInStr<<"#"<<endl;
    for(UINT i=0;i<10;i++)
	{
		 lpOutStrs[i]="**";
	}
	int count=0;
	for(int m = 0;m < phrases_6len; m++)//wordslen��words.txt��size
	   {
		   if (count>=10) break;
		   else if (words_index.size() > phrases_6[m].size() ) continue;
	       else if (words_index == phrases_6[m].substr(0, words_index.size() ))//�Ӵʱ���Ҳ��ȡ��ͬ���ȣ��쿴�Ƿ��൱�������ͬ
		  {
             string s=phrases_6[m];
			const int len = s.length();
			char* c;
		    c = new char[len+1];
		    strcpy(c,s.c_str());

            lpOutStrs[count]="**";
			//cstringתchar *
			//CString str1 =_T("123");

            lpOutStrs[count]=c;
 	
            count++;
		   }
	   }
	////////////////////////////////////////////////////////////////
	
	return 10;

}

//�������룬���ؾ�����ʾ���������������֮������ƶ�
UINT GetSentenceHint_New(LPCSTR lpInStr, LPSTR* lpOutStrs, UINT iMaxCount)//��ȡ������ʾ�����룬��� UINT CCompWindow::UpdateDicBuf()һ�ε���
{	
	//�����з֡���const char* תΪchar *
	//vector <char *> vec_input;
	//vec_input.clear();
	//char *buf = new char[strlen(lpInStr)+1];
 //	strcpy(buf, lpInStr);
	////��������пո��з�http://www.cnblogs.com/c4isr/archive/2012/07/10/2585411.html
	//const char * split = " "; 
	//char * pInput; 
	//pInput = strtok (buf,split); 
	//while(pInput!=NULL) { 	
	//	//outfile1<<"qiefen:"<<pInput<<endl;;	
	//	pInput = strtok(NULL,split); 
	//	vec_input.push_back(pInput);
	//} 
	string input(lpInStr);
	vector <string> vec_input;
	vec_input=splitWithStl(input, " ");

///������չģʽ����������Ļ������뵱ǰ�������ƶ�����10����Ҳ���뵽��ǰ����ķִ�������ȥ�������ӿ��м���/////////////////////////////////////////////////////////////////////////////////////////

	//semantic extension mode
	if (extended==true)
	{	
		vector<string> vec_str;
		vector<float> vec_dis;
		//string str="in this paper";
		compute( input, vec_str, vec_dis); //input text��
		cout<<"size wai....."<<vec_str.size()<<endl;
		for (int a = 0; a < 10; a++) 
		{
			vec_input.push_back(vec_str[a]);
			outfile1<<input<<":    "<<vec_str[a]<<"  ******************* "<<vec_dis[a]<<endl;;	//display results �����뵱ǰ������input�����Ƶ����д��Լ����ƶȣ�����������
		}
	
	}
		 
 /////������չ����//////////////////////////////////////////////////////////////////////////////


		//����ʾ10�� 
	CString words_index(lpInStr);	
	////outfile1<<lpInStr<<"$"<<endl;
	if (lpInStr=="") return 0;
	////outfile1<<lpInStr<<"#"<<endl;
    for(UINT i=0;i<10;i++)
	{
		 lpOutStrs[i]="***";
	}
	
	map<int, int> name_score_map;	 
	//���㵱ǰ����vec_input��ÿ������vec_vec_sentence֮������ƶȣ��������ҵ�10������
		for(int i=0; i<vec_input.size(); i++)	
		{ 
			string temp=vec_input[i];
			////outfile1<<"zzzzzzshuru:"<<temp.c_str()<<endl;
			for (int j=0; j<vec_sentence.size();j++)
			{
				////outfile1<<"xxxxxshuchu:"<<vec_sentence[j].c_str()<<endl;
				string str=vec_sentence[j];
				string::size_type idx;     
				idx=str.find(temp);//��a�в���b.
				if(idx == string::npos )//�����ڡ�
					cout << "not found\n";
				else//����
					name_score_map[j]++;
			}
		}
		//��map��Ԫ��ת�浽vector��  
		int count=0;
		vector<PAIR> name_score_vec(name_score_map.begin(), name_score_map.end());  
		sort(name_score_vec.begin(), name_score_vec.end(), cmp_by_value);  
		for (int i = 0; i != name_score_vec.size(); ++i) 
		{  	int sentenceid= name_score_vec[i].first;
			////outfile1<<"paixuhou.........:"<< sentenceid << endl;  
			////outfile1<<"paixusenence.........:"<< vec_sentence[sentenceid].c_str() << endl; 
			string s=vec_sentence[sentenceid];
			if (s.length()>200) continue;
			//string to char*
			const int len = s.length();
			char* c;
		    c = new char[len+1];
		    strcpy(c,s.c_str());
			if (count <10){				
				lpOutStrs[count]=c;
				count++;
			}
			else break;
		}  
	return 10;

}