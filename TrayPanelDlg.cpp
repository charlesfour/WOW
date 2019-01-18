// TrayPanelDlg.cpp : implementation file
//

#include "stdafx.h"
#include <python.h>
#include "TrayPanel.h"
#include "TrayPanelDlg.h"
#include <imm.h>
#include <string>
using namespace std;

extern string input_history;
bool topicgetted=false; //主题是否已经启动

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef BOOL (* LPFUNC_INSTALL)(HWND);
typedef void (* LPFUNC_UNINSTALL)();

// CTrayPanelDlg dialog

CTrayPanelDlg::CTrayPanelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrayPanelDlg::IDD, pParent)
	,pCompWnd(CCompWindow::Instance())
	,IsHookOn(false)
	,m_hHKDll(NULL)
	, m_bAutoLearnLoaded(FALSE)
{
	m_bEnableModify = FALSE;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CTrayPanelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_sheet);
}

BEGIN_MESSAGE_MAP(CTrayPanelDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SHOWTASK,CTrayPanelDlg::OnShowTask)
	ON_MESSAGE(WM_TRIIVIHOOK,CTrayPanelDlg::OnHookMessage)
	ON_MESSAGE(WM_TRIIVIHOOKCBT,CTrayPanelDlg::OnHookCBTMessage)
	ON_MESSAGE(WM_TRIIVIIME, CTrayPanelDlg::OnHookIMEMessage)
	ON_MESSAGE(WM_HOTKEY,CTrayPanelDlg::OnHotKey)
	ON_MESSAGE(WM_MODIFY,CTrayPanelDlg::OnModified)
	ON_MESSAGE(WM_TIP_NOTIFY,CTrayPanelDlg::OnTipNotify)
	ON_WM_SYSCOMMAND()
	ON_COMMAND(ID_POPUP_EXIT, &CTrayPanelDlg::OnPopupExit)
	ON_COMMAND(ID_POPUP_SHOW, &CTrayPanelDlg::OnPopupShow)
	ON_COMMAND(ID_POPUP_ENABLE, &CTrayPanelDlg::OnPopupEnable)
	ON_COMMAND(ID_POPUP_COMPATIBLEMODE, &CTrayPanelDlg::OnPopupCompatible)

	ON_BN_CLICKED(IDOK, &CTrayPanelDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTrayPanelDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDAPPLY, &CTrayPanelDlg::OnBnClickedApply)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDHELP, &CTrayPanelDlg::OnBnClickedHelp)
END_MESSAGE_MAP()


// CTrayPanelDlg message handlers

BOOL CTrayPanelDlg::OnInitDialog()
{


	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_muPopup.LoadMenu(IDR_MENU_POPUP);
	bEnableDic = TRUE;
	if((m_app=GlobalFindAtom(_T("TRIIVIAPP"))) == 0)
		m_app = GlobalAddAtom(_T("TRIIVIAPP"));
	else
	{
		if(IDYES !=
			MessageBox(_T("Found Triivi already running, open new Triivi anyway?"), 
			_T("Warnning"), 
			MB_YESNO|MB_ICONWARNING))
			exit(0);
	}
	TCHAR exeFullPath[MAX_PATH];
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	CString strPath(exeFullPath);
	INT position=strPath.ReverseFind('\\');
	strPath=strPath.Left(position);
	m_ProfileOp.LoadProfile(strPath + _T("\\config.ini"));
	ReLoadAllDic();
	RestoreCoreParam();
	InitColorTheme();
	m_sheet.AddPage(_T("Basic"), &m_PageMain, IDD_DLG_MAIN);
	m_sheet.AddPage(_T("Key Custom"), &m_PageKey, IDD_DLG_KEY);
	m_sheet.AddPage(_T("Pro Dictionaries"), &m_PageDic, IDD_DLG_DIC);
	m_sheet.AddPage(_T("Translation"), &m_PageTrans, IDD_DLG_TRANS);
	m_sheet.AddPage(_T("Suggestion"), &m_PageSuggest, IDD_DLG_SUGGESTION);
	m_sheet.AddPage(_T("Advanced"), &m_PageAdvanced, IDD_DLG_ADVANCED);
	m_sheet.AddPage(_T("About"), &m_PageAbout, IDD_DLG_ABOUT);
	m_sheet.Show();
	if(GlobalFindAtom(_T("TRIIVIHK")) == 0)
	{
		m_iHotKeyID = GlobalAddAtom(_T("TRIIVIHK"));
	}
	else
		m_iHotKeyID = (ATOM)830207;
	m_PageMain.m_hkHotKey.SetHotKey(m_ProfileOp.m_prmHotKey2.iValue, 
		m_ProfileOp.m_prmHotKey1.iValue);
	RegisterHotKey(GetSafeHwnd(), m_iHotKeyID, 
		m_ProfileOp.m_prmHotKey1.iValue,
		m_ProfileOp.m_prmHotKey2.iValue);
	pCompWnd.m_pProfileOp = &m_ProfileOp;
	if(m_ProfileOp.m_prmAutoEnable.iValue == 1)
	{
		IsHookOn = (InstallHook(this->m_hWnd)==TRUE)?true:false;
	}
	if(m_sheet.m_bEnable)
		PostMessage(WM_SYSCOMMAND, SC_MINIMIZE);
	m_bShowWndForAll = FALSE;
	CString strLan = m_ProfileOp.m_prmLanguage.lpNameValue;
	((CTrayPanelApp*)AfxGetApp())->LoadLanguage(strLan);
	UpdateAllLan();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTrayPanelDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTrayPanelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTrayPanelDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID==SC_MINIMIZE/* || nID == SC_CLOSE*/)
	{
		ToTray();
		return;
	} 
	else if (nID == SC_CLOSE)
	{
		if(IDNO == MessageBox(_T("Are you sure to exit?"), _T("Triivi"),
			MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2 | MB_SETFOREGROUND))
			return;
		else
			OnCancel();
	}
	CDialog::OnSysCommand(nID, lParam);
}

