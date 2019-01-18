// PageMain.cpp : implementation file
//

#include "stdafx.h"
#include "TrayPanel.h"
#include "PageMain.h"
#include "TrayPanelDlg.h"
#include <stdlib.h>
extern bool use_history;// whether use history


// CPageMain dialog

IMPLEMENT_DYNAMIC(CPageMain, CDialog)

CPageMain::CPageMain(CWnd* pParent /*=NULL*/)
	: CDialog(CPageMain::IDD, pParent)
{

}

CPageMain::~CPageMain()
{
}

void CPageMain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HOTKEY, m_hkHotKey);
	DDX_Control(pDX, IDC_COMBO_THEME, m_cbTheme);
	DDX_Control(pDX, IDC_COMBO_FONT, m_cbFont);
	DDX_Control(pDX, IDC_COMBO_CLEAR, m_cbClear);
	DDX_Control(pDX, IDC_COMBO_LAN, m_cbLanguage);
}


BEGIN_MESSAGE_MAP(CPageMain, CDialog)

ON_BN_CLICKED(IDC_CHECK_ENABLE, &CPageMain::OnBnClickedCheckEnable)
//ON_WM_PAINT()
//ON_WM_SYSCOMMAND()
//ON_WM_SHOWWINDOW()
ON_BN_CLICKED(IDC_AUTORUN, &CPageMain::OnBnClickedAutorun) //使用词向量扩展
ON_BN_CLICKED(IDC_AUTOENABLE, &CPageMain::OnBnClickedAutorun) //允许使用历史
ON_BN_CLICKED(IDC_BOOLEAN, &CPageMain::OnBnClickedAutorun)
ON_BN_CLICKED(IDC_CHECK_SHADOW, &CPageMain::OnCbnSelchangeTheme)
ON_BN_CLICKED(IDC_CHECK_BOLD, &CPageMain::OnCbnSelchangeTheme)
ON_BN_CLICKED(IDC_CHECK_ITALIC, &CPageMain::OnCbnSelchangeTheme)


//ON_WM_KEYDOWN()
ON_WM_SHOWWINDOW()
ON_CBN_SELCHANGE(IDC_COMBO_USER_KF, &CPageMain::OnCbnSelchange)
ON_CBN_SELCHANGE(IDC_COMBO_USER_VK, &CPageMain::OnCbnSelchange)
ON_CBN_SELCHANGE(IDC_COMBO_USER_KF, &CPageMain::OnCbnSelchange)
ON_CBN_SELCHANGE(IDC_COMBO_TAB, &CPageMain::OnCbnSelchange)
ON_CBN_SELCHANGE(IDC_COMBO_ENTER, &CPageMain::OnCbnSelchange)
ON_CBN_SELCHANGE(IDC_COMBO_THEME, &CPageMain::OnCbnSelchangeTheme)
ON_CBN_SELCHANGE(IDC_COMBO_FONT, &CPageMain::OnCbnSelchangeTheme)
ON_CBN_SELCHANGE(IDC_COMBO_CLEAR, &CPageMain::OnCbnSelchangeTheme)
ON_EN_CHANGE(IDC_EDIT_FONTSIZE, &CPageMain::OnEnChangeEditFontsize)
ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FONT, &CPageMain::OnDeltaposSpinFont)
ON_CBN_SELCHANGE(IDC_COMBO_LAN, &CPageMain::OnCbnSelchangeComboLan)
END_MESSAGE_MAP()

int CALLBACK EnumFontFamProc(LPENUMLOGFONT lpelf,
							 LPNEWTEXTMETRIC lpntm,DWORD nFontType,long lparam)
{
	// Create a pointer to the dialog window
	CPageMain* pWnd = (CPageMain*) lparam;

	// add the font name to the list box
	if(CB_ERR == pWnd ->m_cbFont.FindString(0, lpelf ->elfLogFont.lfFaceName))
		pWnd ->m_cbFont.AddString(lpelf ->elfLogFont.lfFaceName);
	// Return 1 to continue font enumeration
	return 1;
}

