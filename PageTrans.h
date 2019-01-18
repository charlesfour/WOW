#pragma once
#include "afxcmn.h"
#include "ProfileOp.h"

// CPageTrans dialog

class CPageTrans : public CDialog
{
	DECLARE_DYNAMIC(CPageTrans)

public:
	CPageTrans(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPageTrans();

// Dialog Data
	enum { IDD = IDD_DLG_TRANS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	CListCtrl m_ListTrans;
	virtual BOOL OnInitDialog();

protected:
	CWnd *m_pPanelDlg;
	CProfileOp *m_pProfileOp;
	CFont m_font;
	int m_nIndex;
public:
	void InitListBox(void);
public:
	void RefreshDicName(void);
public:
	afx_msg void OnBnClickedBtnUp();
public:
	afx_msg void OnBnClickedBtnDown();
public:
	BOOL GetDicInfo(int iIndex, BOOL bShow);
	afx_msg void OnNMDblclkListTrans(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListTrans(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnCa();
	afx_msg void OnBnClickedBtnUca();
	void ApplyChanges(void);
public:
	afx_msg void OnLvnKeydownListTrans(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnBnClickedBtnGetworddic();
public:
	void OnOK(void);
public:
	void UpdateLanguage(void);
};