void CTrayPanelDlg::ToTray(void)
{
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd=this->m_hWnd;
	nid.uID=IDR_MAINFRAME;
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
	nid.uCallbackMessage=WM_SHOWTASK;
	if(IsHookOn)
		nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	else
		nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_DISABLE));
	lstrcpy(nid.szTip,_T("Triivi Professional 1.0"));
	Shell_NotifyIcon(NIM_ADD,&nid);
	ShowWindow(SW_SHOWMINIMIZED|SW_SHOWNOACTIVATE);
	ShowWindow(SW_HIDE);
}

LRESULT CTrayPanelDlg::OnShowTask(WPARAM wParam,LPARAM lParam)
{
	if(wParam!=IDR_MAINFRAME)
		return 1;
	switch(lParam)
	{
	case WM_RBUTTONUP:
		{
			this->SetForegroundWindow(); 
			LPPOINT lpoint=new tagPOINT;
			::GetCursorPos(lpoint);
			CMenu *pSubMenu = m_muPopup.GetSubMenu(0);
			if(IsHookOn)
				pSubMenu->CheckMenuItem(ID_POPUP_ENABLE, MF_CHECKED);
			else
				pSubMenu->CheckMenuItem(ID_POPUP_ENABLE, MF_UNCHECKED);
			pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON ,lpoint->x,lpoint->y,this);
			delete lpoint;
		}
		break;
	case WM_LBUTTONDBLCLK:
		{
			m_bEnableModify = TRUE;
			this->ShowWindow(SW_SHOWNORMAL);
		}
		break;
	}
	return 0; 
}

