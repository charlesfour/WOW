// PageDic.cpp : implementation file
//

#include "stdafx.h"
#include "TrayPanel.h"
#include "PageDic.h"
#include "TrayPanelDlg.h"

// CPageDic dialog

IMPLEMENT_DYNAMIC(CPageDic, CDialog)

CPageDic::CPageDic(CWnd* pParent /*=NULL*/)
	: CDialog(CPageDic::IDD, pParent)
{
	m_nIndex = -1;
}

CPageDic::~CPageDic()
{
}

void CPageDic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DIC, m_ListDic);
}


BEGIN_MESSAGE_MAP(CPageDic, CDialog)
//	ON_EN_CHANGE(IDC_EDIT1, &CPageDic::OnEnChangeEdit1)
ON_WM_SETCURSOR()
ON_BN_CLICKED(IDC_BTN_GETWORDDIC, &CPageDic::OnBnClickedBtnGetworddic)
ON_BN_CLICKED(IDC_BTN_UP, &CPageDic::OnBnClickedBtnUp)
ON_BN_CLICKED(IDC_BTN_DOWN, &CPageDic::OnBnClickedBtnDown)
ON_NOTIFY(NM_DBLCLK, IDC_LIST_DIC, &CPageDic::OnNMDblclkListDic)
ON_NOTIFY(NM_CLICK, IDC_LIST_DIC, &CPageDic::OnNMClickListDic)
ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_DIC, &CPageDic::OnLvnKeydownListDic)
ON_BN_CLICKED(IDC_BTN_CA, &CPageDic::OnBnClickedBtnCa)
ON_BN_CLICKED(IDC_BTN_UCA, &CPageDic::OnBnClickedBtnUca)
END_MESSAGE_MAP()

BOOL CPageDic::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_pPanelDlg = GetParent()->GetParent();
	m_pProfileOp = &((CTrayPanelDlg*)m_pPanelDlg)->m_ProfileOp;
	InitListBox();
	RefreshDicName();
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CPageDic::InitListBox(void)
{
	m_font.CreateFont(16, 0,0,0,FW_NORMAL, 0,0,0,
		DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
	m_ListDic.SetFont(&m_font);
	m_ListDic.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	m_ListDic.SetBkColor(RGB(255,255,255));
	m_ListDic.SetTextColor(RGB(55,90,235));
	m_ListDic.SetTextBkColor(RGB(255,255,255));
	m_ListDic.InsertColumn(0, _T("Dictionaries"), LVCFMT_LEFT, 100);
	m_ListDic.InsertColumn(1, _T("Words"), LVCFMT_RIGHT, 50);
	m_ListDic.InsertColumn(2, _T("Phrases"), LVCFMT_RIGHT, 80);
}

BOOL CPageDic::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if(wParam==2)
		return m_pPanelDlg->PostMessage(WM_COMMAND, wParam, lParam);
	return CDialog::OnCommand(wParam, lParam);
}

BOOL CPageDic::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
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

void CPageDic::OnBnClickedBtnGetworddic()
{
	::ShellExecute(NULL, _T("open"), _T("http://www.Triivi.com/download.asp?direct=pro"), NULL, NULL, SW_NORMAL);
}

void CPageDic::OnBnClickedBtnUp()
{
	m_ListDic.SetFocus();
	POSITION pos = m_ListDic.GetFirstSelectedItemPosition();
	m_nIndex = m_ListDic.GetNextSelectedItem(pos);
	if (m_nIndex == -1)	 
		return;  
	if (m_nIndex == 0)
		return;
	CString str1, str2, str3;
	str1 = m_ListDic.GetItemText(m_nIndex, 0);
	str2 = m_ListDic.GetItemText(m_nIndex, 1);
	str3 = m_ListDic.GetItemText(m_nIndex, 2);
	BOOL bCheck = m_ListDic.GetCheck(m_nIndex);
	m_ListDic.DeleteItem(m_nIndex);
	m_ListDic.InsertItem(m_nIndex-1, str1);
	m_ListDic.SetItemText(m_nIndex-1, 1, str2);
	m_ListDic.SetItemText(m_nIndex-1, 2, str3);
	m_nIndex--;
	UINT flag = LVIS_SELECTED|LVIS_FOCUSED;
	m_ListDic.SetItemState(m_nIndex, flag, flag);
	m_ListDic.SetCheck(m_nIndex, bCheck);
	m_pPanelDlg->PostMessage(WM_MODIFY);
}

