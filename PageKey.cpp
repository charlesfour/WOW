// PageKey.cpp : implementation file
//

#include "stdafx.h"
#include "TrayPanel.h"
#include "PageKey.h"
#include "TrayPanelDlg.h"

// CPageKey dialog

IMPLEMENT_DYNAMIC(CPageKey, CDialog)

CPageKey::CPageKey(CWnd* pParent /*=NULL*/)
	: CDialog(CPageKey::IDD, pParent)
{

}

CPageKey::~CPageKey()
{
}

void CPageKey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageKey, CDialog)
//	ON_BN_CLICKED(IDC_RADIO4, &CPageKey::OnBnClickedRadio4)
ON_WM_SHOWWINDOW()
ON_CBN_SELCHANGE(IDC_COMBO_TAB, &CPageKey::OnCbnSelchange)
ON_CBN_SELCHANGE(IDC_COMBO_ENTER, &CPageKey::OnCbnSelchange)
ON_CBN_SELCHANGE(IDC_COMBO_SHIFT, &CPageKey::OnCbnSelchange)
ON_CBN_SELCHANGE(IDC_COMBO_USER_VK, &CPageKey::OnCbnSelchange)
ON_CBN_SELCHANGE(IDC_COMBO_USER_KF, &CPageKey::OnCbnSelchange)
ON_BN_CLICKED(IDC_RADIO_SUB1, &CPageKey::OnBnClickedRadio)
ON_BN_CLICKED(IDC_RADIO_SUB2, &CPageKey::OnBnClickedRadio)
ON_BN_CLICKED(IDC_RADIO_SUB3, &CPageKey::OnBnClickedRadio)
ON_BN_CLICKED(IDC_RADIO_BRA1, &CPageKey::OnBnClickedRadio)
ON_BN_CLICKED(IDC_RADIO_BRA2, &CPageKey::OnBnClickedRadio)
ON_BN_CLICKED(IDC_RADIO_BRA3, &CPageKey::OnBnClickedRadio)
ON_BN_CLICKED(IDC_RADIO_TRADITIONAL, &CPageKey::OnBnClickedRadio)
ON_BN_CLICKED(IDC_RADIO_EXPRESS, &CPageKey::OnBnClickedRadio)
ON_BN_CLICKED(IDC_CHECK_NEEDSPACE, &CPageKey::OnBnClickedRadio)
ON_BN_CLICKED(IDC_CHECK_INTER, &CPageKey::OnBnClickedRadio)

END_MESSAGE_MAP()


BOOL CPageKey::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if(wParam==2)
		return m_pPanelDlg->PostMessage(WM_COMMAND, wParam, lParam);
	return CDialog::OnCommand(wParam, lParam);
}

BOOL CPageKey::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_pPanelDlg = (CDialog*)(GetParent()->GetParent());
	return TRUE;  
}

void CPageKey::OnOK()
{
	CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
	pPanelDlg->OnBnClickedOk();
}

void CPageKey::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
	if(bShow)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_TAB))->SetCurSel(pPanelDlg->m_ProfileOp.m_prmTabFunction.iValue);
		((CComboBox*)GetDlgItem(IDC_COMBO_ENTER))->SetCurSel(pPanelDlg->m_ProfileOp.m_prmReturnFunction.iValue);
		((CComboBox*)GetDlgItem(IDC_COMBO_SHIFT))->SetCurSel(pPanelDlg->m_ProfileOp.m_prmShiftFunction.iValue);
		((CComboBox*)GetDlgItem(IDC_COMBO_USER_VK))->SetCurSel(pPanelDlg->m_ProfileOp.m_prmUserVK.iValue);
		((CComboBox*)GetDlgItem(IDC_COMBO_USER_KF))->SetCurSel(pPanelDlg->m_ProfileOp.m_prmUserFunction.iValue);

		((CButton*)GetDlgItem(IDC_RADIO_SUB1))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_SUB2))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_SUB3))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_BRA1))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_BRA2))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_BRA3))->SetCheck(FALSE);
		switch(pPanelDlg->m_ProfileOp.m_prmSubFunction.iValue)
		{
		case KF_PASS:
			((CButton*)GetDlgItem(IDC_RADIO_SUB1))->SetCheck(TRUE);
			break;
		case KF_ARROW:
			((CButton*)GetDlgItem(IDC_RADIO_SUB2))->SetCheck(TRUE);
			break;
		case KF_PAGE:
			((CButton*)GetDlgItem(IDC_RADIO_SUB3))->SetCheck(TRUE);
			break;
		default:
			((CButton*)GetDlgItem(IDC_RADIO_SUB1))->SetCheck(TRUE);
			break;
		}
		switch(pPanelDlg->m_ProfileOp.m_prmBraFunction.iValue)
		{
		case KF_PASS:
			((CButton*)GetDlgItem(IDC_RADIO_BRA1))->SetCheck(TRUE);
			break;
		case KF_ARROW:
			((CButton*)GetDlgItem(IDC_RADIO_BRA2))->SetCheck(TRUE);
			break;
		case KF_PAGE:
			((CButton*)GetDlgItem(IDC_RADIO_BRA3))->SetCheck(TRUE);
			break;
		default:
			((CButton*)GetDlgItem(IDC_RADIO_BRA1))->SetCheck(TRUE);
			break;
		}

		if(pPanelDlg->m_ProfileOp.m_prmInputMode.iValue==0)
		{
			((CButton*)GetDlgItem(IDC_RADIO_TRADITIONAL))->SetCheck(TRUE);
			((CButton*)GetDlgItem(IDC_RADIO_EXPRESS))->SetCheck(FALSE);
			pPanelDlg->pCompWnd.m_bEditInPlace=false;
		}
		else
		{
			((CButton*)GetDlgItem(IDC_RADIO_EXPRESS))->SetCheck(TRUE);
			((CButton*)GetDlgItem(IDC_RADIO_TRADITIONAL))->SetCheck(FALSE);
			pPanelDlg->pCompWnd.m_bEditInPlace=true;
		}

		if(pPanelDlg->m_ProfileOp.m_prmAutoAddSpace.iValue==0)
			((CButton*)GetDlgItem(IDC_CHECK_NEEDSPACE))->SetCheck(FALSE);
		else
			((CButton*)GetDlgItem(IDC_CHECK_NEEDSPACE))->SetCheck(TRUE);

		if(pPanelDlg->m_ProfileOp.m_prmCompleteInter.iValue==0)
			((CButton*)GetDlgItem(IDC_CHECK_INTER))->SetCheck(FALSE);
		else
			((CButton*)GetDlgItem(IDC_CHECK_INTER))->SetCheck(TRUE);
	}
}