BOOL CPageMain::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_pPanelDlg = (CDialog*)(GetParent()->GetParent());
	CTrayPanelDlg* pPannelDlg = (CTrayPanelDlg*)m_pPanelDlg;
	m_dlgCompSee.Create(IDD_DLG_COMPSEE, this);
	CComboBox *pThemeBox = (CComboBox*)GetDlgItem(IDC_COMBO_THEME);
	RECT rtWindow;
	pThemeBox->GetWindowRect(&rtWindow);
	pThemeBox->GetParent()->ScreenToClient(&rtWindow);
	m_dlgCompSee.MoveWindow(rtWindow.right+10, rtWindow.bottom-20, 170, 180);
	m_dlgCompSee.ShowWindow(TRUE);
	TCHAR pName[32];
	for (UINT i=0; i<pPannelDlg->m_ColorTheme.GetThemeNum(); i++)
	{
		if(pPannelDlg->m_ColorTheme.GetThemeName(i,pName))
			m_cbTheme.AddString(pName);
	}
	m_cbTheme.SetCurSel(pPannelDlg->m_ProfileOp.m_prmTheme.iValue);
	FillFontList();
	int iIndex = m_cbFont.SelectString(0, pPannelDlg->m_ProfileOp.m_prmFontName.lpNameValue);
	if(iIndex==CB_ERR)
	{
		m_cbFont.SelectString(0, _T("Times New Roma"));
		wcscpy(pPannelDlg->m_ProfileOp.m_prmFontName.lpNameValue, _T("Times New Roma"));
	}
	SetDlgItemInt(IDC_EDIT_FONTSIZE, pPannelDlg->m_ProfileOp.m_prmFontSize.iValue, FALSE);
	int iStyle = pPannelDlg->m_ProfileOp.m_prmFontStyle.iValue;
	if( (iStyle&FontStyleBold)!=0 )
	{
		((CButton*)GetDlgItem(IDC_CHECK_BOLD))->SetCheck(TRUE);
	}
	if( (iStyle&FontStyleItalic)!=0 )
	{
		((CButton*)GetDlgItem(IDC_CHECK_ITALIC))->SetCheck(TRUE);
	}
	m_cbClear.SetCurSel(pPannelDlg->m_ProfileOp.m_prmClearType.iValue);
	ListLanguage();
	return TRUE;  
}

void CPageMain::FillFontList()
{
	CString strCurFont;
	CString strPrevFont = _T("");
	LOGFONT lf;

	// Initialize the LOGFONT structure
	lf.lfCharSet = DEFAULT_CHARSET;
	wcscpy(lf.lfFaceName,_T(""));
	// clear the list box
	m_cbFont.ResetContent();
	// create a device context variable
	CClientDC dc (this);
	// Enumerate the font families
	::EnumFontFamiliesEx((HDC) dc,&lf,
		(FONTENUMPROC) EnumFontFamProc,(LPARAM) this,0);	
}

void CPageMain::OnBnClickedCheckEnable()
{
	CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
	pPanelDlg->OnPopupEnable();
}

void CPageMain::Setuphk()
{
	WORD mf, vk;
	m_hkHotKey.GetHotKey(vk, mf);
	CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
	if (!pPanelDlg->SetSysHotKey(mf, vk))
	{
		MessageBox(_T("Cann't install current hot key! It may be in conflict with other hot key."),
			_T("Triivi"), MB_OK | MB_ICONEXCLAMATION);
	m_hkHotKey.SetHotKey(0,0);
	}
}

BOOL CPageMain::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	if(wParam==2)
		return m_pPanelDlg->PostMessage(WM_COMMAND, wParam, lParam);
	return CDialog::OnCommand(wParam, lParam);
}

