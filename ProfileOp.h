#pragma once
#include "stdafx.h"

#define	MAX_PARAM_NUM	35
#define MAX_DIC_LOAD	32

typedef struct _tagIniParam
{
	TCHAR lpszSection[32];
	TCHAR lpszEntry[32];
	UINT iValue;
	UINT iDefault;
	UINT iMin;
	UINT iMax;
}IniParam, *lpIniParam;

typedef struct _tagDicParam
{
	TCHAR lpszSection[32];
	TCHAR lpszEntry[32];
	TCHAR lpNameValue[32];
}DicParam, *lpDicParam, StringParam;

class CProfileOp
{
public:
	CProfileOp(void);
	~CProfileOp(void);

	void LoadProfile(LPCTSTR lpszFile);
	void SaveProfile();

public:
	union
	{
		IniParam Param[MAX_PARAM_NUM];
		struct {
			IniParam m_prmHotKey1;
			IniParam m_prmHotKey2;
			IniParam m_prmWordHintNum;
			IniParam m_prmPhraseHintNum;
			IniParam m_prmAutoRun;
			IniParam m_prmAutoEnable;
			IniParam m_prmEnableBoolean;
			IniParam m_prmTabFunction;
			IniParam m_prmShiftFunction;
			IniParam m_prmReturnFunction;
			IniParam m_prmUserVK;
			IniParam m_prmUserFunction;
			IniParam m_prmSubFunction;
			IniParam m_prmBraFunction;
			IniParam m_prmTheme;
			IniParam m_prmShadow;
			IniParam m_prmMaxWordLearn;
			IniParam m_prmMaxPhraseSort;
			IniParam m_prmHideWordBelow;
			IniParam m_prmStartHintLetter;
			IniParam m_prmEnableTranslation;
			IniParam m_prmShowUnmatched;
			IniParam m_prmProPhraseOnly;
			IniParam m_prmFontSize;
			IniParam m_prmFontStyle;
			IniParam m_prmEnableErrorCheck;
			IniParam m_prmEnablePronunCheck;
			IniParam m_prmStartECNum;
			IniParam m_prmECMaxHint;
			IniParam m_prmStartPCNum;
			IniParam m_prmPCMaxHint;
			IniParam m_prmClearType;
			IniParam m_prmInputMode;
			IniParam m_prmAutoAddSpace;
			IniParam m_prmCompleteInter;
		};
	};
	DicParam m_prmDicLoad[MAX_DIC_LOAD];
	DicParam m_prmTransLoad[MAX_DIC_LOAD];
	StringParam m_prmFontName;
	StringParam m_prmLanguage;

protected:
	TCHAR m_lpszFile[256];
};
