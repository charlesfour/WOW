#pragma once


// CPageKey dialog

class CPageKey : public CDialog
{
	DECLARE_DYNAMIC(CPageKey)

public:
	CPageKey(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPageKey();

// Dialog Data
	enum { IDD = IDD_DLG_KEY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedRadio4();
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
protected:
	CDialog *m_pPanelDlg;
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
public:
	void DlgOK(void);
public:
	afx_msg void OnCbnSelchange();
	afx_msg void OnBnClickedRadio();
public:
	void UpdateLanguage(void);
};
