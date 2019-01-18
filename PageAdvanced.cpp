// PageAdvanced.cpp : implementation file
//

#include "stdafx.h"
#include "TrayPanel.h"
#include "PageAdvanced.h"
#include "ProfileOp.h"
#include "TrayPanelDlg.h"

// CPageAdvanced dialog

IMPLEMENT_DYNAMIC(CPageAdvanced, CDialog)

CPageAdvanced::CPageAdvanced(CWnd* pParent /*=NULL*/)
	: CDialog(CPageAdvanced::IDD, pParent)
	, m_iHideWordBelow(0)
	, m_iStartHintLetter(0)
{

}

CPageAdvanced::~CPageAdvanced()
{
}

void CPageAdvanced::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLI_WORDNUM, m_sliWordNum);
	DDX_Control(pDX, IDC_SLI_PHRASENUM, m_sliPhraseNum);
	DDX_Control(pDX, IDC_SLI_WORDCACHE, m_sliWordCache);
	DDX_Control(pDX, IDC_SLI_PHRASESORT, m_sliPhraseSortDepth);
	DDX_Text(pDX, IDC_EDIT_HIDE, m_iHideWordBelow);
	DDV_MinMaxUInt(pDX, m_iHideWordBelow, 0, 8);
	DDX_Text(pDX, IDC_EDIT_START, m_iStartHintLetter);
	DDV_MinMaxInt(pDX, m_iStartHintLetter, 1, 8);
}


BEGIN_MESSAGE_MAP(CPageAdvanced, CDialog)
//	ON_BN_CLICKED(IDC_BUTTON1, &CPageAdvanced::OnBnClickedButton1)
//ON_NOTIFY(NM_THEMECHANGED, IDC_SCR_MAXWORDNUM, &CPageAdvanced::OnNMThemeChangedScrMaxwordnum)
ON_WM_HSCROLL()
//ON_WM_PAINT()
ON_WM_SHOWWINDOW()
ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_HIDE, &CPageAdvanced::OnDeltaposSpinHide)
ON_BN_CLICKED(IDC_CHECK_ENTRANS, &CPageAdvanced::OnBnClickedCheckEntrans)
ON_BN_CLICKED(IDC_CHECK_UNMATCH, &CPageAdvanced::OnBnClickedCheckUnmatch)
ON_BN_CLICKED(IDC_CHECK_PROPHONLY, &CPageAdvanced::OnBnClickedCheckUnmatch)
ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_START, &CPageAdvanced::OnDeltaposSpinStart)
END_MESSAGE_MAP()


BOOL CPageAdvanced::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	if(wParam==2)
		return m_pPanelDlg->PostMessage(WM_COMMAND, wParam, lParam);
	return CDialog::OnCommand(wParam, lParam);
}

BOOL CPageAdvanced::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_pPanelDlg = (CDialog*)(GetParent()->GetParent());
	CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
	CProfileOp *pProfileOp = &pPanelDlg->m_ProfileOp;

	m_sliWordNum.SetRange(pProfileOp->m_prmWordHintNum.iMin,
		pProfileOp->m_prmWordHintNum.iMax);
	m_sliWordNum.SetPos(pProfileOp->m_prmWordHintNum.iValue);
	SetDlgItemInt(IDC_EDIT_WORDNUM, m_sliWordNum.GetPos());
	m_sliPhraseNum.SetRange(pProfileOp->m_prmPhraseHintNum.iMin,
		pProfileOp->m_prmPhraseHintNum.iMax);
	m_sliPhraseNum.SetPos(pProfileOp->m_prmPhraseHintNum.iValue);
	SetDlgItemInt(IDC_EDIT_PHRASENUM, m_sliPhraseNum.GetPos());
	m_sliWordCache.SetRange(pProfileOp->m_prmMaxWordLearn.iMin,
		pProfileOp->m_prmMaxWordLearn.iMax);
	m_sliWordCache.SetPos(pProfileOp->m_prmMaxWordLearn.iValue);
	SetDlgItemInt(IDC_EDIT_WORDCACHE, m_sliWordCache.GetPos());
	m_sliPhraseSortDepth.SetRange(pProfileOp->m_prmMaxPhraseSort.iMin,
		pProfileOp->m_prmMaxPhraseSort.iMax);
	m_sliPhraseSortDepth.SetPos(pProfileOp->m_prmMaxPhraseSort.iValue);
	SetDlgItemInt(IDC_EDIT_PHRASESORT, m_sliPhraseSortDepth.GetPos());
	((CButton*)GetDlgItem(IDC_CHECK_ENTRANS))->SetCheck(pProfileOp->m_prmEnableTranslation.iValue);
	((CButton*)GetDlgItem(IDC_CHECK_UNMATCH))->SetCheck(pProfileOp->m_prmShowUnmatched.iValue);
	((CButton*)GetDlgItem(IDC_CHECK_PROPHONLY))->SetCheck(pProfileOp->m_prmProPhraseOnly.iValue);
	if(pProfileOp->m_prmEnableTranslation.iValue==0)
		GetDlgItem(IDC_CHECK_UNMATCH)->EnableWindow(FALSE);
	else
		GetDlgItem(IDC_CHECK_UNMATCH)->EnableWindow(TRUE);
	m_iHideWordBelow = pProfileOp->m_prmHideWordBelow.iValue;
	m_iStartHintLetter = pProfileOp->m_prmStartHintLetter.iValue;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CPageAdvanced::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
	if(pScrollBar == (CScrollBar*)&m_sliWordNum)
	{
		SetDlgItemInt(IDC_EDIT_WORDNUM, m_sliWordNum.GetPos());
	}
	else if (pScrollBar == (CScrollBar*)&m_sliPhraseNum)
	{
		SetDlgItemInt(IDC_EDIT_PHRASENUM, m_sliPhraseNum.GetPos());
	}
	else if(pScrollBar == (CScrollBar*)&m_sliWordCache)
	{
		SetDlgItemInt(IDC_EDIT_WORDCACHE, m_sliWordCache.GetPos());
	}
	else if(pScrollBar == (CScrollBar*)&m_sliPhraseSortDepth)
	{
		SetDlgItemInt(IDC_EDIT_PHRASESORT, m_sliPhraseSortDepth.GetPos());
	}
	m_pPanelDlg->PostMessage(WM_MODIFY);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CPageAdvanced::DlgOK()
{
	TRIICOREPARAM CoreParam;
	GetParam(&CoreParam);
	CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
	CProfileOp *pProfileOp = &pPanelDlg->m_ProfileOp;
	pProfileOp->m_prmWordHintNum.iValue = m_sliWordNum.GetPos();
	pProfileOp->m_prmPhraseHintNum.iValue = m_sliPhraseNum.GetPos();
	pProfileOp->m_prmMaxWordLearn.iValue = m_sliWordCache.GetPos();
	pProfileOp->m_prmMaxPhraseSort.iValue = m_sliPhraseSortDepth.GetPos();
	pProfileOp->m_prmHideWordBelow.iValue = m_iHideWordBelow;
	pProfileOp->m_prmStartHintLetter.iValue = m_iStartHintLetter;
	pProfileOp->m_prmEnableTranslation.iValue = ((CButton*)GetDlgItem(IDC_CHECK_ENTRANS))->GetCheck();
	pProfileOp->m_prmShowUnmatched.iValue = ((CButton*)GetDlgItem(IDC_CHECK_UNMATCH))->GetCheck();
	pProfileOp->m_prmProPhraseOnly.iValue = ((CButton*)GetDlgItem(IDC_CHECK_PROPHONLY))->GetCheck();
	CoreParam.m_iMaxAutoLearnWords =  m_sliWordCache.GetPos();
	CoreParam.m_iMaxPhraseSort = m_sliPhraseSortDepth.GetPos();
	CoreParam.m_iHideWordBelow = m_iHideWordBelow;
	SetParam(&CoreParam);
}


