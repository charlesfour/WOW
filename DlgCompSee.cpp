// DlgCompSee.cpp : implementation file
//

#include "stdafx.h"
#include "TrayPanel.h"
#include "DlgCompSee.h"
#include "TrayPanelDlg.h"
#include "PageMain.h"

// CDlgCompSee dialog

IMPLEMENT_DYNAMIC(CDlgCompSee, CDialog)

CDlgCompSee::CDlgCompSee(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCompSee::IDD, pParent)
{

}

CDlgCompSee::~CDlgCompSee()
{
}

void CDlgCompSee::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgCompSee, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgCompSee message handlers

void CDlgCompSee::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CPageMain* pPageMain = (CPageMain*)GetParent();
	UINT iTheme = pPageMain->m_cbTheme.GetCurSel();
	BOOL bShadow = ((CButton*)(pPageMain->GetDlgItem(IDC_CHECK_SHADOW)))->GetCheck();
	pPageMain->m_pColorTheme->GetColorTheme(iTheme,
		&m_clShadow, &m_clMargin, &m_clHotText, &m_clCommonText, &m_clBack1, &m_clBack2, &m_clFrame);
	CRect ClientRect;
	GetClientRect(&ClientRect);
	CSize ClientSize(ClientRect.Width(),ClientRect.Height());
	RectF theRect((REAL)ClientRect.left,
		(REAL)ClientRect.top,
		(REAL)ClientRect.Width(),
		(REAL)ClientRect.Height());
	PointF textPos;
	LinearGradientBrush b(theRect, m_clBack1, m_clBack2,90.0f);
	Graphics g(dc.m_hDC);
	g.Clear(Color(255,255,255,255));
	g.SetInterpolationMode(InterpolationModeHighQualityBicubic);
	g.SetTextRenderingHint((TextRenderingHint)pPageMain->m_cbClear.GetCurSel());
	g.FillRectangle(&b,theRect);
	g.DrawRectangle(&Pen(m_clFrame, 2), theRect);
	char strText[5][16] = {"1 .  great", 
		"2 .  gentlemen", "3 .  general",
		"4 .  given", "5 .  give"};
	textPos.X = (REAL)ClientRect.left + 20;
	textPos.Y = (REAL)ClientRect.top + 5;
	SolidBrush *pBrush;
	SolidBrush brushHot(m_clHotText);
	SolidBrush brushCommon(m_clCommonText);
	SolidBrush brushShadow(m_clShadow);
	TCHAR lpFontName[32];
	pPageMain->m_cbFont.GetWindowText(lpFontName, 32);
	FontFamily  fontFamily(lpFontName);
	INT iStyle = FontStyleRegular;
	if(((CButton*)(pPageMain->GetDlgItem(IDC_CHECK_BOLD)))->GetCheck())
		iStyle = FontStyleBold;
	if(((CButton*)(pPageMain->GetDlgItem(IDC_CHECK_ITALIC)))->GetCheck())
		iStyle |= FontStyleItalic;
	UINT iFontSize = pPageMain->GetDlgItemInt(IDC_EDIT_FONTSIZE);
	Font font(&fontFamily, (REAL)iFontSize, iStyle, UnitPixel);	
	for (UINT i=0; i<5; i++)
	{
		if(bShadow)
		{
			textPos.X++;
			textPos.Y++;
			g.DrawString(CString(strText[i]), strlen(strText[i]), &font, textPos, &brushShadow);
			textPos.X--;
			textPos.Y--;
		}
		if(i==GetTickCount()%5)
		{
			pBrush = &brushHot;
			g.DrawLine(&Pen(m_clMargin, 1), textPos.X, textPos.Y+font.GetHeight(&g)+2, (REAL)ClientRect.right-15, textPos.Y+font.GetHeight(&g)+2);
		}
		else
			pBrush = &brushCommon;
		
		g.DrawString(CString(strText[i]), strlen(strText[i]), &font, textPos, pBrush);
		textPos.Y+=font.GetHeight(&g)+1;
	}
	
}
