#include "stdafx.h"
#include "ProfileOp.h"

CProfileOp::CProfileOp(void)
{
	// UISETUP-Hotkey1
	wcscpy(m_prmHotKey1.lpszSection, _T("UISETUP"));
	wcscpy(m_prmHotKey1.lpszEntry, _T("Hotkey1"));
	m_prmHotKey1.iDefault = MOD_CONTROL;
	m_prmHotKey1.iMin = 0;
	m_prmHotKey1.iMax = 256;
	
	// UISETUP-Hotkey2
	wcscpy(m_prmHotKey2.lpszSection, _T("UISETUP"));
	wcscpy(m_prmHotKey2.lpszEntry, _T("Hotkey2"));
	m_prmHotKey2.iDefault = VK_F5;
	m_prmHotKey2.iMin = 0;
	m_prmHotKey2.iMax = 0x0FFFF;

	wcscpy(m_prmWordHintNum.lpszSection, _T("CORESETUP"));
	wcscpy(m_prmWordHintNum.lpszEntry, _T("MaxWordHintNum"));
	m_prmWordHintNum.iDefault = 16;
	m_prmWordHintNum.iMin = 3;
	m_prmWordHintNum.iMax = 63;

	wcscpy(m_prmPhraseHintNum.lpszSection, _T("CORESETUP"));
	wcscpy(m_prmPhraseHintNum.lpszEntry, _T("MaxPhraseHintNum"));
	m_prmPhraseHintNum.iDefault = 12;
	m_prmPhraseHintNum.iMin = 0;
	m_prmPhraseHintNum.iMax = 32;

	wcscpy(m_prmAutoRun.lpszSection, _T("UISETUP"));
	wcscpy(m_prmAutoRun.lpszEntry, _T("Automatic Run"));
	m_prmAutoRun.iDefault = 1;
	m_prmAutoRun.iMin = 0;
	m_prmAutoRun.iMax = 1;

	wcscpy(m_prmAutoEnable.lpszSection, _T("UISETUP"));
	wcscpy(m_prmAutoEnable.lpszEntry, _T("Automatic Enable"));
	m_prmAutoEnable.iDefault = 1;
	m_prmAutoEnable.iMin = 0;
	m_prmAutoEnable.iMax = 1;

	wcscpy(m_prmEnableBoolean.lpszSection, _T("UISETUP"));
	wcscpy(m_prmEnableBoolean.lpszEntry, _T("Enable Boolean"));
	m_prmEnableBoolean.iDefault = 1;
	m_prmEnableBoolean.iMin = 0;
	m_prmEnableBoolean.iMax = 1;

	wcscpy(m_prmTabFunction.lpszSection, _T("UISETUP"));
	wcscpy(m_prmTabFunction.lpszEntry, _T("TAB Key Function"));
	m_prmTabFunction.iDefault = KF_COMPLETE;
	m_prmTabFunction.iMin = KF_START;
	m_prmTabFunction.iMax = KF_END;

	wcscpy(m_prmReturnFunction.lpszSection, _T("UISETUP"));
	wcscpy(m_prmReturnFunction.lpszEntry, _T("Enter Key Function"));
	m_prmReturnFunction.iDefault = KF_NOTHING;
	m_prmReturnFunction.iMin = KF_START;
	m_prmReturnFunction.iMax = KF_END;

	wcscpy(m_prmUserFunction.lpszSection, _T("UISETUP"));
	wcscpy(m_prmUserFunction.lpszEntry, _T("User Key Function"));
	m_prmUserFunction.iDefault = 1;
	m_prmUserFunction.iMin = 0;
	m_prmUserFunction.iMax = 1;

	wcscpy(m_prmUserVK.lpszSection, _T("UISETUP"));
	wcscpy(m_prmUserVK.lpszEntry, _T("User Key VK"));
	m_prmUserVK.iDefault = 0;
	m_prmUserVK.iMin = 0;
	m_prmUserVK.iMax = 2;

	wcscpy(m_prmShiftFunction.lpszSection, _T("UISETUP"));
	wcscpy(m_prmShiftFunction.lpszEntry, _T("Shift Key Function"));
	m_prmShiftFunction.iDefault = KF_COMPLETE;
	m_prmShiftFunction.iMin = KF_START;
	m_prmShiftFunction.iMax = KF_END;

	wcscpy(m_prmSubFunction.lpszSection, _T("UISETUP"));
	wcscpy(m_prmSubFunction.lpszEntry, _T("Sub Key Function"));
	m_prmSubFunction.iDefault = KF_PASS;
	m_prmSubFunction.iMin = KF_PASS;
	m_prmSubFunction.iMax = KF_PAGE;

	wcscpy(m_prmBraFunction.lpszSection, _T("UISETUP"));
	wcscpy(m_prmBraFunction.lpszEntry, _T("Bra Key Function"));
	m_prmBraFunction.iDefault = KF_PASS;
	m_prmBraFunction.iMin = KF_PASS;
	m_prmBraFunction.iMax = KF_PAGE;

	wcscpy(m_prmTheme.lpszSection, _T("UISETUP"));
	wcscpy(m_prmTheme.lpszEntry, _T("Color Theme"));
	m_prmTheme.iDefault = 0;
	m_prmTheme.iMin = 0;
	m_prmTheme.iMax = 15;

	wcscpy(m_prmShadow.lpszSection, _T("UISETUP"));
	wcscpy(m_prmShadow.lpszEntry, _T("Text Shadow"));
	m_prmShadow.iDefault = 1;
	m_prmShadow.iMin = 0;
	m_prmShadow.iMax = 1;

	wcscpy(m_prmMaxWordLearn.lpszSection, _T("CORESETUP"));
	wcscpy(m_prmMaxWordLearn.lpszEntry, _T("Word Cache Size"));
	m_prmMaxWordLearn.iDefault = 1000;
	m_prmMaxWordLearn.iMin = 500;
	m_prmMaxWordLearn.iMax = 5000;

	wcscpy(m_prmMaxPhraseSort.lpszSection, _T("CORESETUP"));
	wcscpy(m_prmMaxPhraseSort.lpszEntry, _T("Phrase Sort Depth"));
	m_prmMaxPhraseSort.iDefault = 800;
	m_prmMaxPhraseSort.iMin = 100;
	m_prmMaxPhraseSort.iMax = 2000;

	wcscpy(m_prmHideWordBelow.lpszSection, _T("CORESETUP"));
	wcscpy(m_prmHideWordBelow.lpszEntry, _T("Hide Word Below"));
	m_prmHideWordBelow.iDefault = 3;
	m_prmHideWordBelow.iMin = 0;
	m_prmHideWordBelow.iMax = 8;

	wcscpy(m_prmEnableTranslation.lpszSection, _T("CORESETUP"));
	wcscpy(m_prmEnableTranslation.lpszEntry, _T("Enable Translation"));
	m_prmEnableTranslation.iDefault = 1;
	m_prmEnableTranslation.iMin = 0;
	m_prmEnableTranslation.iMax = 1;

	wcscpy(m_prmShowUnmatched.lpszSection, _T("CORESETUP"));
	wcscpy(m_prmShowUnmatched.lpszEntry, _T("Unmatched Translation"));
	m_prmShowUnmatched.iDefault = 1;
	m_prmShowUnmatched.iMin = 0;
	m_prmShowUnmatched.iMax = 1;

	wcscpy(m_prmStartHintLetter.lpszSection, _T("CORESETUP"));
	wcscpy(m_prmStartHintLetter.lpszEntry, _T("Start Hint Letters"));
	m_prmStartHintLetter.iDefault = 1;
	m_prmStartHintLetter.iMin = 1;
	m_prmStartHintLetter.iMax = 8;
	
	wcscpy(m_prmProPhraseOnly.lpszSection, _T("CORESETUP"));
	wcscpy(m_prmProPhraseOnly.lpszEntry, _T("Pro Phrases Only"));
	m_prmProPhraseOnly.iDefault = 0;
	m_prmProPhraseOnly.iMin = 0;
	m_prmProPhraseOnly.iMax = 1;

	wcscpy(m_prmEnableErrorCheck.lpszSection, _T("CORESETUP"));
	wcscpy(m_prmEnableErrorCheck.lpszEntry, _T("Enable Error Check"));
	m_prmEnableErrorCheck.iDefault = 0;
	m_prmEnableErrorCheck.iMin = 0;
	m_prmEnableErrorCheck.iMax = 1;

	wcscpy(m_prmEnablePronunCheck.lpszSection, _T("CORESETUP"));
	wcscpy(m_prmEnablePronunCheck.lpszEntry, _T("Enable Pronun Check"));
	m_prmEnablePronunCheck.iDefault = 1;
	m_prmEnablePronunCheck.iMin = 0;
	m_prmEnablePronunCheck.iMax = 1;

	wcscpy(m_prmStartECNum.lpszSection, _T("CORESETUP"));
	wcscpy(m_prmStartECNum.lpszEntry, _T("Start EC Less"));
	m_prmStartECNum.iDefault = 1;
	m_prmStartECNum.iMin = 1;
	m_prmStartECNum.iMax = 8;
	wcscpy(m_prmECMaxHint.lpszSection, _T("CORESETUP"));
	wcscpy(m_prmECMaxHint.lpszEntry, _T("Max EC Hint"));
	m_prmECMaxHint.iDefault = 4;
	m_prmECMaxHint.iMin = 1;
	m_prmECMaxHint.iMax = 16;

	wcscpy(m_prmStartPCNum.lpszSection, _T("CORESETUP"));
	wcscpy(m_prmStartPCNum.lpszEntry, _T("Start PC Less"));
	m_prmStartPCNum.iDefault = 1;
	m_prmStartPCNum.iMin = 1;
	m_prmStartPCNum.iMax = 8;

	wcscpy(m_prmPCMaxHint.lpszSection, _T("CORESETUP"));
	wcscpy(m_prmPCMaxHint.lpszEntry, _T("Max PC Hint"));
	m_prmPCMaxHint.iDefault = 8;
	m_prmPCMaxHint.iMin = 1;
	m_prmPCMaxHint.iMax = 16;

	wcscpy(m_prmFontSize.lpszSection, _T("UISETUP"));
	wcscpy(m_prmFontSize.lpszEntry, _T("Font Size"));
	m_prmFontSize.iDefault = 16;
	m_prmFontSize.iMin = 6;
	m_prmFontSize.iMax = 50;

	wcscpy(m_prmFontStyle.lpszSection, _T("UISETUP"));
	wcscpy(m_prmFontStyle.lpszEntry, _T("Font Style"));
	m_prmFontStyle.iDefault = 0;
	m_prmFontStyle.iMin = 0;
	m_prmFontStyle.iMax = 3;

	wcscpy(m_prmClearType.lpszSection, _T("UISETUP"));
	wcscpy(m_prmClearType.lpszEntry, _T("Text Clear"));
	m_prmClearType.iDefault = 0;
	m_prmClearType.iMin = 0;
	m_prmClearType.iMax = 5;

	wcscpy(m_prmInputMode.lpszSection, _T("UISETUP"));
	wcscpy(m_prmInputMode.lpszEntry, _T("Input Mode"));
	m_prmInputMode.iDefault = 0;
	m_prmInputMode.iMin = 0;
	m_prmInputMode.iMax = 1;

	wcscpy(m_prmAutoAddSpace.lpszSection, _T("UISETUP"));
	wcscpy(m_prmAutoAddSpace.lpszEntry, _T("Append Space"));
	m_prmAutoAddSpace.iDefault = 0;
	m_prmAutoAddSpace.iMin = 0;
	m_prmAutoAddSpace.iMax = 1;

	wcscpy(m_prmCompleteInter.lpszSection, _T("UISETUP"));
	wcscpy(m_prmCompleteInter.lpszEntry, _T("Complete After Inter"));
	m_prmCompleteInter.iDefault = 0;
	m_prmCompleteInter.iMin = 0;
	m_prmCompleteInter.iMax = 1;

	TCHAR num[4];
	TCHAR index[64];
	for (UINT i=0; i<MAX_DIC_LOAD; i++)
	{
		wcscpy(m_prmDicLoad[i].lpszSection, _T("Pro Dictionaries"));
		_itow(i+1, num, 10);
		wcscpy(index, _T("DicIndex"));
		wcscat(index, num);
		wcscpy(m_prmDicLoad[i].lpszEntry, index);

		wcscpy(m_prmTransLoad[i].lpszSection, _T("Translation"));
		wcscpy(m_prmTransLoad[i].lpszEntry, index);
	}

	wcscpy(m_prmFontName.lpszSection, _T("UISETUP"));
	wcscpy(m_prmFontName.lpszEntry, _T("Font Name"));

	wcscpy(m_prmLanguage.lpszSection, _T("UISETUP"));
	wcscpy(m_prmLanguage.lpszEntry, _T("Language"));

}

