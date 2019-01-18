// PageTrans.cpp : implementation file
//

#include "stdafx.h"
#include "TrayPanel.h"
#include "PageTrans.h"
#include "TrayPanelDlg.h"

// CPageTrans dialog

IMPLEMENT_DYNAMIC(CPageTrans, CDialog)

CPageTrans::CPageTrans(CWnd* pParent /*=NULL*/)
	: CDialog(CPageTrans::IDD, pParent)
{

}

CPageTrans::~CPageTrans()
{
}

void CPageTrans::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TRANS, m_ListTrans);
}


BEGIN_MESSAGE_MAP(CPageTrans, CDialog)
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_BTN_UP, &CPageTrans::OnBnClickedBtnUp)
	ON_BN_CLICKED(IDC_BTN_DOWN, &CPageTrans::OnBnClickedBtnDown)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TRANS, &CPageTrans::OnNMDblclkListTrans)
//	ON_NOTIFY(HDN_ITEMCLICK, 0, &CPageTrans::OnHdnItemclickListTrans)
ON_NOTIFY(NM_CLICK, IDC_LIST_TRANS, &CPageTrans::OnNMClickListTrans)
ON_BN_CLICKED(IDC_BTN_CA, &CPageTrans::OnBnClickedBtnCa)
ON_BN_CLICKED(IDC_BTN_UCA, &CPageTrans::OnBnClickedBtnUca)
ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_TRANS, &CPageTrans::OnLvnKeydownListTrans)
ON_BN_CLICKED(IDC_BTN_GETWORDDIC, &CPageTrans::OnBnClickedBtnGetworddic)
END_MESSAGE_MAP()


// CPageTrans message handlers

BOOL CPageTrans::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	POINT pt;
	GetCursorPos(&pt);
	CRect rt;
	((CButton*)GetDlgItem(IDC_BTN_GETWORDDIC))->GetWindowRect(rt);
	if(rt.PtInRect(pt))
	{
		SetCursor(::LoadCursor(NULL, IDC_HAND));
		return TRUE;
	}
	return CDialog::OnSetCursor(pWnd, nHitTest, message);

}

