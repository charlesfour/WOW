// ToolTipWnd.cpp : implementation file
//

#include "stdafx.h"
#include "TrayPanel.h"
#include "ToolTipWnd.h"


// CToolTipWnd

IMPLEMENT_DYNAMIC(CToolTipWnd, CWnd)

CToolTipWnd::CToolTipWnd(CWnd *pCompWnd)
{
	m_pCompWnd = pCompWnd;
}

CToolTipWnd::~CToolTipWnd()
{
}

void CToolTipWnd::SetTranslationString(WCHAR *pTransStr)
{
	if(wcslen(pTransStr)<511)
		wcscpy(m_strTrans, pTransStr);
	else
		wcscpy(m_strTrans, L"Translation data is too long!");
}

BOOL CToolTipWnd::Create() 
{

	LPCTSTR szWndClass;
	szWndClass = AfxRegisterWndClass(
		CS_VREDRAW | CS_HREDRAW | CS_GLOBALCLASS,
		::LoadCursor(NULL, IDC_ARROW),
		(HBRUSH) ::GetStockObject(WHITE_BRUSH),
		NULL);

	BOOL bRet = CWnd::CreateEx(NULL, szWndClass, NULL,
		WS_POPUP, 0, 0, 100, 100,
		m_pCompWnd->GetSafeHwnd(), NULL, NULL);

	m_hCompWnd = m_pCompWnd->GetSafeHwnd();
	if(bRet)
		SetOwner(m_pCompWnd);
	return bRet;
}
BEGIN_MESSAGE_MAP(CToolTipWnd, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CToolTipWnd message handlers

void CToolTipWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rectCl;
	GetClientRect(&rectCl);

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0,0,244));

	dc.DrawText(m_strTrans, rectCl, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}

void CToolTipWnd::ShowWnd(BOOL show)
{
	ShowWindow(show?SW_SHOWNOACTIVATE:SW_HIDE);
}

void CToolTipWnd::InformCompWndPos(LPRECT LPCompRect, int iCandTop, int iCandHeight)
{
	RECT rt;
	memcpy(&rt, LPCompRect, sizeof(RECT));
	rt.left+=200;
	rt.right+=200;
	MoveWindow(&rt);
}