void CPageDic::OnBnClickedBtnDown()
{
	m_ListDic.SetFocus();
	POSITION pos = m_ListDic.GetFirstSelectedItemPosition();
	m_nIndex = m_ListDic.GetNextSelectedItem(pos);
	if (m_nIndex == -1)
		return;  
	if (m_nIndex == m_ListDic.GetItemCount()-1)
		return;
	CString str1, str2, str3;
	str1 = m_ListDic.GetItemText(m_nIndex, 0);
	str2 = m_ListDic.GetItemText(m_nIndex, 1);
	str3 = m_ListDic.GetItemText(m_nIndex, 2);
	BOOL bCheck = m_ListDic.GetCheck(m_nIndex);
	m_ListDic.DeleteItem(m_nIndex);
	m_ListDic.InsertItem(m_nIndex+1, str1);
	m_ListDic.SetItemText(m_nIndex+1, 1, str2);
	m_ListDic.SetItemText(m_nIndex+1, 2, str3);
	m_nIndex++;
	UINT flag = LVIS_SELECTED|LVIS_FOCUSED;
	m_ListDic.SetItemState(m_nIndex, flag, flag);
	m_ListDic.SetCheck(m_nIndex, bCheck);
	m_pPanelDlg->PostMessage(WM_MODIFY);
}

void CPageDic::OnNMDblclkListDic(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ListDic.GetFirstSelectedItemPosition();
	m_nIndex = m_ListDic.GetNextSelectedItem(pos);
	if(m_nIndex>=0)
	{
		m_ListDic.SetCheck(m_nIndex, !m_ListDic.GetCheck(m_nIndex));
	}
	m_pPanelDlg->PostMessage(WM_MODIFY);
	*pResult = 0;
}

void CPageDic::RefreshDicName(void)
{
	m_ListDic.DeleteAllItems();
	TCHAR Path[MAX_PATH];
	GetModuleFileName(NULL, Path, MAX_PATH);
	CString strPath(Path);
	strPath = strPath.Left(strPath.ReverseFind(_T('\\')));
	strPath.Append(PRODICPATH);
	UINT iIndex = 0;
	for (UINT i=0; i<MAX_DIC_LOAD; i++)
	{
		if(wcscmp(_T("NULL"), m_pProfileOp->m_prmDicLoad[i].lpNameValue) == 0)
			break;
		m_ListDic.InsertItem(iIndex, m_pProfileOp->m_prmDicLoad[i].lpNameValue);
		m_ListDic.SetCheck(iIndex);
		iIndex++;
	}
	LVFINDINFO lfi;
	lfi.flags = LVFI_WRAP|LVFI_STRING;
	TCHAR lpName[128];
	CFileFind ffPhs;
	BOOL bRetp = ffPhs.FindFile(strPath+_T("*.idx"));
	while (bRetp)
	{
		bRetp = ffPhs.FindNextFile();
		wcscpy(lpName, ffPhs.GetFileTitle());
		lfi.psz = lpName;
		if(-1 == m_ListDic.FindItem(&lfi))
			m_ListDic.InsertItem(iIndex++, lpName);

	}
	UINT iDicNum = m_ListDic.GetItemCount();
	for (UINT i=0; i<iDicNum; i++)
		GetDicInfo(i, FALSE);
}