void CPageMain::DlgOK(void)
{
	CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
	Setuphk();
	pPanelDlg->m_ProfileOp.m_prmAutoRun.iValue = ((CButton*)GetDlgItem(IDC_AUTORUN))->GetCheck();
	pPanelDlg->m_ProfileOp.m_prmAutoEnable.iValue = ((CButton*)GetDlgItem(IDC_AUTOENABLE))->GetCheck();
	pPanelDlg->m_ProfileOp.m_prmEnableBoolean.iValue = ((CButton*)GetDlgItem(IDC_BOOLEAN))->GetCheck();

	/*pPanelDlg->m_ProfileOp.m_prmTabFunction.iValue = ((CComboBox*)GetDlgItem(IDC_COMBO_TAB))->GetCurSel();
	pPanelDlg->m_ProfileOp.m_prmReturnFunction.iValue = ((CComboBox*)GetDlgItem(IDC_COMBO_ENTER))->GetCurSel();
	pPanelDlg->m_ProfileOp.m_prmUserVK.iValue = ((CComboBox*)GetDlgItem(IDC_COMBO_USER_VK))->GetCurSel();
	pPanelDlg->m_ProfileOp.m_prmUserFunction.iValue = ((CComboBox*)GetDlgItem(IDC_COMBO_USER_KF))->GetCurSel();
	*/
	pPanelDlg->m_ProfileOp.m_prmShadow.iValue = ((CButton*)GetDlgItem(IDC_CHECK_SHADOW))->GetCheck();
	pPanelDlg->m_ProfileOp.m_prmTheme.iValue = m_cbTheme.GetCurSel();
	pPanelDlg->m_ColorTheme.GetColorTheme(m_cbTheme.GetCurSel(),
		&pPanelDlg->pCompWnd.m_clShadow,
		&pPanelDlg->pCompWnd.m_clMargin,
		&pPanelDlg->pCompWnd.m_clHotText,
		&pPanelDlg->pCompWnd.m_clCommonText,
		&pPanelDlg->pCompWnd.m_clBack1,
		&pPanelDlg->pCompWnd.m_clBack2,
		&pPanelDlg->pCompWnd.m_clFrame);
	/////////// font ///////////////
	int iStyle = FontStyleRegular;
	if(((CButton*)(GetDlgItem(IDC_CHECK_BOLD)))->GetCheck())
		iStyle = FontStyleBold;
	if(((CButton*)(GetDlgItem(IDC_CHECK_ITALIC)))->GetCheck())
		iStyle |= FontStyleItalic;
	pPanelDlg->m_ProfileOp.m_prmFontStyle.iValue = iStyle;
	UINT iSize = GetDlgItemInt(IDC_EDIT_FONTSIZE);
	if(iSize>=pPanelDlg->m_ProfileOp.m_prmFontSize.iMin &&
		iSize<=pPanelDlg->m_ProfileOp.m_prmFontSize.iMax)
		pPanelDlg->m_ProfileOp.m_prmFontSize.iValue = iSize;
	TCHAR strFontName[128];
	m_cbFont.GetWindowText(strFontName, 128);
	wcscpy(pPanelDlg->m_ProfileOp.m_prmFontName.lpNameValue, strFontName);
	pPanelDlg->m_ProfileOp.m_prmClearType.iValue = m_cbClear.GetCurSel();
	CString strPath;
	GetModuleFileName(NULL,strPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	strPath.ReleaseBuffer();
	if(pPanelDlg->m_ProfileOp.m_prmAutoRun.iValue)
	{
		SetAutoRun(strPath);
	}
	else
	{
		SetAutoRun(strPath, FALSE);
	}
	m_dlgCompSee.Invalidate();
}

BOOL CPageMain::SetAutoRun(CString strPath, BOOL bEnable)
{
	CString str;
	HKEY hRegKey;
	BOOL bResult = TRUE;
	str=_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");
	if(RegOpenKey(HKEY_LOCAL_MACHINE, str, &hRegKey) != ERROR_SUCCESS) 
		bResult=FALSE;
	else
	{
		_wsplitpath(strPath.GetBuffer(0),NULL,NULL,str.GetBufferSetLength(MAX_PATH+1),NULL);
		strPath.ReleaseBuffer();
		str.ReleaseBuffer();
		if(!bEnable)
		{
			RegDeleteValue(hRegKey,L"Triivi Typing");
		}
		else
		{
			if(::RegSetValueEx( hRegKey,L"Triivi Typing",0,REG_SZ,(CONST BYTE *)strPath.GetBuffer(0),strPath.GetLength()*2 )!=ERROR_SUCCESS)
				bResult=FALSE;
			else
				bResult=TRUE;
		}
		strPath.ReleaseBuffer();
	}
	return bResult;
}
void CPageMain::OnBnClickedAutorun()
{
	m_pPanelDlg->PostMessage(WM_MODIFY);
	//use_history=true; //允许使用历史

}

void CPageMain::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		CButton* pBtnEnable = (CButton*)GetDlgItem(IDC_CHECK_ENABLE);
		CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
		pBtnEnable->SetCheck(pPanelDlg->IsHookOn);
		m_hkHotKey.SetHotKey(pPanelDlg->m_ProfileOp.m_prmHotKey2.iValue, 
			pPanelDlg->m_ProfileOp.m_prmHotKey1.iValue);

		((CButton*)GetDlgItem(IDC_AUTORUN))->SetCheck(pPanelDlg->m_ProfileOp.m_prmAutoRun.iValue);
		((CButton*)GetDlgItem(IDC_AUTOENABLE))->SetCheck(pPanelDlg->m_ProfileOp.m_prmAutoEnable.iValue);
		((CButton*)GetDlgItem(IDC_BOOLEAN))->SetCheck(pPanelDlg->m_ProfileOp.m_prmEnableBoolean.iValue);
		/*((CComboBox*)GetDlgItem(IDC_COMBO_TAB))->SetCurSel(pPanelDlg->m_ProfileOp.m_prmTabFunction.iValue);
		((CComboBox*)GetDlgItem(IDC_COMBO_ENTER))->SetCurSel(pPanelDlg->m_ProfileOp.m_prmReturnFunction.iValue);
		((CComboBox*)GetDlgItem(IDC_COMBO_USER_VK))->SetCurSel(pPanelDlg->m_ProfileOp.m_prmUserVK.iValue);
		((CComboBox*)GetDlgItem(IDC_COMBO_USER_KF))->SetCurSel(pPanelDlg->m_ProfileOp.m_prmUserFunction.iValue);*/
		((CButton*)GetDlgItem(IDC_CHECK_SHADOW))->SetCheck(pPanelDlg->m_ProfileOp.m_prmShadow.iValue);
		m_cbTheme.SetCurSel(pPanelDlg->m_ProfileOp.m_prmTheme.iValue);
	}
}

