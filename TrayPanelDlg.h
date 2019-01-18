// TrayPanelDlg.h : header file

#pragma once

#include "KeyProcess.h"
#include "TabSheet.h"
#include "PageMain.h"
#include "PageAdvanced.h"
#include "PageDic.h"
#include "PageAbout.h"
#include "ProfileOp.h"
#include "PageTrans.h"
#include "PageSuggest.h"
#include "PageKey.h"
#include "ColorTheme.h"

CString g_LoadString(CString szID);
void g_SetDialogStrings(CDialog *pDlg,UINT uDlgID);

extern CString g_szCurPath;
extern CString g_szSettingPath;	//保存设置的文件路径
extern CString g_szLanguagePath;	//保存语言文件的路径
// CTrayPanelDlg dialog
class CTrayPanelDlg : public CDialog
{
// Construction
public:
	CTrayPanelDlg(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	enum { IDD = IDD_TRAYPANEL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnHookMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnHookCBTMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnHookIMEMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnModified(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTipNotify(WPARAM WPARAM, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	BOOL InstallHook(HWND hWnd);
	BOOL ReLoadAllDic(void);
	void UnloadHook();
	afx_msg void OnBnClickedOk();
	BOOL SetSysHotKey(UINT mf, UINT vk);
	afx_msg void OnPopupEnable();
	afx_msg void OnPopupCompatible();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	void ToTray(void);
	virtual BOOL DestroyWindow();
	void BoolNotify(CString strInfo);
	NOTIFYICONDATA nid;
	bool IsHookOn;
	CProfileOp m_ProfileOp;
	CColorTheme m_ColorTheme;
	CCompWindow& pCompWnd;
	BOOL bEnableDic;
	CTabSheet m_sheet;

private:
	CKeyProcess m_KeyProcess;
	CMenu m_muPopup;
	afx_msg void OnPopupExit();
	afx_msg void OnPopupShow();
	HMODULE m_hHKDll;
	HWND m_hwndTarget;
	CPageMain m_PageMain;
	ATOM m_iHotKeyID;
	ATOM m_app;
	CPageAdvanced m_PageAdvanced;
	CPageAbout m_PageAbout;
	CPageDic m_PageDic;
	CPageTrans m_PageTrans;
	CPageSuggest m_PageSuggest;
	CPageKey m_PageKey;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedApply();
	void InitColorTheme(void);
	void RestoreCoreParam();

protected:
	BOOL m_bShowWndForAll;
	BOOL m_bEnableModify;
	BOOL m_bAutoLearnLoaded;
public:
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
public:
	afx_msg void OnBnClickedHelp();
public:
	void UpdateLanguage(void);
public:
	void UpdateAllLan(void);
};