void CPageKey::DlgOK(void)
{
	CTrayPanelDlg *pPanelDlg = (CTrayPanelDlg*)m_pPanelDlg;
	pPanelDlg->m_ProfileOp.m_prmTabFunction.iValue = ((CComboBox*)GetDlgItem(IDC_COMBO_TAB))->GetCurSel();
	pPanelDlg->m_ProfileOp.m_prmReturnFunction.iValue = ((CComboBox*)GetDlgItem(IDC_COMBO_ENTER))->GetCurSel();
	pPanelDlg->m_ProfileOp.m_prmUserVK.iValue = ((CComboBox*)GetDlgItem(IDC_COMBO_USER_VK))->GetCurSel();
	pPanelDlg->m_ProfileOp.m_prmUserFunction.iValue = ((CComboBox*)GetDlgItem(IDC_COMBO_USER_KF))->GetCurSel();
	pPanelDlg->m_ProfileOp.m_prmShiftFunction.iValue = ((CComboBox*)GetDlgItem(IDC_COMBO_SHIFT))->GetCurSel();

	if(((CButton*)GetDlgItem(IDC_RADIO_SUB1))->GetCheck())
		pPanelDlg->m_ProfileOp.m_prmSubFunction.iValue = KF_PASS;
	else if(((CButton*)GetDlgItem(IDC_RADIO_SUB2))->GetCheck())
		pPanelDlg->m_ProfileOp.m_prmSubFunction.iValue = KF_ARROW;
	else if(((CButton*)GetDlgItem(IDC_RADIO_SUB3))->GetCheck())
		pPanelDlg->m_ProfileOp.m_prmSubFunction.iValue = KF_PAGE;

	if(((CButton*)GetDlgItem(IDC_RADIO_BRA1))->GetCheck())
		pPanelDlg->m_ProfileOp.m_prmBraFunction.iValue = KF_PASS;
	else if(((CButton*)GetDlgItem(IDC_RADIO_BRA2))->GetCheck())
		pPanelDlg->m_ProfileOp.m_prmBraFunction.iValue = KF_ARROW;
	else if(((CButton*)GetDlgItem(IDC_RADIO_BRA3))->GetCheck())
		pPanelDlg->m_ProfileOp.m_prmBraFunction.iValue = KF_PAGE;

	if(((CButton*)GetDlgItem(IDC_RADIO_TRADITIONAL))->GetCheck())
	{
		pPanelDlg->m_ProfileOp.m_prmInputMode.iValue = 0;
		pPanelDlg->pCompWnd.m_bEditInPlace = false;
	}
	else
	{
		pPanelDlg->m_ProfileOp.m_prmInputMode.iValue = 1;
		pPanelDlg->pCompWnd.m_bEditInPlace = true;
	}

	if(((CButton*)GetDlgItem(IDC_CHECK_NEEDSPACE))->GetCheck())
		pPanelDlg->m_ProfileOp.m_prmAutoAddSpace.iValue = 1;
	else
		pPanelDlg->m_ProfileOp.m_prmAutoAddSpace.iValue = 0;

	if(((CButton*)GetDlgItem(IDC_CHECK_INTER))->GetCheck())
		pPanelDlg->m_ProfileOp.m_prmCompleteInter.iValue = 1;
	else
		pPanelDlg->m_ProfileOp.m_prmCompleteInter.iValue = 0;
}

void CPageKey::OnCbnSelchange()
{
	m_pPanelDlg->PostMessage(WM_MODIFY);
}

void CPageKey::OnBnClickedRadio()
{
	m_pPanelDlg->PostMessage(WM_MODIFY);
}

void CPageKey::UpdateLanguage(void)
{
	g_SetDialogStrings(this, IDD);
}