LRESULT CTrayPanelDlg::OnHookMessage(WPARAM wParam, LPARAM lParam)
{
	HWND	hWnd = ::GetForegroundWindow();
	DWORD   FormThreadID   =   GetCurrentThreadId();
	DWORD   CWndThreadID   =   GetWindowThreadProcessId(hWnd,   NULL);  
	AttachThreadInput(CWndThreadID,   FormThreadID,   true);  
	hWnd   =   ::GetFocus();  
	POINT pt;
	::GetCaretPos(&pt);
	::ClientToScreen(hWnd, &pt);
	AttachThreadInput(CWndThreadID,   FormThreadID,   false);
	if (!hWnd)
	{
		return 0L;
	}
	char str[256];
	BOOL bIsEdit = FALSE;
	GetClassNameA(hWnd, str, 256);
	strlwr(str);
	if (0 == strcmp(str, "_wwg") ||						// MS Word
		0 == strcmp(str, "directuihwnd") ||				// MSN
		//0 == memcmp(str, "excel", 5) ||				// MS Excel, Not supported now
		0 == strcmp(str, "paneclassdc") ||				// MS PowerPoint
		0 == strcmp(str, "internet explorer_server") ||	// MS IE
		0 == strcmp(str, "emacs") ||					// Emacs
		0 == strcmp(str, "ttnemulvt")					// FTerm
		)
	{
		bIsEdit = TRUE;
	}
	else
	{
		for(UINT i=0;i<strlen(str)-3;i++)
			if(0 == memcmp(str+i, "edit",4))
			{
				if((GetWindowLong(hWnd, GWL_STYLE)&(ES_PASSWORD|ES_NUMBER)) == 0)
					bIsEdit = TRUE;
				break;
			}
	}
	if(0 == memcmp(str, "richedit", 8) ||
		0 == memcmp(str, "directuihwnd", 12) ||
		0 == strcmp(str, "internet explorer_server") ||
		0 == memcmp(str, "emacs", 5))// special for backspace
		pCompWnd.m_bNeedSpecialBack = TRUE;
	else
		pCompWnd.m_bNeedSpecialBack = FALSE;
	m_hwndTarget = hWnd;
	if(hWnd) 
	{
		return m_KeyProcess.ProcessKey(hWnd, pt, wParam, lParam, bIsEdit||m_bShowWndForAll);
	}
	return 0L;
}

LRESULT CTrayPanelDlg::OnHookCBTMessage(WPARAM wParam, LPARAM lParam)
{
	if (wParam == HCBT_ACTIVATE || wParam==HCBT_SETFOCUS)
	{
		HWND activated=(HWND)lParam;// hwnd to be activated
		if (activated!=pCompWnd.GetTargetWnd()&&activated!=pCompWnd.m_hWnd) 
		{
			pCompWnd.ShowWnd(false);
		}
		else if(pCompWnd.IsNeedShow()) //sometimes we don't need to show it when switching back
			pCompWnd.ShowWnd(true);
	}
	return 0L;
}

LRESULT CTrayPanelDlg::OnHookIMEMessage(WPARAM wParam, LPARAM lParam)
{
	pCompWnd.SetTargetWnd(NULL);
	return 0l;
}
LRESULT CTrayPanelDlg::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	if (wParam==m_iHotKeyID)//switch on/off of the hook
	{
		if(IsHookOn)
		{
			UnloadHook();
			IsHookOn=false;
			BoolNotify(_T("Triivi Disabled!"));
		}
		else
		{
			if(InstallHook(this->m_hWnd)==false)
			{
				BoolNotify(_T("Insall Hook Error!"));
				return 0L;
			}
			else
			{
				IsHookOn=true;
				BoolNotify(_T("Triivi Enabled!"));
			}

		}
		Invalidate();
		return 0L;
	}
	return 0L;	
}

BOOL CTrayPanelDlg::DestroyWindow()
{
	if(IsHookOn)
	{
		UnloadHook();
	}
	Shell_NotifyIcon(NIM_DELETE,&nid);
	m_muPopup.DestroyMenu();
	UnLoadAllDictinaries();
	UnregisterHotKey(m_hWnd,m_iHotKeyID);
	GlobalDeleteAtom(m_iHotKeyID);
	GlobalDeleteAtom(m_app);
	return CDialog::DestroyWindow();
}

void CTrayPanelDlg::OnPopupExit()
{
	OnCancel();
}

void CTrayPanelDlg::OnPopupShow()
{
	this->ShowWindow(SW_SHOWNORMAL);
	m_bEnableModify = TRUE;
}
void CTrayPanelDlg::OnPopupCompatible()
{
	CMenu *pSubMenu = m_muPopup.GetSubMenu(0);
	if(m_bShowWndForAll)
	{
		m_bShowWndForAll = FALSE;
		pSubMenu->CheckMenuItem(ID_POPUP_COMPATIBLEMODE, MF_UNCHECKED);
	}
	else
	{
		m_bShowWndForAll = TRUE;
		pSubMenu->CheckMenuItem(ID_POPUP_COMPATIBLEMODE, MF_CHECKED);
	}
}
void CTrayPanelDlg::OnPopupEnable()
{
	CMenu *pSubMenu = m_muPopup.GetSubMenu(0);
	if(!IsHookOn)
	{
		pSubMenu->CheckMenuItem(ID_POPUP_ENABLE, MF_CHECKED);
		if(InstallHook(this->m_hWnd)==false)
		{
			BoolNotify(_T("Install Hook Error!"));
			return;
		}
		IsHookOn = true;
		BoolNotify(_T("Triivi Enabled!"));
	}
	else
	{
		pSubMenu->CheckMenuItem(ID_POPUP_ENABLE, MF_UNCHECKED);
		UnloadHook();
		IsHookOn = false;
		BoolNotify(_T("Triivi Disabled!"));
	}
}