CProfileOp::~CProfileOp(void)
{
	if(wcslen(m_lpszFile)>0)
		SaveProfile();
}

void CProfileOp::LoadProfile(LPCTSTR lpszFile)
{
	for (int i=0; i<MAX_PARAM_NUM; i++)
	{
		Param[i].iValue = GetPrivateProfileInt(Param[i].lpszSection, 
			Param[i].lpszEntry, Param[i].iDefault, lpszFile);
		if(Param[i].iValue>Param[i].iMax || Param[i].iValue<Param[i].iMin)
			Param[i].iValue = Param[i].iDefault;
	}
	for (int i=0; i<MAX_DIC_LOAD; i++)
	{
		GetPrivateProfileString(m_prmDicLoad[i].lpszSection,
			m_prmDicLoad[i].lpszEntry, _T("NULL"),
			m_prmDicLoad[i].lpNameValue, 32,
			lpszFile);
		GetPrivateProfileString(m_prmTransLoad[i].lpszSection,
			m_prmTransLoad[i].lpszEntry, _T("NULL"),
			m_prmTransLoad[i].lpNameValue, 32,
			lpszFile);
	}
	wcscpy(m_lpszFile, lpszFile);
	GetPrivateProfileString(m_prmFontName.lpszSection,
		m_prmFontName.lpszEntry, _T("Times New Roma"),
		m_prmFontName.lpNameValue, 32,
		lpszFile);
	GetPrivateProfileString(m_prmLanguage.lpszSection,
		m_prmLanguage.lpszEntry, _T("English"),
		m_prmLanguage.lpNameValue, 32,
		lpszFile);
}

