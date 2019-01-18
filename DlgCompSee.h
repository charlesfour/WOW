#pragma once


// CDlgCompSee dialog

class CDlgCompSee : public CDialog
{
	DECLARE_DYNAMIC(CDlgCompSee)

public:
	CDlgCompSee(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgCompSee();

// Dialog Data
	enum { IDD = IDD_DLG_COMPSEE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	Color m_clShadow;
	Color m_clMargin;
	Color m_clHotText;
	Color m_clCommonText;
	Color m_clBack1;
	Color m_clBack2;
	Color m_clFrame;

public:
	afx_msg void OnPaint();
};