BOOL CPageTrans::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_pPanelDlg = GetParent()->GetParent();
	m_pProfileOp = &((CTrayPanelDlg*)m_pPanelDlg)->m_ProfileOp;
	InitListBox();
	RefreshDicName();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPageTrans::InitListBox(void)
{
	m_font.CreateFont(16, 0,0,0,FW_NORMAL, 0,0,0,
		DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
	m_ListTrans.SetFont(&m_font);
	m_ListTrans.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	m_ListTrans.SetBkColor(RGB(255,255,255));
	m_ListTrans.SetTextColor(RGB(55,90,235));
	m_ListTrans.SetTextBkColor(RGB(255,255,255));
	m_ListTrans.InsertColumn(0, _T("Dictionaries"), LVCFMT_LEFT, 120);
	m_ListTrans.InsertColumn(1, _T("Items"), LVCFMT_RIGHT, 50);
	m_ListTrans.InsertColumn(2, _T("Language"), LVCFMT_LEFT, 80);
}

void CPageTrans::RefreshDicName(void)
{
	m_ListTrans.DeleteAllItems();
	TCHAR Path[MAX_PATH];
	GetModuleFileName(NULL, Path, MAX_PATH);
	CString strPath(Path);
	strPath = strPath.Left(strPath.ReverseFind(_T('\\')));
	strPath.Append(TRANSDIRPATH);
	UINT iIndex = 0;
	for (UINT i=0; i<MAX_DIC_LOAD; i++)
	{
		if(wcscmp(_T("NULL"), m_pProfileOp->m_prmTransLoad[i].lpNameValue) == 0)
			break;
		m_ListTrans.InsertItem(iIndex, m_pProfileOp->m_prmTransLoad[i].lpNameValue);
		m_ListTrans.SetCheck(iIndex);
		iIndex++;
	}
	LVFINDINFO lfi;
	lfi.flags = LVFI_WRAP|LVFI_STRING;
	TCHAR lpName[128];
	CFileFind ffTns;
	BOOL bRetp = ffTns.FindFile(strPath+_T("*.tns"));
	while (bRetp)
	{
		bRetp = ffTns.FindNextFile();
		wcscpy(lpName, ffTns.GetFileTitle());
		lfi.psz = lpName;
		if(-1 == m_ListTrans.FindItem(&lfi))
			m_ListTrans.InsertItem(iIndex++, lpName);

	}
	UINT iDicNum = m_ListTrans.GetItemCount();
	for (UINT i=0; i<iDicNum; i++)
		GetDicInfo(i, FALSE);
}

void CPageTrans::OnBnClickedBtnUp()
{
	m_ListTrans.SetFocus();
	POSITION pos = m_ListTrans.GetFirstSelectedItemPosition();
	m_nIndex = m_ListTrans.GetNextSelectedItem(pos);
	if (m_nIndex == -1)	 
		return;  
	if (m_nIndex == 0)
		return;
	CString str1, str2, str3;
	str1 = m_ListTrans.GetItemText(m_nIndex, 0);
	str2 = m_ListTrans.GetItemText(m_nIndex, 1);
	str3 = m_ListTrans.GetItemText(m_nIndex, 2);
	BOOL bCheck = m_ListTrans.GetCheck(m_nIndex);
	m_ListTrans.DeleteItem(m_nIndex);
	m_ListTrans.InsertItem(m_nIndex-1, str1);
	m_ListTrans.SetItemText(m_nIndex-1, 1, str2);
	m_ListTrans.SetItemText(m_nIndex-1, 2, str3);
	m_nIndex--;
	UINT flag = LVIS_SELECTED|LVIS_FOCUSED;
	m_ListTrans.SetItemState(m_nIndex, flag, flag);
	m_ListTrans.SetCheck(m_nIndex, bCheck);
	m_pPanelDlg->PostMessage(WM_MODIFY);
}

void CPageTrans::OnBnClickedBtnDown()
{
	m_ListTrans.SetFocus();
	POSITION pos = m_ListTrans.GetFirstSelectedItemPosition();
	m_nIndex = m_ListTrans.GetNextSelectedItem(pos);
	if (m_nIndex == -1)
		return;  
	if (m_nIndex == m_ListTrans.GetItemCount()-1)
		return;
	CString str1, str2, str3;
	str1 = m_ListTrans.GetItemText(m_nIndex, 0);
	str2 = m_ListTrans.GetItemText(m_nIndex, 1);
	str3 = m_ListTrans.GetItemText(m_nIndex, 2);
	BOOL bCheck = m_ListTrans.GetCheck(m_nIndex);
	m_ListTrans.DeleteItem(m_nIndex);
	m_ListTrans.InsertItem(m_nIndex+1, str1);
	m_ListTrans.SetItemText(m_nIndex+1, 1, str2);
	m_ListTrans.SetItemText(m_nIndex+1, 2, str3);
	m_nIndex++;
	UINT flag = LVIS_SELECTED|LVIS_FOCUSED;
	m_ListTrans.SetItemState(m_nIndex, flag, flag);
	m_ListTrans.SetCheck(m_nIndex, bCheck);
	m_pPanelDlg->PostMessage(WM_MODIFY);
}

BOOL CPageTrans::GetDicInfo(int iIndex, BOOL bShow)
{
	if(iIndex<0)
		return FALSE;

	TCHAR exeFullPath[MAX_PATH];
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	CString strPath(exeFullPath);
	strPath=strPath.Left(strPath.ReverseFind('\\'));
	strPath.Append(TRANSDIRPATH);
	TCHAR strName[256];
	m_ListTrans.GetItemText(iIndex, 0, strName, 256);
	strPath.Append(strName);
	strPath.Append(_T(".tns"));
	TRANSDICINFO TransInfo;
	GetTransDicInfo(strPath, &TransInfo);
	CString strConvert;
	strConvert.Format(_T("%d"), TransInfo.m_iWordCount);
	m_ListTrans.SetItemText(iIndex, 1, strConvert);
	strConvert.Format(_T("%d"), TransInfo.m_dwLanguage);
	if(TransInfo.m_dwLanguage == 0)
		strConvert.Append(_T("(Default)"));
	m_ListTrans.SetItemText(iIndex, 2, strConvert);
	if(bShow)
	{
		SetDlgItemText(IDC_EDIT_INFO, TransInfo.m_lpDescription);
	}
	return 0;
}

void CPageTrans::OnNMDblclkListTrans(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ListTrans.GetFirstSelectedItemPosition();
	m_nIndex = m_ListTrans.GetNextSelectedItem(pos);
	if(m_nIndex>=0)
	{
		m_ListTrans.SetCheck(m_nIndex, !m_ListTrans.GetCheck(m_nIndex));
	}
	m_pPanelDlg->PostMessage(WM_MODIFY);
	*pResult = 0;
}


void CPageTrans::OnNMClickListTrans(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_pPanelDlg->PostMessage(WM_MODIFY);
	m_ListTrans.SetFocus();
	POSITION pos = m_ListTrans.GetFirstSelectedItemPosition();
	m_nIndex = m_ListTrans.GetNextSelectedItem(pos);
	GetDicInfo(m_nIndex, TRUE);
	*pResult = 0;
}

void CPageTrans::OnBnClickedBtnCa()
{
	UINT iCount = m_ListTrans.GetItemCount();
	UINT iUnChecked = 0;
	m_pPanelDlg->PostMessage(WM_MODIFY);
	for (UINT i=0; i<iCount; i++)
	{
		if(!m_ListTrans.GetCheck(i))
		{
			m_ListTrans.SetCheck(i);
			iUnChecked++;
		}
	}
	if(iUnChecked>0)
		return;
	for (UINT i=0; i<iCount; i++)
	{
		m_ListTrans.SetCheck(i, FALSE);
	}
}

void CPageTrans::OnBnClickedBtnUca()
{
	ApplyChanges();
	RefreshDicName();
}

void CPageTrans::ApplyChanges(void)
{
	int iCount = m_ListTrans.GetItemCount();
	int index = 0;
	for (int i=0; i<iCount && index<MAX_DIC_LOAD; i++)
	{
		if(m_ListTrans.GetCheck(i))
		{
			m_ListTrans.GetItemText(i, 0, m_pProfileOp->m_prmTransLoad[index++].lpNameValue, 31);
		}
	}
	for (; index<MAX_DIC_LOAD; index++)
	{
		wcscpy(m_pProfileOp->m_prmTransLoad[index].lpNameValue, _T("NULL"));
	}
}

void CPageTrans::OnLvnKeydownListTrans(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	m_ListTrans.SetFocus();
	POSITION pos = m_ListTrans.GetFirstSelectedItemPosition();
	m_nIndex = m_ListTrans.GetNextSelectedItem(pos);
	if(pLVKeyDow->wVKey == VK_UP)
	{
		if(m_nIndex>0)
			m_nIndex--;
	}
	else if(pLVKeyDow->wVKey == VK_DOWN)
	{
		if(m_nIndex<m_ListTrans.GetItemCount()-1)
			m_nIndex++;
	}
	GetDicInfo(m_nIndex, TRUE);
	*pResult = 0;
}

void CPageTrans::OnBnClickedBtnGetworddic()
{
	::ShellExecute(NULL, _T("open"), _T("http://www.Triivi.com/download.asp?direct=trans"), NULL, NULL, SW_NORMAL);
}

void CPageTrans::OnOK(void)
{
	CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
	pPanelDlg->OnBnClickedOk();
}

void CPageTrans::UpdateLanguage(void)
{
	g_SetDialogStrings(this, IDD);
}
