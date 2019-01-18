// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TRIIVICORE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TRIIVICORE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#pragma once
#ifdef TRIIVICORE_EXPORTS
#define TRIIVICORE_API __declspec(dllexport)
#else
#define TRIIVICORE_API __declspec(dllimport)
#endif

typedef struct _tagTRIICOREPARAM
{
	UINT m_iMaxAutoLearnWords;
	INT m_iMaxPhraseSort;
	UINT m_iHideWordBelow;
}TRIICOREPARAM, *LPTRIICOREPARAM;

typedef struct _tagPhraseDicInfo
{
	UINT32	m_iNodeCount;
	UINT32	m_iWordCount;				// how many words e.g:take
	UINT32	m_iPraseCount;			// how many phrase e.g:take on
	TCHAR	m_pDescrip[256];
}PHRASEDICINFO;

typedef struct _tagWordDicInfo
{
	UINT16	m_iVersion;
	UINT32	m_iNodeCount;
	DWORD	m_iWordCount;
	TCHAR	m_pDescrip[256];
}WORDDICINFO;

typedef struct _tagTRANSDICINFO
{
	UINT32 m_iNodeCount;
	UINT32 m_iWordCount;
	DWORD m_dwLanguage;
	TCHAR m_lpDescription[256];
}TRANSDICINFO;

TRIIVICORE_API BOOL SetStudyDictionary(LPCTSTR lpFileName);
TRIIVICORE_API BOOL LoadWordDictionary(LPCTSTR lpFileName);
TRIIVICORE_API BOOL LoadPhraseDictionary(LPCTSTR lpIndexName, LPCTSTR lpPhraseName);
TRIIVICORE_API void UnLoadAllDictinaries();
TRIIVICORE_API BOOL LoadTranslateData(LPCTSTR lpFileName);
TRIIVICORE_API BOOL LoadErrorCheckDic(LPCTSTR lpFileName);
TRIIVICORE_API BOOL GetTranslation(LPCSTR lpInStr, LPTSTR lpOutStr);
TRIIVICORE_API void GetLoadedDicNum(UINT &iWordDic, UINT &iPhraseDic, UINT &iTransDic);
TRIIVICORE_API UINT GetWordHint(LPCSTR lpInStr, LPSTR* lpOutStrs, UINT iMaxCount);
TRIIVICORE_API UINT GetPhraseHint(LPCSTR lpInStr, LPSTR* lpOutStrs, UINT iMaxCount);
TRIIVICORE_API UINT GetErrorCheck(LPCSTR lpInStr, LPSTR* lpOutStrs, UINT iMaxCount);
TRIIVICORE_API UINT GetMetaPhoneHint(LPSTR lpInStr, LPSTR* lpOutStrs, UINT iMaxCount);
TRIIVICORE_API BOOL LoadMetaPhoneDic(LPCTSTR lpFileIdx, LPCTSTR lpFileData);
TRIIVICORE_API void Learn(LPCSTR lpInStr);
TRIIVICORE_API void GetParam(LPTRIICOREPARAM pCoreParam);
TRIIVICORE_API void SetParam(LPTRIICOREPARAM pCoreParam);
TRIIVICORE_API BOOL IsStringExist(LPCSTR strIn);
TRIIVICORE_API BOOL GetPhraseDicInfo(LPCTSTR lpFileName, PHRASEDICINFO* pPhraseDicInfo);
TRIIVICORE_API BOOL GetWordDicInfo(LPCTSTR lpFileName, WORDDICINFO* pWordDicInfo);
TRIIVICORE_API BOOL GetTransDicInfo(LPCTSTR lpFileName, TRANSDICINFO* pTrasnDicInfo);
