// TrayPanel.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include <python.h>
#include "TrayPanel.h"
#include "TrayPanelDlg.h"
#include <vector>
#include <algorithm>
#include <set>
 
#include <string>

#include <iostream> 
#include <fstream> 

#include <sstream>  
//ͷ�ļ�
#include "StdAfx.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <math.h>
#include <malloc.h>
#include <iostream>




const long long max_size = 2000;         // max length of strings
const long long N = 40;                  // number of closest words that will be shown
const long long max_w = 50;              // max length of vocabulary entries
bool use_history=false;// whether use history

char *vocab;
float *M;
long long wordsnumber;
long long size;
//��������word2vector
using namespace std; 


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

	 int wordslen;
	 int phraseslen;
    int phrases_6len;
	int  sentences_len;
	 std::vector < std::string> vec_sentence;
	 	 vector < string> words;
		 vector < string> phrases;
		 vector < string> phrases_6;

	//CString words[150000];//���ʿ�
   // CString phrases[46000];//���ʿ� ����ĳ����ƺ������ƣ��ٴ�Щ�����
    //CString phrases_6[154000];
	
	vector < vector < string > > vec_vec;
	//vector < vector < string> > vec_vec_sentence;

    vector <vector <string>> vec_sentence_topic; //�������������ڱ��治ͬ�����µľ���
//	vector <vector < vector < string> >> vec_vec_sentence_topic;

	ofstream outfile2("result3.txt",ios::app);

	//����word2vector �������ļ�
int load_vocab()
{
	cout<<"load vocab...."<<endl;
  char *bestw[N];
  float  bestd[N];

  FILE *f;
  char st1[max_size];
 

  char file_name[max_size], st[100][max_size];
  float dist, len,  vec[max_size];	//dist: distance; len: norm of vector; bestd: best distance
  long long  a, b, c, d, cn, bi[100];
  char ch;

  
  strcpy(file_name, "vectors.bin");	//copy filename to the variable
  f = fopen(file_name, "rb");	//open the file in BINARY mode
  if (f == NULL) {
    printf("Input file not found\n");
    return -1;
  }
  fscanf(f, "%lld", &wordsnumber);	//word count
  fscanf(f, "%lld", &size);		//dimension count
  vocab = (char *)malloc((long long)wordsnumber * max_w * sizeof(char));	//memory alloc, store wordsnumber, max_w chars per word
  for (a = 0; a < N; a++) bestw[a] = (char *)malloc(max_size * sizeof(char));	//memory alloc, store closest vocabs
  
  M = (float *)malloc((long long)wordsnumber * (long long)size * sizeof(float));		//memory alloc, store vectors
  if (M == NULL) {
    printf("Cannot allocate memory: %lld MB    %lld  %lld\n", (long long)wordsnumber * size * sizeof(float) / 1048576, wordsnumber, size);	//1048576 = 1024 * 1024
    return -1;
  }
  for (b = 0; b < wordsnumber; b++) {
    fscanf(f, "%s%c", &vocab[b * max_w], &ch);
    for (a = 0; a < size; a++) fread(&M[a + b * size], sizeof(float), 1, f);
    len = 0;
    for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];
    len = sqrt(len);	//denominator, [ZH_CN]FenMu
    for (a = 0; a < size; a++) M[a + b * size] /= len;	//unit vector, [ZH_CN]DanWei XiangLiang
  }
  fclose(f);

    // for (int b = 0; b <wordsnumber; b++)  cout<<ocab[b * max_w]<<endl;

  return wordsnumber;
}

	string CStringToString(CString cstr)
{
    string str;
    setlocale(LC_ALL,"chs");
    wchar_t wch[20480];
    char temp[20480];
    wcscpy(wch,cstr.GetString());
    wcstombs(temp,wch,20479);    
    str.append(temp);        
    return str;

}
	std::vector<std::string> splitWithStl(const std::string &str,const std::string &pattern)
{
    std::vector<std::string> resVec;

    if ("" == str)
    {
        return resVec;
    }
    //�����ȡ���һ������
    std::string strs = str + pattern;

    size_t pos = strs.find(pattern);
    size_t size = strs.size();

    while (pos != std::string::npos)
    {
        std::string x = strs.substr(0,pos);
        resVec.push_back(x);
        strs = strs.substr(pos+1,size);
        pos = strs.find(pattern);
    }

    return resVec;
}

