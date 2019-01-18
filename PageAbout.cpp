// PageAbout.cpp : implementation file
//

#include "stdafx.h"
#include "TrayPanel.h"
#include "PageAbout.h"
#include "TriiviCore.h"
#include "TrayPanelDlg.h"
// CPageAbout dialog

IMPLEMENT_DYNAMIC(CPageAbout, CDialog)

CPageAbout::CPageAbout(CWnd* pParent /*=NULL*/)
	: CDialog(CPageAbout::IDD, pParent)
{

}

CPageAbout::~CPageAbout()
{
}

void CPageAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageAbout, CDialog)

//	ON_BN_CLICKED(IDC_BUTTON1, &CPageAbout::OnBnClickedButton1)
END_MESSAGE_MAP()


// CPageAbout message handlers
BOOL CPageAbout::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_EDIT_ABOUT,
		_T("Triivi is a brand new conception of English typing.\r\n\
This 2.0 professional version contains more than 700,000 words and phrases.\r\n\
You can simply type several letters of a word, and then Triivi will note you with the most common used words and phrases.\r\n\
Press TAB or number key to complete a word/phrase.\r\n\
Pleased give us your precious advices. And our Website is www.Triivi.com.\r\n\
\r\n\
GUI Ver      \t2.0 pro.\r\n\
CORE Ver     \t1.5 beta.\r\n\
Programmer   \tKatsu, Comabob."));
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPageAbout::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if(wParam==2)
		return m_pPanelDlg->PostMessage(WM_COMMAND, wParam, lParam);
	return CDialog::OnCommand(wParam, lParam);
}


void CPageAbout::OnOK()
{
}

//void CPageAbout::OnBnClickedButton1()
//{
//	((CTrayPanelApp*)AfxGetApp())->LoadLanguage(_T("CHS"));
//	g_SetDialogStrings(this,IDD);
//}

void CPageAbout::UpdateLanguage(void)
{
	g_SetDialogStrings(this, IDD);
}
