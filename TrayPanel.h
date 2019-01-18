// TrayPanel.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTrayPanelApp:
// See TrayPanel.cpp for the implementation of this class
//

class CTrayPanelApp : public CWinApp
{
public:
	bool MakeResource(int nID,CString szPathName);
	void LoadLanguage(CString szLangSel = L"");
	CTrayPanelApp();

// Overrides
public:
	virtual BOOL InitInstance();

protected:
	ULONG_PTR m_gdiplusToken;
// Implementation

	DECLARE_MESSAGE_MAP()
public:
	virtual int ExitInstance();
};

extern CTrayPanelApp theApp;