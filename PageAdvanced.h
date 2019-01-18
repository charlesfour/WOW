#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPageAdvanced dialog

class CPageAdvanced : public CDialog
{
	DECLARE_DYNAMIC(CPageAdvanced)

public:
	CPageAdvanced(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPageAdvanced();

// Dialog Data
	enum { IDD = IDD_DLG_ADVANCED };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	CDialog* m_pPanelDlg;
public:
	virtual BOOL OnInitDialog();
	void DlgOK();

public:
	CSliderCtrl m_sliWordNum;
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
public:
	CSliderCtrl m_sliPhraseNum;
public:
//	afx_msg void OnPaint();
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
public:
	CSliderCtrl m_sliWordCache;
public:
	CSliderCtrl m_sliPhraseSortDepth;
public:
	afx_msg void OnDeltaposSpinHide(NMHDR *pNMHDR, LRESULT *pResult);
public:
	INT m_iHideWordBelow;
public:
	afx_msg void OnBnClickedCheckEntrans();
public:
	afx_msg void OnBnClickedCheckUnmatch();
public:
	afx_msg void OnDeltaposSpinStart(NMHDR *pNMHDR, LRESULT *pResult);
public:
	UINT m_iStartHintLetter;
public:
	void OnOK(void);
public:
	void UpdateLanguage(void);
};