BOOL CPageDic::GetDicInfo(int iIndex, BOOL bSetEdit)
{
	if(iIndex<0)
		return FALSE;

	TCHAR exeFullPath[MAX_PATH];
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	CString strPath(exeFullPath);
	strPath=strPath.Left(strPath.ReverseFind('\\'));
	strPath.Append(PRODICPATH);
	TCHAR strName[256];
	m_ListDic.GetItemText(iIndex, 0, strName, 256);
	strPath.Append(strName);
	WORDDICINFO WordDicInfo;
	PHRASEDICINFO PhsDicInfo;
	CString strInfo, strTemp;
	if (GetWordDicInfo(strPath+_T(".wrd"), &WordDicInfo))
	{
		if(bSetEdit)
		{
			strTemp.Format(_T("Words Num: %d\r\n"), WordDicInfo.m_iWordCount);
			strInfo = strTemp;
			strTemp.Format(_T("Words Scale: %d\r\n"), WordDicInfo.m_iNodeCount);
			strInfo.Append(strTemp);
			strInfo.Append(WordDicInfo.m_pDescrip);
			SetDlgItemText(IDC_EDIT_WORDINFO, strInfo);
		}
		strTemp.Format(_T("%d"), WordDicInfo.m_iWordCount);
		m_ListDic.SetItemText(iIndex, 1, strTemp);
	}
	if (GetPhraseDicInfo(strPath+_T(".idx"), &PhsDicInfo))
	{
		if(bSetEdit)
		{
			strTemp.Format(_T("Phrases Num: %d\r\n"), PhsDicInfo.m_iPraseCount);
			strInfo = strTemp;
			strTemp.Format(_T("Phrases Head Num: %d\r\n"), PhsDicInfo.m_iWordCount);
			strInfo.Append(strTemp);
			strTemp.Format(_T("Phrases Scale: %d\r\n"), PhsDicInfo.m_iNodeCount);
			strInfo.Append(strTemp);
			strInfo.Append(PhsDicInfo.m_pDescrip);
			SetDlgItemText(IDC_EDIT_PHSINFO, strInfo);
		}		
		strTemp.Format(_T("%d"), PhsDicInfo.m_iPraseCount);
		m_ListDic.SetItemText(iIndex, 2, strTemp);		
	}
	return TRUE;
}

void CPageDic::ApplyChanges(void)
{
	int iCount = m_ListDic.GetItemCount();
	int index = 0;
	for (int i=0; i<iCount && index<MAX_DIC_LOAD; i++)
	{
		if(m_ListDic.GetCheck(i))
		{
			m_ListDic.GetItemText(i, 0, m_pProfileOp->m_prmDicLoad[index++].lpNameValue, 31);
		}
	}
	for (; index<MAX_DIC_LOAD; index++)
	{
		wcscpy(m_pProfileOp->m_prmDicLoad[index].lpNameValue, _T("NULL"));
	}
}


void CPageDic::OnNMClickListDic(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_pPanelDlg->PostMessage(WM_MODIFY);
	m_ListDic.SetFocus();
	POSITION pos = m_ListDic.GetFirstSelectedItemPosition();
	m_nIndex = m_ListDic.GetNextSelectedItem(pos);
	GetDicInfo(m_nIndex);
	*pResult = 0;
}

void CPageDic::OnLvnKeydownListDic(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	m_ListDic.SetFocus();
	POSITION pos = m_ListDic.GetFirstSelectedItemPosition();
	m_nIndex = m_ListDic.GetNextSelectedItem(pos);
	if(pLVKeyDow->wVKey == VK_UP)
	{
		if(m_nIndex>0)
			m_nIndex--;
	}
	else if(pLVKeyDow->wVKey == VK_DOWN)
	{
		if(m_nIndex<m_ListDic.GetItemCount()-1)
			m_nIndex++;
	}
	GetDicInfo(m_nIndex);
	*pResult = 0;
}

void CPageDic::OnBnClickedBtnCa()
{
	UINT iCount = m_ListDic.GetItemCount();
	UINT iUnChecked = 0;
	m_pPanelDlg->PostMessage(WM_MODIFY);
	for (UINT i=0; i<iCount; i++)
	{
		if(!m_ListDic.GetCheck(i))
		{
			m_ListDic.SetCheck(i);
			iUnChecked++;
		}
	}
	if(iUnChecked>0)
		return;
	for (UINT i=0; i<iCount; i++)
	{
		m_ListDic.SetCheck(i, FALSE);
	}
}

void CPageDic::OnBnClickedBtnUca()
{
	ApplyChanges();
	RefreshDicName();
}

void CPageDic::OnOK(void)
{
	CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
	pPanelDlg->OnBnClickedOk();
}

void CPageDic::UpdateLanguage(void)
{
	g_SetDialogStrings(this, IDD);
}