LRESULT CTrayPanelDlg::OnModified(WPARAM wParam, LPARAM lParam)
{
	if(!m_bEnableModify)
		return 0L;
	CWnd *pBtn = GetDlgItem(IDAPPLY);
	pBtn->EnableWindow();
	return 0L;
}
BOOL CTrayPanelDlg::SetSysHotKey(UINT mf, UINT vk)
{
	UnregisterHotKey(GetSafeHwnd(), m_iHotKeyID);
	m_ProfileOp.m_prmHotKey1.iValue = mf;
	m_ProfileOp.m_prmHotKey2.iValue = vk;
	UINT mfu = 0;
	if(mf&HOTKEYF_ALT)
		mfu|=MOD_ALT;
	if(mf&HOTKEYF_CONTROL)
		mfu|=MOD_CONTROL;
	if(mf&HOTKEYF_EXT)
		mfu|=MOD_WIN;
	if(mf&HOTKEYF_SHIFT)
		mfu|=MOD_SHIFT;
	return RegisterHotKey(GetSafeHwnd(), m_iHotKeyID, mfu, vk);
}

void CTrayPanelDlg::OnBnClickedOk()
{
	if(GetDlgItem(IDAPPLY)->IsWindowEnabled())
	{
		m_PageMain.DlgOK();
		m_PageKey.DlgOK();
		m_PageAdvanced.DlgOK();
		m_PageDic.ApplyChanges();
		m_PageTrans.ApplyChanges();
		m_PageSuggest.DlgOK();
		ReLoadAllDic();
	}
	ToTray();
}

void CTrayPanelDlg::BoolNotify(CString strInfo)
{
	if(IsHookOn)
	{
		DestroyIcon(nid.hIcon);
		nid.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	}
	else
	{
		DestroyIcon(nid.hIcon);
		nid.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_DISABLE));
	}
	if(m_ProfileOp.m_prmEnableBoolean.iValue)
	{
		nid.uFlags=NIF_ICON|NIF_INFO|NIF_MESSAGE|NIF_TIP;
	}
	else
	{
		nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
	}
	lstrcpy(nid.szInfo, strInfo);
	lstrcpy(nid.szInfoTitle, TEXT("Triivi:"));
	nid.uTimeout = 10000; // in milliseconds
	nid.dwInfoFlags = NIIF_INFO|NIIF_NOSOUND;
	Shell_NotifyIcon(NIM_MODIFY, &nid);
}

LRESULT CTrayPanelDlg::OnTipNotify(WPARAM WPARAM, LPARAM lParam)
{
	return 0L;
}

BOOL CTrayPanelDlg::InstallHook(HWND hWnd)
{
	if(m_hHKDll!=NULL)
	{
		FreeLibrary(m_hHKDll);
	}
	pCompWnd.SetTargetWnd(NULL);
	m_hHKDll = LoadLibrary(_T("Triivihk.dll"));
	if(!m_hHKDll)
		return FALSE;
	LPFUNC_INSTALL InstallHK_DLL = (LPFUNC_INSTALL)GetProcAddress(m_hHKDll, "InstallHook");
	BOOL bRet = InstallHK_DLL(hWnd);
	((CButton*)m_PageMain.GetDlgItem(IDC_CHECK_ENABLE))->SetCheck(bRet);
	if(!bRet)
		m_hHKDll = NULL;
	return
		bRet;
}

