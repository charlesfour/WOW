#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "ProfileOp.h"

// CPageDic dialog

class CPageDic : public CDialog
{
	DECLARE_DYNAMIC(CPageDic)

public:
	CPageDic(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPageDic();

// Dialog Data
	enum { IDD = IDD_DLG_DIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	void InitListBox(void);
	CListCtrl m_ListDic;
protected:
	int m_nIndex;
	CWnd *m_pPanelDlg;
	CFont m_font;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnBnClickedBtnGetworddic();
	afx_msg void OnBnClickedBtnUp();
	afx_msg void OnBnClickedBtnDown();
	afx_msg void OnNMDblclkListDic(NMHDR *pNMHDR, LRESULT *pResult);
public:
	void RefreshDicName(void);

protected:
	CProfileOp* m_pProfileOp;
public:
	BOOL GetDicInfo(int iIndex, BOOL bSetEdit=TRUE);
public:
	void ApplyChanges(void);

public:
	afx_msg void OnNMClickListDic(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnLvnKeydownListDic(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnBnClickedBtnCa();
public:
	afx_msg void OnBnClickedBtnUca();
public:
	void OnOK(void);
public:
	void UpdateLanguage(void);
};
