#pragma once
//#define _UNICODE
#include "TriiviCore.h"
#include "ToolTipWnd.h"
#include "ProfileOp.h"
#include "XInfoTip.h"


#define TOOL_BASE_ID 10000
#pragma comment (lib, "TriiviCore.lib")

//void PaintCompWindow(HWND);

class CCompWindow : public CWnd
{
private: //yeah, private,but you can manage the ONLY ONE object of this class by Instance
		//inherit is forbidden from this class
	CCompWindow();

public:
	~CCompWindow();
public:
	static CCompWindow & Instance();
	BOOL m_bNeedSpace;
	afx_msg void OnPaint();
	afx_msg void OnTranslation(NMHDR* pnmh, LRESULT* pResult);// notify from tooltip,need translation

	//FreeInstance();

	//friend LRESULT WINAPI CompWndProc(HWND   hWnd,UINT   message,WPARAM wParam,LPARAM lParam);
	bool IsBufNull();
	bool IsActive();
	bool IsNeedShow();
	bool IsBufEndWithSpace();
	void SetTargetWnd(HWND targetWnd);
	HWND GetTargetWnd();
	void SetWndPos(UINT x,UINT y);
	void SelectItem(UINT i); //i=1-9,0  ,0 will turned to 10 in the processing
	//append a 'char',aA..zZ
	void AppendChar(char charCode);
	void Backspace(void);//delete the lastest char in buf
	//condidate list select/move
	void FlushToTarget(bool bStep = false, bool IsUpperCase = false);
	void FlushTyped(void); //needed when !m_bEditInPlace
	void cursorUp(INT times=1);
	void cursorDown(INT times=1);
	void PageUP(void);
	void PageDown(void);
	void ShowWnd(bool show);
	void SetFont(LPCTSTR lpFontName, REAL iSize, INT iStyle, Unit unit);
	friend class TransTipCtrl;

private:
	void ResizeCompWindow(void);
	void CalcWindowWidth(Graphics *pG, Font *pFont);
	UINT UpdateDicBuf();//search in Dic by szInputBuf
	BOOL InitWindow();
	void CreateCompWindow(void);
	UINT GetWndHeight();
	UINT GetWndWidth();
	void EndOneCompletion();
	void MouseMoveToItem(int i); //i:[1 2 ... 10]
	void FormatTransBuf();
	void FormatTransWidth();
	//TCHAR m_lpFontName[128];
	//REAL m_iFontSize;
	//INT m_iFontStyle;
	//Unit m_uFontUnit;

private:
	
	//HWND m_hCompWnd;//itself's handle
	HWND m_hTargetWnd;//handle to the target edit control
	//HWND m_hParentWnd;//handle to the traypanel
	POINT m_ptPos; //upperleft point
	//window 's states
	UINT m_uiLeftMargin;
	UINT m_uiUpperMargin;
	UINT m_uiItemHeight;
	UINT m_uiCharWidth;
	UINT m_wndWidth;
	CToolTipWnd *pToolTipWnd;
	CXInfoTip m_tip;
	Image *m_pPNGMark;
	
public:
	Color m_clShadow;
	Color m_clMargin;
	Color m_clHotText;
	Color m_clCommonText;
	Color m_clBack1;
	Color m_clBack2;
	Color m_clFrame;

	BOOL m_bNeedSpecialBack;
	UINT m_TargetCharHeight;
	UINT m_TargetCharWidth;
	UINT m_uiScreenCX;//screen size
	UINT m_uiScreenCY;
	CProfileOp *m_pProfileOp;
	bool m_bEditInPlace;//false:do not send the chars to target before make a selection

private:
	static const int BUFLEN=128;
	static const int DICBUFSIZE=128;
	bool  isActive;
	bool  isNeedShow;//isActive is a subset states of in Insession,
	//when flushed,the wnd is Not active(not showed on screen),but still in a session
	bool lockPos;//lock the wnd's position
	bool lockHot;
	char szInputBuf[BUFLEN*2];//store the current buffered chars
	TCHAR transBuf[2048]; //store result for translation   
	INT m_iInputPosition;//current index in input buf,start from 0,point to the last char
	INT m_iCompStartPos; //current index in input buf,point to the start position of the str searched in the dic
	char * pszDicBuf[DICBUFSIZE];//candidates from dictionary
	UINT m_uiCurrentSelectedIndex; //which condidate is selected(global id in retrived set),start from 1
	UINT m_uiStartIndex;//candidate from this id to (id+9) will be listed in the window 
	UINT m_uiECStartIndex;//after(include) this index(start from 1),candidates are EC result ,so need special treat when flushed
	UINT m_uiPCStartIndex;

public:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	void SetFontParam(LPCTSTR strFontName, int iFontSize, int iFontStyle);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


