#include "stdafx.h"
#include "ColorTheme.h"

CColorTheme::CColorTheme(void)
{
	m_NumOfTheme = 0;
	m_pCompColor = NULL;
}

CColorTheme::~CColorTheme(void)
{
	if (m_pCompColor!=NULL)
	{
		free(m_pCompColor);
	}
}

void CColorTheme::AddColorTheme(Color clShadow, 
				   Color clMargin, 
				   Color clHotText, 
				   Color clCommon,
				   Color clBack1,
				   Color clBack2,
				   Color clFrame,
				   TCHAR* pstrName)
{
	UINT iIndex = m_NumOfTheme;
	m_NumOfTheme++;
	m_pCompColor = (COMPTHEMECOLOR*)realloc(m_pCompColor, 
		m_NumOfTheme*sizeof(COMPTHEMECOLOR));
	(m_pCompColor+iIndex)->m_ShadowColor = clShadow;
	(m_pCompColor+iIndex)->m_MarginColor = clMargin;
	(m_pCompColor+iIndex)->m_HotTextColor = clHotText;
	(m_pCompColor+iIndex)->m_CommonTextColor = clCommon;
	(m_pCompColor+iIndex)->m_BackColor1 = clBack1;
	(m_pCompColor+iIndex)->m_BackColor2 = clBack2;
	(m_pCompColor+iIndex)->m_FrameColor = clFrame;
	wcscpy((m_pCompColor+iIndex)->m_strName, pstrName);
}

BOOL CColorTheme::GetColorTheme(TCHAR* pstrName, 
				   Color* pclShadow, 
				   Color* pclMargin, 
				   Color* pclHotText, 
				   Color* pclCommon,
				   Color* pclBack1,
				   Color* pclBack2,
				   Color* pclFrame)
{
	BOOL bRet = FALSE;
	for(UINT i=0; i<m_NumOfTheme; i++)
	{
		if(0 == wcscmp(pstrName, (m_pCompColor+i)->m_strName))
		{
			bRet = TRUE;
			*pclShadow = (m_pCompColor+i)->m_ShadowColor;
			*pclMargin = (m_pCompColor+i)->m_MarginColor;
			*pclHotText = (m_pCompColor+i)->m_HotTextColor;
			*pclCommon = (m_pCompColor+i)->m_CommonTextColor;
			*pclBack1 = (m_pCompColor+i)->m_BackColor1;
			*pclBack2 = (m_pCompColor+i)->m_BackColor2;
			*pclFrame = (m_pCompColor+i)->m_FrameColor;
			break;
		}
	}
	return bRet;
}

BOOL CColorTheme::GetColorTheme(UINT iIndex, 
				   Color* pclShadow, 
				   Color* pclMargin, 
				   Color* pclHotText, 
				   Color* pclCommon,
				   Color* pclBack1,
				   Color* pclBack2,
				   Color* pclFrame)
{
	if(iIndex<m_NumOfTheme)
	{
		*pclShadow = (m_pCompColor+iIndex)->m_ShadowColor;
		*pclMargin = (m_pCompColor+iIndex)->m_MarginColor;
		*pclHotText = (m_pCompColor+iIndex)->m_HotTextColor;
		*pclCommon = (m_pCompColor+iIndex)->m_CommonTextColor;
		*pclBack1 = (m_pCompColor+iIndex)->m_BackColor1;
		*pclBack2 = (m_pCompColor+iIndex)->m_BackColor2;
		*pclFrame = (m_pCompColor+iIndex)->m_FrameColor;
		return TRUE;
	}
	else 
		return FALSE;
}

UINT CColorTheme::GetThemeNum()
{
	return m_NumOfTheme;
}

BOOL CColorTheme::GetThemeName(UINT iIndex, LPTSTR lpName)
{
	BOOL bRet = FALSE;
	if (iIndex<m_NumOfTheme)
	{
		bRet = TRUE;
		wcscpy(lpName, (m_pCompColor+iIndex)->m_strName);
	}
	return bRet;
}