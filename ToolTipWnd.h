#pragma once


// CToolTipWnd

class CToolTipWnd : public CWnd
{
	DECLARE_DYNAMIC(CToolTipWnd)

public:
	CToolTipWnd(CWnd *pCompWnd);
	void SetTranslationString(WCHAR *pTransStr);
	virtual ~CToolTipWnd();
	BOOL Create();
	void ShowWnd(BOOL show);

protected:
	CWnd *m_pCompWnd;
	HWND m_hCompWnd;
	WCHAR m_strTrans[512];
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
public:
	void InformCompWndPos(LPRECT LPCompRect, int iCandTop, int iCandHeight);
};


