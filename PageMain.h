#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ColorTheme.h"
#include "DlgCompSee.h"

// CPageMain dialog

class CPageMain : public CDialog
{
	DECLARE_DYNAMIC(CPageMain)

public:
	CPageMain(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPageMain();

// Dialog Data
	enum { IDD = IDD_DLG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL SetAutoRun(CString strPath, BOOL bEnable=TRUE);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckEnable();
//	afx_msg void OnPaint();
	CHotKeyCtrl m_hkHotKey;
	
	void Setuphk();
private:
	CDialog *m_pPanelDlg;
	void FillFontList();
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	void DlgOK(void);
public:
	afx_msg void OnBnClickedAutorun();
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
public:
	afx_msg void OnCbnSelchange();
public:
	CColorTheme *m_pColorTheme;
	CDlgCompSee m_dlgCompSee; 
public:
	CComboBox m_cbTheme;
public:
	afx_msg void OnCbnSelchangeTheme();
public:
	CComboBox m_cbFont;
public:
	afx_msg void OnEnChangeEditFontsize();
public:
	void OnOK(void);
public:
	CComboBox m_cbClear;
public:
	afx_msg void OnDeltaposSpinFont(NMHDR *pNMHDR, LRESULT *pResult);
public:
	void UpdateLanguage(void);
	void ListLanguage(void);
public:
	CComboBox m_cbLanguage;
public:
	afx_msg void OnCbnSelchangeComboLan();
};
