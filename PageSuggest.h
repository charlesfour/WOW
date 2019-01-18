#pragma once


// CPageSuggest dialog

class CPageSuggest : public CDialog
{
	DECLARE_DYNAMIC(CPageSuggest)

public:
	CPageSuggest(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPageSuggest();

// Dialog Data
	enum { IDD = IDD_DLG_SUGGESTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	void DlgOK();
	virtual BOOL OnInitDialog();
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
protected:
	CDialog *m_pPanelDlg;
public:
	afx_msg void OnDeltaposSpin(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnBnClickedCheck();
public:
	void UpdateLanguage(void);
};