void CPageMain::OnCbnSelchange()
{
	m_pPanelDlg->PostMessage(WM_MODIFY);
}

void CPageMain::OnCbnSelchangeTheme()
{
	m_pPanelDlg->PostMessage(WM_MODIFY);
	m_dlgCompSee.Invalidate();
}


void CPageMain::OnEnChangeEditFontsize()
{
	m_pPanelDlg->PostMessage(WM_MODIFY);
}

void CPageMain::OnOK(void)
{
	CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
	pPanelDlg->OnBnClickedOk();
}

void CPageMain::OnDeltaposSpinFont(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	if(pNMHDR->idFrom == IDC_SPIN_FONT)
	{
		UINT iSize = GetDlgItemInt(IDC_EDIT_FONTSIZE);
		if(iSize>=6 && iSize<=50)
		{
			iSize-=(pNMUpDown->iDelta>0?1:-1);
			if(iSize != 51 && iSize != 5)
				SetDlgItemInt(IDC_EDIT_FONTSIZE, iSize, FALSE);
		}
		m_pPanelDlg->PostMessage(WM_MODIFY);
		m_dlgCompSee.Invalidate();
	}
	*pResult = 0;
}

void CPageMain::UpdateLanguage(void)
{
	g_SetDialogStrings(this, IDD);
}

void CPageMain::ListLanguage(void)
{
	CFileFind find;
	BOOL bRet = find.FindFile(g_szCurPath + L"Language\\*.ini");
	BOOL bFound = false;
	CString szEng = L"";
	CString szFilePath;
	CString szValue;
	int dwSize = 256;
	while(bRet)
	{
		bRet = find.FindNextFile();
		if(find.IsDots() || find.IsDirectory()) continue;
		szFilePath = find.GetFilePath();
		if(GetPrivateProfileString(_T("Setting"),_T("Language"),L"",szValue.GetBuffer(dwSize),
			dwSize,szFilePath) != 0)
		{
			m_cbLanguage.AddString(szValue);
		}
	}
	CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
	m_cbLanguage.SelectString(0, pPanelDlg->m_ProfileOp.m_prmLanguage.lpNameValue);
}

void CPageMain::OnCbnSelchangeComboLan()
{
	CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
	int iSel = m_cbLanguage.GetCurSel();
	CString strLan;
	m_cbLanguage.GetLBText(iSel, strLan);
	((CTrayPanelApp*)AfxGetApp())->LoadLanguage(strLan);
	((CTrayPanelDlg*)(GetParent()->GetParent()))->UpdateAllLan();
	wcscpy((pPanelDlg->m_ProfileOp.m_prmLanguage).lpNameValue, strLan);
	m_pPanelDlg->PostMessage(WM_MODIFY);
}