void CTrayPanelDlg::UnloadHook()
{
	pCompWnd.SetTargetWnd(NULL);
	if(!m_hHKDll)
		return;
	LPFUNC_UNINSTALL UnInstallHK_DLL = 
		(LPFUNC_UNINSTALL)GetProcAddress(m_hHKDll, "UnloadHook");
	UnInstallHK_DLL();
	((CButton*)m_PageMain.GetDlgItem(IDC_CHECK_ENABLE))->SetCheck(FALSE);
	FreeLibrary(m_hHKDll);
	m_hHKDll = NULL;
}
void CTrayPanelDlg::OnBnClickedCancel()
{
	ToTray();
}

void CTrayPanelDlg::OnBnClickedApply()
{
	GetDlgItem(IDAPPLY)->EnableWindow(FALSE);
	m_PageMain.DlgOK();
	m_PageKey.DlgOK();
	m_PageAdvanced.DlgOK();
	m_PageDic.ApplyChanges();
	m_PageTrans.ApplyChanges();
	ReLoadAllDic();
}

void CTrayPanelDlg::InitColorTheme(void)
{
	m_ColorTheme.AddColorTheme(Color(255,200,200,200),
		Color(255,192,0,0), Color(255,255,61,48), 
		Color(255,0,130,229), Color(255,240,240,240), 
		Color(255,250,250,250), Color(255,50,130,229),
		_T("Flower of Pacific"));
	m_ColorTheme.AddColorTheme(Color(255,200,200,255),
		Color(255,25,25,133), Color(255,0,0,168),
		Color(255,74,74,233), Color(255,235,236,243),
		Color(255,245,246,253),Color(255,60,140,239),
		_T("Blue Melody"));
	m_ColorTheme.AddColorTheme(Color(255,200,200,200),
		Color(255,25,25,25), Color(255,122,122,122),
		Color(255,0,21,12), Color(255,240,245,240), 
		Color(255,250,250,250),Color(255,90,90,90),
		_T("Black & White"));
	m_ColorTheme.AddColorTheme(Color(255,160,160,160),
		Color(255,192,192,192), Color(255,208,0,160), 
		Color(255,0,0,240), Color(255,234,234,238), 
		Color(255,244,244,248), Color(255,188,0,140),
		_T("Rainy Summer"));
	m_ColorTheme.AddColorTheme(Color(255,215,215,205), 
		Color(255,0,0,0), Color(255,20,150,150),
		Color(255,20,160,160), Color(255,250,250,230), 
		Color(255,255,255,235), Color(255,10,120,120),
		_T("Classic"));
	m_ColorTheme.AddColorTheme(Color(255,215,221,225), 
		Color(255,139,173,209), Color(255,14,25,106),
		Color(255,89,89,89), Color(255,235,241,245), 
		Color(255,245,251,255),Color(255,139,173,209),
		_T("Feel Cool"));
	m_PageMain.m_pColorTheme = &m_ColorTheme;
	m_ColorTheme.GetColorTheme(m_ProfileOp.m_prmTheme.iValue,
		&pCompWnd.m_clShadow,
		&pCompWnd.m_clMargin,
		&pCompWnd.m_clHotText,
		&pCompWnd.m_clCommonText,
		&pCompWnd.m_clBack1,
		&pCompWnd.m_clBack2,
		&pCompWnd.m_clFrame);
}