void CPageAdvanced::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
		CProfileOp *pProfileOp = &pPanelDlg->m_ProfileOp;

		m_sliWordNum.SetPos(pProfileOp->m_prmWordHintNum.iValue);
		SetDlgItemInt(IDC_EDIT_WORDNUM, m_sliWordNum.GetPos());
		m_sliPhraseNum.SetPos(pProfileOp->m_prmPhraseHintNum.iValue);
		SetDlgItemInt(IDC_EDIT_PHRASENUM, m_sliPhraseNum.GetPos());
	}
}

void CPageAdvanced::OnDeltaposSpinHide(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	if(pNMHDR->idFrom == IDC_SPIN_HIDE)
	{
		CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
		CProfileOp *pProfileOp = &pPanelDlg->m_ProfileOp;
		m_iHideWordBelow-=pNMUpDown->iDelta;
		if(m_iHideWordBelow<0)
			m_iHideWordBelow = 0;
		else if((UINT)m_iHideWordBelow<pProfileOp->m_prmHideWordBelow.iMin)
			m_iHideWordBelow = pProfileOp->m_prmHideWordBelow.iMin;
		else if((UINT)m_iHideWordBelow>pProfileOp->m_prmHideWordBelow.iMax)
			m_iHideWordBelow = pProfileOp->m_prmHideWordBelow.iMax;
		UpdateData(FALSE);
		pPanelDlg->PostMessage(WM_MODIFY);
	}
	*pResult = 0;
}

void CPageAdvanced::OnBnClickedCheckEntrans()
{
	m_pPanelDlg->PostMessage(WM_MODIFY);
	if (((CButton*)GetDlgItem(IDC_CHECK_ENTRANS))->GetCheck())
	{
		((CButton*)GetDlgItem(IDC_CHECK_UNMATCH))->EnableWindow(TRUE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_UNMATCH))->EnableWindow(FALSE);
	}
}

void CPageAdvanced::OnBnClickedCheckUnmatch()
{
	m_pPanelDlg->PostMessage(WM_MODIFY);
}

void CPageAdvanced::OnDeltaposSpinStart(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	if(pNMHDR->idFrom == IDC_SPIN_START)
	{
		CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
		CProfileOp *pProfileOp = &pPanelDlg->m_ProfileOp;
		m_iStartHintLetter-=pNMUpDown->iDelta;
		if(m_iStartHintLetter<1)
			m_iStartHintLetter = 1;
		else if((UINT)m_iStartHintLetter<pProfileOp->m_prmStartHintLetter.iMin)
			m_iStartHintLetter = pProfileOp->m_prmStartHintLetter.iMin;
		else if((UINT)m_iStartHintLetter>pProfileOp->m_prmStartHintLetter.iMax)
			m_iStartHintLetter = pProfileOp->m_prmStartHintLetter.iMax;
		UpdateData(FALSE);
		pPanelDlg->PostMessage(WM_MODIFY);
	}
	*pResult = 0;
}

void CPageAdvanced::OnOK(void)
{
	CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
	pPanelDlg->OnBnClickedOk();
}

void CPageAdvanced::UpdateLanguage(void)
{
	g_SetDialogStrings(this, IDD);
}
