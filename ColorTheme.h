#pragma once
#include <gdipluscolor.h>


struct COMPTHEMECOLOR
{
	Color m_ShadowColor;
	Color m_MarginColor;
	Color m_HotTextColor;
	Color m_CommonTextColor;
	Color m_BackColor1;
	Color m_BackColor2;
	Color m_FrameColor;
	TCHAR m_strName[32];
};

class CColorTheme
{
public:
	CColorTheme(void);
	~CColorTheme(void);
	BOOL GetThemeName(UINT iIndex, LPTSTR lpName);
	void AddColorTheme(Color clShadow, 
		Color clMargin, 
		Color clHotText, 
		Color clCommon, 
		Color clBack1,
		Color clBack2,
		Color clFrame,
		TCHAR* pstrName);
	BOOL GetColorTheme(TCHAR* pstrName, 
		Color* pclShadow, 
		Color* pclMargin, 
		Color* pclHotText, 
		Color* pclCommon,
		Color* pclBack1,
		Color* pclBack2,
		Color* clFrame);
	BOOL GetColorTheme(UINT iIndex, 
		Color* pclShadow, 
		Color* pclMargin, 
		Color* pclHotText, 
		Color* pclCommon,
		Color* pclBack1,
		Color* pclBack2,
		Color* clFrame);
	UINT GetThemeNum();

protected:
	COMPTHEMECOLOR *m_pCompColor;
	UINT m_NumOfTheme;
};
