#pragma once
#include "CompWindow.h"
#define VK_USER_SHIFT 0x0100

typedef struct _tagKEYDATALPARAM
{
	UINT32 RepeatCount		: 16;
	UINT32 ScanCode			: 8;
	UINT32 IsExtended		: 1;
	UINT32 Researved		: 4;
	UINT32 ALTDown			: 1;
	UINT32 PreviousState	: 1;
	UINT32 BeingReleased	: 1;
} KEYSTATE, *LPKEYSTATE;

typedef struct _tagCONTROLSTATE
{
	BYTE CtrlPressed		: 1;
	BYTE AltPressed			: 1;
	BYTE ShiftPressed		: 1;
	BYTE CapsLocked			: 1;
	BYTE NumLocked			: 1;
	BYTE RCtrlPressed		: 1;
	BYTE RAltPressed		: 1;
	BYTE RShiftPressed		: 1;
} CONTROLSTATE, *LPCONTROLSTATE;

class CKeyProcess
{
public:
	CKeyProcess();
	~CKeyProcess(void);
	LRESULT ProcessKey(HWND hTargetWnd, POINT pt, WPARAM wParam, LPARAM lParam, BOOL IsEditCtrl);
	bool IsKeyWanted(WPARAM vk);//the key presses we should pay attention to
	bool IsKeyChar(WPARAM vk); //a-z
	bool IsKeyDigit(WPARAM vk); //0-9
	bool IsKeyFunctional(WPARAM vk);//tab,space,backspace,enter,esc
	bool IsKeyJoint(WPARAM vk); // '.' ,'-','\''

	void LocateCompWnd(void);//to set the upper-left corner point of the comp wnd
	void EvalCharSize(HWND target);

	//void  
private:
	void SendChar(UINT Msg,WPARAM wParam, LPARAM lParam);
	bool CharInput(WPARAM wParam, LPARAM lParam); //return shouldIKillTheMsg ?
public:
	HWND m_hTargetWnd;
	POINT m_CaretPos;
private:
	
//	HWND m_hParentWnd;
	CCompWindow & pComWnd;
//	HINSTANCE m_hParentInst;
	BOOL m_bShiftJustPressed;
	CONTROLSTATE m_ControlState;	
protected:
	bool KeyFunction(UINT kf);
};
