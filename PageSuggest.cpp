// PageSuggest.cpp : implementation file
//

#include "stdafx.h"
#include "TrayPanel.h"
#include "PageSuggest.h"
#include "TrayPanelDlg.h"

// CPageSuggest dialog

IMPLEMENT_DYNAMIC(CPageSuggest, CDialog)

CPageSuggest::CPageSuggest(CWnd* pParent /*=NULL*/)
	: CDialog(CPageSuggest::IDD, pParent)
{

}

CPageSuggest::~CPageSuggest()
{
}

void CPageSuggest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageSuggest, CDialog)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_EC, &CPageSuggest::OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PC, &CPageSuggest::OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_ECMAX, &CPageSuggest::OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PCMAX, &CPageSuggest::OnDeltaposSpin)
	ON_BN_CLICKED(IDC_CHECK_EC, &CPageSuggest::OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_PC, &CPageSuggest::OnBnClickedCheck)
END_MESSAGE_MAP()


// CPageSuggest message handlers

void CPageSuggest::OnOK()
{
	CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
	pPanelDlg->OnBnClickedOk();
}

void CPageSuggest::DlgOK()
{
	CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
	CProfileOp *pProfileOp = &pPanelDlg->m_ProfileOp;
	pProfileOp->m_prmEnableErrorCheck.iValue = ((CButton*)GetDlgItem(IDC_CHECK_EC))->GetCheck();
	pProfileOp->m_prmEnablePronunCheck.iValue = ((CButton*)GetDlgItem(IDC_CHECK_PC))->GetCheck();
	UINT iNum = GetDlgItemInt(IDC_EDIT_ECMAX);
	if(iNum>=pProfileOp->m_prmECMaxHint.iMin && iNum<=pProfileOp->m_prmECMaxHint.iMax)
		pProfileOp->m_prmECMaxHint.iValue = iNum;
	iNum = GetDlgItemInt(IDC_EDIT_PCMAX);
	if(iNum>=pProfileOp->m_prmPCMaxHint.iMin && iNum<=pProfileOp->m_prmPCMaxHint.iMax)
		pProfileOp->m_prmPCMaxHint.iValue = iNum;
	iNum = GetDlgItemInt(IDC_EDIT_EC);
	if(iNum>=pProfileOp->m_prmStartECNum.iMin && iNum<=pProfileOp->m_prmStartECNum.iMax)
		pProfileOp->m_prmStartECNum.iValue = iNum;
	iNum = GetDlgItemInt(IDC_EDIT_PC);
	if(iNum>=pProfileOp->m_prmStartPCNum.iMin && iNum<=pProfileOp->m_prmStartPCNum.iMax)
		pProfileOp->m_prmStartPCNum.iValue = iNum;
}

BOOL CPageSuggest::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_pPanelDlg = (CDialog*)(GetParent()->GetParent());
	CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
	CProfileOp *pProfileOp = &pPanelDlg->m_ProfileOp;
	((CButton*)GetDlgItem(IDC_CHECK_EC))->SetCheck(pProfileOp->m_prmEnableErrorCheck.iValue);
	((CButton*)GetDlgItem(IDC_CHECK_PC))->SetCheck(pProfileOp->m_prmEnablePronunCheck.iValue);
	SetDlgItemInt(IDC_EDIT_ECMAX, pProfileOp->m_prmECMaxHint.iValue);
	SetDlgItemInt(IDC_EDIT_PCMAX, pProfileOp->m_prmPCMaxHint.iValue);
	SetDlgItemInt(IDC_EDIT_EC, pProfileOp->m_prmStartECNum.iValue);
	SetDlgItemInt(IDC_EDIT_PC, pProfileOp->m_prmStartPCNum.iValue);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPageSuggest::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if(wParam==2)
		return m_pPanelDlg->PostMessage(WM_COMMAND, wParam, lParam);
	return CDialog::OnCommand(wParam, lParam);
}

void CPageSuggest::OnDeltaposSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
	CProfileOp *pProfileOp = &pPanelDlg->m_ProfileOp;
	UINT iData;
	switch(pNMHDR->idFrom)
	{
	case IDC_SPIN_EC:
		iData = GetDlgItemInt(IDC_EDIT_EC);
		iData-=pNMUpDown->iDelta;
		if(iData<pProfileOp->m_prmStartECNum.iMin)
			iData = pProfileOp->m_prmStartECNum.iMin;
		else if(iData>pProfileOp->m_prmStartECNum.iMax)
			iData = pProfileOp->m_prmStartECNum.iMax;
		SetDlgItemInt(IDC_EDIT_EC, iData);
		break;
	case IDC_SPIN_PC:
		iData = GetDlgItemInt(IDC_EDIT_PC);
		iData-=pNMUpDown->iDelta;
		if(iData<pProfileOp->m_prmStartPCNum.iMin)
			iData = pProfileOp->m_prmStartPCNum.iMin;
		else if(iData>pProfileOp->m_prmStartPCNum.iMax)
			iData = pProfileOp->m_prmStartPCNum.iMax;
		SetDlgItemInt(IDC_EDIT_PC, iData);
		break;
	case IDC_SPIN_ECMAX:
		iData = GetDlgItemInt(IDC_EDIT_ECMAX);
		iData-=pNMUpDown->iDelta;
		if(iData<pProfileOp->m_prmECMaxHint.iMin)
			iData = pProfileOp->m_prmECMaxHint.iMin;
		else if(iData>pProfileOp->m_prmECMaxHint.iMax)
			iData = pProfileOp->m_prmECMaxHint.iMax;
		SetDlgItemInt(IDC_EDIT_ECMAX, iData);
		break;
	case IDC_SPIN_PCMAX:
		iData = GetDlgItemInt(IDC_EDIT_PCMAX);
		iData-=pNMUpDown->iDelta;
		if(iData<pProfileOp->m_prmPCMaxHint.iMin)
			iData = pProfileOp->m_prmPCMaxHint.iMin;
		else if(iData>pProfileOp->m_prmPCMaxHint.iMax)
			iData = pProfileOp->m_prmPCMaxHint.iMax;
		SetDlgItemInt(IDC_EDIT_PCMAX, iData);
		break;
	}
	pPanelDlg->PostMessage(WM_MODIFY);
	*pResult = 0;
}

void CPageSuggest::OnBnClickedCheck()
{
	m_pPanelDlg->PostMessage(WM_MODIFY);
}	

void CPageSuggest::UpdateLanguage(void)
{
	g_SetDialogStrings(this, IDD);
}