BOOL CTrayPanelDlg::ReLoadAllDic(void)
{
	if(bEnableDic==FALSE)
		return FALSE;
	BOOL bRet = TRUE;
	TCHAR exeFullPath[MAX_PATH];
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	CString strPath(exeFullPath);
	strPath=strPath.Left(strPath.ReverseFind('\\'));
	if(!m_bAutoLearnLoaded)
	{
		SetStudyDictionary(LPCTSTR(strPath+AUTOLEARN));
		m_bAutoLearnLoaded = TRUE;
	}
	UnLoadAllDictinaries();
	if(m_ProfileOp.m_prmEnableErrorCheck.iValue==1)
		bRet &= LoadErrorCheckDic(strPath + ECDIC);
	if(m_ProfileOp.m_prmEnablePronunCheck.iValue==1)
		bRet &= LoadMetaPhoneDic(strPath + METAPHIDX, strPath + METAPHDATA);
	LoadWordDictionary(LPCTSTR(strPath+WORDDIC));
	if(m_ProfileOp.m_prmProPhraseOnly.iValue==0)
		LoadPhraseDictionary(LPCTSTR(strPath+PHRASEIDX),LPCTSTR(strPath+PHRASEPHS));
	CString strTranPath(strPath+TRANSDIRPATH);
	strPath.Append(PRODICPATH);
	BOOL bRetDic1, bRetDic2;
	for (UINT i=0; i<MAX_DIC_LOAD; i++)
	{
		if(wcscmp(_T("NULL"), m_ProfileOp.m_prmDicLoad[i].lpNameValue) == 0)
			break;
		CString strDicName(strPath + m_ProfileOp.m_prmDicLoad[i].lpNameValue);
		bRetDic1 = LoadWordDictionary(strDicName + _T(".wrd"));
		bRetDic2 =  LoadPhraseDictionary(strDicName + _T(".idx"), 
			strDicName + _T(".phs"));

		if(!(bRetDic1 || bRetDic2))		// dic had been deleted
		{
			bRet = FALSE;
			for (UINT j=i; j<MAX_DIC_LOAD-1; j++)	//jump the error file;
			{
				if(wcscmp(_T("NULL"), m_ProfileOp.m_prmDicLoad[j+1].lpNameValue) == 0)
				{
					wcscpy(m_ProfileOp.m_prmDicLoad[j].lpNameValue, _T("NULL"));
					break;
				}
				wcscpy(m_ProfileOp.m_prmDicLoad[j].lpNameValue,
					m_ProfileOp.m_prmDicLoad[j+1].lpNameValue);
			}
			wcscpy(m_ProfileOp.m_prmDicLoad[MAX_DIC_LOAD-1].lpNameValue, _T("NULL"));
			i--;
		}
	}
	for (UINT i=0; i<MAX_DIC_LOAD; i++)
	{
		if(wcscmp(_T("NULL"), m_ProfileOp.m_prmTransLoad[i].lpNameValue) == 0)
			break;
		CString strDicName(strTranPath + m_ProfileOp.m_prmTransLoad[i].lpNameValue);
		strDicName.Append(_T(".tns"));
		bRetDic1 = LoadTranslateData(strDicName);
		if(!bRetDic1)
		{
			bRet = FALSE;
			for (UINT j=i; j<MAX_DIC_LOAD-1; j++)	//jump the error file;
			{
				if(wcscmp(_T("NULL"), m_ProfileOp.m_prmTransLoad[j+1].lpNameValue) == 0)
				{
					wcscpy(m_ProfileOp.m_prmTransLoad[j].lpNameValue, _T("NULL"));
					break;
				}
				wcscpy(m_ProfileOp.m_prmTransLoad[j].lpNameValue,
					m_ProfileOp.m_prmTransLoad[j+1].lpNameValue);
			}
			wcscpy(m_ProfileOp.m_prmTransLoad[MAX_DIC_LOAD-1].lpNameValue, _T("NULL"));
			i--;
		}
	}
	return bRet;
}

void CTrayPanelDlg::RestoreCoreParam()
{
	TRIICOREPARAM CoreParam;
	CoreParam.m_iHideWordBelow = m_ProfileOp.m_prmHideWordBelow.iValue;
	CoreParam.m_iMaxAutoLearnWords = m_ProfileOp.m_prmMaxWordLearn.iValue;
	CoreParam.m_iMaxPhraseSort = m_ProfileOp.m_prmMaxPhraseSort.iValue;
	SetParam(&CoreParam);
}

BOOL CTrayPanelDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	TCHAR exeFullPath[MAX_PATH];
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	CString strPath(exeFullPath);
	INT position=strPath.ReverseFind('\\');
	strPath=strPath.Left(position);
	::ShellExecute(NULL, _T("open"), 
		strPath+_T("\\Triivi.chm"), 
		NULL, NULL, SW_NORMAL);
	return 0;
}

void CTrayPanelDlg::OnBnClickedHelp()
{
	OnHelpInfo(NULL);
}

void CTrayPanelDlg::UpdateLanguage(void)
{
	g_SetDialogStrings(this, IDD);
}

void CTrayPanelDlg::UpdateAllLan(void)
{
	UpdateLanguage();
	
	m_PageDic.UpdateLanguage();
	m_PageMain.UpdateLanguage();
	m_PageKey.UpdateLanguage();
	m_PageAbout.UpdateLanguage();
	m_PageTrans.UpdateLanguage();
	m_PageSuggest.UpdateLanguage();
	m_PageAdvanced.UpdateLanguage();
}