void CProfileOp::SaveProfile()
{
	TCHAR str[256];
	for(int i=0; i<MAX_PARAM_NUM; i++)
	{
		if(Param[i].iValue>Param[i].iMax || Param[i].iValue<Param[i].iMin)
			Param[i].iValue = Param[i].iDefault;
		_itow_s(Param[i].iValue, str, 255, 10);
		WritePrivateProfileString(Param[i].lpszSection, 
			Param[i].lpszEntry, str, m_lpszFile);
	}
	for (int i=0; i<MAX_DIC_LOAD; i++)
	{
		WritePrivateProfileString(m_prmDicLoad[i].lpszSection,
			m_prmDicLoad[i].lpszEntry,
			m_prmDicLoad[i].lpNameValue,
			m_lpszFile);
		if(wcscmp(_T("NULL"), m_prmDicLoad[i].lpNameValue) != 0)
			continue;
		else
			break;
	}
	for (int i=0; i<MAX_DIC_LOAD; i++)
	{
		WritePrivateProfileString(m_prmTransLoad[i].lpszSection,
			m_prmTransLoad[i].lpszEntry,
			m_prmTransLoad[i].lpNameValue,
			m_lpszFile);
		if(wcscmp(_T("NULL"), m_prmTransLoad[i].lpNameValue) != 0)
			continue;
		else
			break;
	}
	WritePrivateProfileString(m_prmFontName.lpszSection, 
		m_prmFontName.lpszEntry, m_prmFontName.lpNameValue, m_lpszFile);
	WritePrivateProfileString(m_prmLanguage.lpszSection, 
		m_prmLanguage.lpszEntry, m_prmLanguage.lpNameValue, m_lpszFile);
}