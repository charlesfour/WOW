#pragma once
#include "afxwin.h"


// CPageAbout dialog

class CPageAbout : public CDialog
{
	DECLARE_DYNAMIC(CPageAbout)

public:
	CPageAbout(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPageAbout();

// Dialog Data
	enum { IDD = IDD_DLG_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	CDialog *m_pPanelDlg;
public:
	//afx_msg void OnBnClickedButtonReg();
public:
	//CStatic m_Picture;
public:
	//afx_msg void OnBnClickedButtonGetsn();
public:
//	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
protected:
	virtual void OnOK();
public:
//	afx_msg void OnBnClickedButton1();
public:
	void UpdateLanguage(void);
};