// CTrayPanelApp

BEGIN_MESSAGE_MAP(CTrayPanelApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTrayPanelApp construction

CTrayPanelApp::CTrayPanelApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTrayPanelApp object

CTrayPanelApp theApp;

CString g_szLanguagePath;	//���������ļ���·��
CString g_szSettingPath;	//�������õ��ļ�·��
CString	g_szCurPath;		//���浱ǰ·��

// CTrayPanelApp initialization

BOOL CTrayPanelApp::InitInstance()
{
	//�����������
	load_vocab();

	//�Ƚ�������������ʷ�ļ����롣
	std::ifstream t("input_history111.txt");  
	std::stringstream buffer;  
	buffer << t.rdbuf();  
	std::string contents(buffer.str()); 
	if (contents.size()<5) contents="the food is bad and bad and bad";
	outfile2<<contents<<endl;
	t.close();

	//������lstm��ģ�͡�
	outfile2<<"python begin...."<<endl;
    Py_Initialize(); /*��ʼ��python������,���߱�����Ҫ�õ�python������*/
	PyRun_SimpleString("import sys");
	
	 //���ݲ��� //���²�������������
	 /*
	PyObject* moduleName = PyString_FromString("test001"); //ģ�����������ļ���
    PyObject* pModule = PyImport_Import(moduleName);

 	 if (!pModule) // ����ģ��ʧ��
    {
        AfxMessageBox(_T("����ģ��1ʧ�ܣ�"));
        return 0;
    }

	PyObject * pFunc= PyObject_GetAttrString(pModule,"add");//Add:Python�ļ��еĺ�����    //��������  
	 if (!pFunc || !PyCallable_Check(pFunc))  // ��֤�Ƿ���سɹ�
    {
       AfxMessageBox(_T("���غ���1ʧ�ܣ�"));
        return 0;
    }

	PyObject *pArgs = PyTuple_New(2); //�������õĲ������ݾ�����Ԫ�����ʽ�����,2��ʾ��������  
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 5));//0---���i��ʾ����int�ͱ���  
	PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 7));//1---���//����ֵ  
	PyObject *pReturn = NULL;  
	pReturn = PyEval_CallObject(pFunc, pArgs);//���ú���  
	//������ֵת��Ϊint����  
	int result;  
	PyArg_Parse(pReturn, "i", &result);//i��ʾת����int�ͱ���  
	cout << "5+7 = " << result << endl;  	
	//AfxMessageBox(_T("���غ���ʧ�ܣ�"));
    AfxMessageBox(result);
	outfile2<<"python over77777777777777...."<<result<<endl;
	*/
	//������ʽģ��



	PyObject* moduleName = PyString_FromString("lstm-predict"); //ģ�����������ļ���
    PyObject* pModule = PyImport_Import(moduleName);

 	 if (!pModule) // ����ģ��ʧ��
    {
        AfxMessageBox(_T("����ģ��lstm-predictʧ�ܣ�"));
        return 0;
    }

	PyObject * pFunc= PyObject_GetAttrString(pModule,"train_lstm");//Add:Python�ļ��еĺ�����    //��������  
	 if (!pFunc || !PyCallable_Check(pFunc))  // ��֤�Ƿ���سɹ�
    {
       AfxMessageBox(_T("���غ���train_lstmʧ�ܣ�"));
        return 0;
    }	

	PyObject *pArgs = PyTuple_New(1); //�������õĲ������ݾ�����Ԫ�����ʽ�����,2��ʾ��������  
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", contents));//0---���i��ʾ����int�ͱ���  
	//PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", "the food is bad and bad and bad"));//0---���i��ʾ����int�ͱ���  
	//PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 7));//1---���//����ֵ  
	
	PyObject *pReturn = NULL;  
	pReturn = PyEval_CallObject(pFunc, pArgs);//���ú���  
	//������ֵת��Ϊint����  
	int result;  
	result=9;
	PyArg_Parse(pReturn, "i", &result);//i��ʾת����int�ͱ���  
	
	

	outfile2<<result<<endl;

    Py_Finalize(); /*����python���������ͷ���Դ*/
   //system("pause");

   //outfile2<<"python over77777777777777...."<<result<<endl;

	//����ʱ�words.txt
    int k1=0;
	ifstream file1;
    file1.open("words.txt",ios::in);
    if(!file1.is_open())
        return 0;    
     std::string strLine1;
	 vector<std::string> vec_temp1;
     while(getline(file1,strLine1))
    {
		vec_temp1.clear();
		if(strLine1.empty())
            continue;
        cout<<strLine1 <<endl; 
		k1++;
		words.push_back(strLine1);
    }
	 wordslen = k1;
   
	// //�������ã����Ƿ�ʹ��extended��
	//ifstream filexxx;
 //   filexxx.open("setting.txt",ios::in);
 //   if(!filexxx.is_open())
 //       return 0;    
 //    std::string s;

 //    getline(filexxx,s);
	// std::string last=s.substr(s.length()-1, 1);
	// if (last == "1") extended=true;


  //����phrases_6.text
    int k6=0;
	ifstream file6;
    file6.open("phrases_6.txt",ios::in);
    if(!file6.is_open())
        return 0;    
     std::string strLine6;
	 vector<std::string> vec_temp6;
     while(getline(file6,strLine6))
    {
		vec_temp6.clear();
		if(strLine6.empty())
            continue;
        cout<<strLine6 <<endl; 
		k6++;
		phrases_6.push_back(strLine6);
    }
	phrases_6len  = k6;

  //����abstract_sentence.txt
	int k9=0;
	ifstream file9;
    file9.open("pattern_sentence.txt",ios::in);
	//file9.open("4.txt",ios::in);

    if(!file9.is_open())
        return 0;    
     std::string strLine9;
	 vector<std::string> vec_temp9;
     while(getline(file9,strLine9))
    {
		vec_temp9.clear();
		if(strLine9.empty())
            continue;
        cout<<strLine9 <<endl; 
		k9++;
		vec_sentence.push_back(strLine9);
		//vec_temp= splitWithStl(strLine, " ");
		//for (int n=0; n<vec_temp.size(); n++) ////outfile2<<"ppppp:"<<vec_temp[n]<<endl;
		//vec_vec_sentence.push_back(vec_temp);
    }
	 sentences_len = k9;

  //���벻ͬ�����µľ���sentence.txt
	 for (int x=0; x<5; x++)
	 {
		 std::stringstream ss;
		std::string str;
		ss<<x;
		ss>>str;

		int k99=0;
		ifstream file;
		file.open(str+".txt",ios::in);
		if(!file.is_open())
			return 0;    
		 std::string strLine;
		 vector<std::string> vec_111;
		 vector < vector < string> > vec_vec_222;

		 vector<std::string> vec_temp;
		 while(getline(file,strLine))
		{
			vec_temp.clear();
			if(strLine.empty())
				continue;
			cout<<strLine <<endl; 
			k99++;
			vec_111.push_back(strLine);
			//vec_temp= splitWithStl(strLine, " ");
			//for (int n=0; n<vec_temp.size(); n++) ////outfile2<<"ppppp:"<<vec_temp[n]<<endl;
			//vec_vec_222.push_back(vec_temp);

		}
		 outfile2<<""<<vec_111.size()<<endl;
		
		 vec_sentence_topic.push_back(vec_111);
		// vec_vec_sentence_topic.push_back(vec_vec_222);
		// sentences_len = k9;
	 }

	 //��һ�������£���history��size �ϴ�ʱ���滻vec_sentence��vec_vec_sentence
	 if ( contents.size()>10000 )
	 {
		 outfile2<<"yijing dayu 100:   "<<result<<"   yuanlai desize   "<<vec_sentence.size()<<endl;
		 vec_sentence= vec_sentence_topic[result];
		 outfile2<<"houlai de size..."<<vec_sentence.size()<<endl;
		// vec_vec_sentence=vec_vec_sentence_topic[result];	 
	 }


//����similar_meaning_lexicon.txt�ļ�
                              
	CString tmp8;
	CStdioFile file8; 
	file8.Open(_T("similar_meaning_lexicon.txt"),CFile::modeRead);
    ofstream outfile("sim_log.txt",ios::app);
	while(file8.ReadString(tmp8)) //tmp8Ϊһ��
	{
       vector <string> word_vec;		
		//ȡ����һ����

		string oneline=CStringToString(tmp8);
		std::string firstword= oneline.substr(0, oneline.find(":",0) );
		word_vec.push_back(firstword);
		
		//outfile<<firstword.c_str()<<" ";
		string remains=oneline.substr( oneline.find(":",0)+1, oneline.length()-oneline.find(":",0)-1 );
		while ( true)//��remains���ҵ�һ����ǰ�Ĵ�
		{
		
			string oneword=remains.substr(0, remains.find(";",0));
			word_vec.push_back(oneword);
			//outfile<<oneword.c_str()<<" ";
			if ( remains.find(";",0)==remains.length()-1 ) 
			{
			remains=remains.substr( remains.find(";",0)+1,remains.length()- remains.find(";",0)-1 );
			break;
			}
               remains=remains.substr( remains.find(";",0)+1,remains.length()- remains.find(";",0)-1 );
		}
		//outfile<<endl;
		if (word_vec.size()>0 ) vec_vec.push_back(word_vec);	
		word_vec.clear();
			 	
	} 
	file8.Close();

	AfxMessageBox(_T("WOW (WOnderful Words): An IME-based Revision Assistant."));

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	
	CWinApp::InitInstance();
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	AfxOleInit();		// Triivi New Added!!!!!

	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
/////////////////////////////////////
	
	//��ȡ��ǰ·��
	CString szCurPath(L"");
	GetModuleFileName(NULL,szCurPath.GetBuffer(MAX_PATH),MAX_PATH);	
	szCurPath.ReleaseBuffer();
	g_szCurPath = szCurPath.Left(szCurPath.ReverseFind(L'\\') + 1);

	//�����ļ��ڵ�ǰ·���� 
	g_szSettingPath = g_szCurPath + L"config.ini";
	CFileFind find;
	if(!find.FindFile(g_szSettingPath)) 
		MakeResource(IDR_SETTING,g_szSettingPath);
	find.Close();
	
/////////////////////////////////////
	CTrayPanelDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CTrayPanelApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
	return CWinApp::ExitInstance();
}

/*********************************************************************
* ��������:CTrayPanelApp::LoadLanguage
* ˵��:	װ������������� ��� szLangSelΪ����װ�����ԣ�������������
* ����: Geng 
*********************************************************************/
void CTrayPanelApp::LoadLanguage(CString szLangSel /*= ""*/)
{
	//��������
	CString szSection = L"Setting";
	CString szKey = L"Language",szLang;
	DWORD dwSize = 1000;

	if(!szLangSel.IsEmpty())	//��������
	{
		szLang = szLangSel;
	}
	else	//��ȡ��������
	{
		//��ȡ���õ�����
		GetPrivateProfileString(szSection,szKey,L"English",szLang.GetBuffer(dwSize),dwSize,g_szSettingPath);
		szLang.ReleaseBuffer();
	}

	//�����Ƿ����
	CFileFind find;
	BOOL bRet = find.FindFile(g_szCurPath + L"Language\\*.ini");
	BOOL bFound = false;
	CString szEng = L"";
	while(bRet)
	{
		bRet = find.FindNextFile();
		if(find.IsDots() || find.IsDirectory()) continue;

		CString szValue;
		CString szFilePath = find.GetFilePath();
		if(GetPrivateProfileString(szSection,szKey,L"",szValue.GetBuffer(dwSize),
			dwSize,szFilePath) != 0)
		{
			szValue.ReleaseBuffer();
			if(szValue == szLang)
			{
				g_szLanguagePath = szFilePath;
				bFound = true;
				break;
			}
		}
	}
	find.Close();

	//δ�ҵ��趨������
	if(!bFound)
	{
		int nLangID[2] = {IDR_LANG_ENG,IDR_LANG_CH};
		CString szFileName[2] = {L"\\English.ini",L"\\SimpChs.ini"};
		CString szPath = g_szCurPath + L"Language";
		CreateDirectory(szPath,NULL);
		for(int i = 0;i < 2;i++)
		{
			MakeResource(nLangID[i],szPath + szFileName[i]);
		}
		//Ĭ��ʹ��Ӣ��
		g_szLanguagePath = szPath + szFileName[0];
		szLang = L"English";
	}

	//������������
	WritePrivateProfileString(szSection,szKey,szLang,g_szSettingPath);
}

/*********************************************************************
* ��������:CTrayPanelApp::MakeResource
* ˵��:	���δ�ҵ��������Դ�ļ�(�������ļ��������ļ���)���ӳ����в���
* ����: Geng 
*********************************************************************/
bool CTrayPanelApp::MakeResource(int nID, CString szPathName)
{
	HRSRC hSrc = FindResource(NULL,MAKEINTRESOURCE(nID),_T("OWNER_DATA"));
	if(hSrc == NULL)	return false;

	HGLOBAL hGlobal = LoadResource(NULL,hSrc);
	if(hGlobal == NULL)	return false;

	LPVOID lp = LockResource(hGlobal);
	DWORD dwSize = SizeofResource(NULL,hSrc);

	CFile file;
	if(file.Open(szPathName,CFile::modeCreate|CFile::modeWrite))
	{
		file.Write(lp,dwSize);
		file.Close();
	}
	FreeResource(hGlobal);

	return true;
}

/*********************************************************************
* ��������:g_LoadString
* ˵��:	���ݱ�ʶ szID��ѡ���������ļ��м����ַ���
* ����:	Geng 
*********************************************************************/
CString g_LoadString(CString szID)
{
	CString szValue;
	DWORD dwSize = 1000;
	GetPrivateProfileString(L"String",szID,L"Not found",
		szValue.GetBuffer(dwSize),dwSize,g_szLanguagePath);
	szValue.ReleaseBuffer();

	szValue.Replace(L"\\n",L"\n");	//�滻�ػ��з���

	return szValue;
}

/*********************************************************************
* ��������:g_SetDialogStrings(CDialog *pDlg,UINT uDlgID)
* ˵��:	���Ի�������ʱ��ȡ�����пɵõ����ַ����������浽�����ļ���
ÿ���ؼ��öԻ���ID�Ϳؼ�IDΨһ��ʶ

* ��ڲ���:
* CDialog *pDlg -- �Ի����ָ��
* UINT uDlgID -- �öԻ����ID
* ����: Geng 
*********************************************************************/
void g_SetDialogStrings(CDialog *pDlg,UINT uDlgID)
{
	CString szSection = L"String";
	CString szKey,szText;
	bool bSetText = 1;	//1:���ļ��������öԻ���
						//0:�ӶԻ���������浽�ļ�
	if(bSetText)		//1:���ļ��������öԻ���
	{
		CString szDefault = L"";
		DWORD dwSize = 1000;
		TCHAR* pData = (TCHAR*)malloc(dwSize*sizeof(TCHAR));

		//���Ի������
		szKey.Format(L"IDD%d_Title",uDlgID);
		if(GetPrivateProfileString(szSection,szKey,szDefault,
			pData,dwSize,g_szLanguagePath) != 0)
		{
			pDlg->SetWindowText(pData);
		}

		//д������ӿؼ��ı�������
		CWnd* pWnd = pDlg->GetWindow(GW_CHILD);
		while(pWnd != NULL)
		{
			szKey.Format(L"IDD%d_%d",uDlgID,pWnd->GetDlgCtrlID());
			if(GetPrivateProfileString(szSection,szKey,szDefault,
				pData,dwSize,g_szLanguagePath) != 0)
			{
				pWnd->SetWindowText(pData);
			}
			pWnd = pWnd->GetWindow(GW_HWNDNEXT);
		}

		//�ͷ��ڴ�
		free(pData);
	}
	else	//0:�ӶԻ���������浽�ļ�
	{
		//д��Ի������
		szKey.Format(L"IDD%d_Title",uDlgID);
		pDlg->GetWindowText(szText);
		WritePrivateProfileString(szSection,szKey,szText,g_szLanguagePath);

		//д������ӿؼ��ı�������
		CWnd* pWnd = pDlg->GetWindow(GW_CHILD);
		while(pWnd != NULL)
		{
			szKey.Format(L"IDD%d_%d",uDlgID,pWnd->GetDlgCtrlID());
			pWnd->GetWindowText(szText);
			WritePrivateProfileString(szSection,szKey,szText,g_szLanguagePath);
			pWnd = pWnd->GetWindow(GW_HWNDNEXT);
		}
	}
}