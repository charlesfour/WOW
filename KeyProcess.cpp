#include "StdAfx.h"
#include "KeyProcess.h"
#include <iostream>
#include "msword9.h"
#include "msppt.h"

CKeyProcess::CKeyProcess()
:pComWnd(CCompWindow::Instance())
{
	m_hTargetWnd = NULL;
	//	m_hParentInst = NULL;
	//	m_hParentWnd = parentWnd;
	//pComWnd=CCompWindow::Instance();

	*(BYTE*)&m_ControlState = 0;
	m_ControlState.CapsLocked = GetKeyState(20);
}

CKeyProcess::~CKeyProcess(void)
{
}
//////////////////////////////////////////
bool CKeyProcess::IsKeyChar(WPARAM vk) //a-z
{
	return (vk>='A' && vk<='Z');
}
///////////////////////////////////////////
bool CKeyProcess::IsKeyDigit(WPARAM vk) //0-9
{
	return (vk>='0' && vk<='9')||(vk>=VK_NUMPAD0 && vk<=VK_NUMPAD9);
}
//////////////////////////////////////////
bool CKeyProcess::IsKeyFunctional(WPARAM vk)//tab,space,backspace,enter,esc,pagedown/up,arrowdown/up
{
	if(pComWnd.m_pProfileOp->m_prmCompleteInter.iValue)
	{
		if(vk==VK_OEM_COMMA || vk==VK_OEM_PERIOD || vk==VK_OEM_1 ||
			vk==VK_OEM_2 || (vk=='1'&&m_ControlState.ShiftPressed))
			return true;
	}
	if(pComWnd.m_pProfileOp->m_prmSubFunction.iValue>0)
		if(vk==VK_OEM_MINUS || vk==VK_OEM_PLUS)	// + -
			return true;
	if(pComWnd.m_pProfileOp->m_prmBraFunction.iValue>0)
		if(vk==VK_OEM_4 || vk==VK_OEM_6)	// [ ]
			return true;
	if(vk==VK_TAB||vk==VK_SPACE||vk==VK_BACK||vk==VK_RETURN||vk==VK_ESCAPE||vk==VK_SHIFT
		||vk==VK_PRIOR||vk==VK_NEXT||vk==VK_UP||vk==VK_DOWN||vk==VK_CAPITAL||vk==VK_USER_SHIFT
		||vk==VK_LEFT||vk==VK_RIGHT)//||vk==250)
		return true;
	else 
		return false;
}
///////////////////////////////////////////
bool CKeyProcess::IsKeyJoint(WPARAM vk) // '.' ,'-','\''
{
	if(vk==VK_OEM_MINUS||vk==VK_OEM_7)//||vk==VK_OEM_PERIOD
		return true;
	else 
		return false;
}
////////////////////////////////////////////
bool CKeyProcess::IsKeyWanted(WPARAM vk)
{
	if(IsKeyChar(vk)||IsKeyDigit(vk)||IsKeyFunctional(vk)||IsKeyJoint(vk))
		return true;
	else
		return false;
}
///////////////////////////////////////////
LRESULT CKeyProcess::ProcessKey(HWND hTargetWnd, POINT pt, WPARAM wParam, LPARAM lParam, BOOL IsEditCtrl)
{
	BOOL bCaptured = FALSE;
	UINT Msg=0; 
	m_CaretPos = pt;

	if(hTargetWnd!=pComWnd.m_hWnd)
		m_hTargetWnd = hTargetWnd;

	KEYSTATE KeyState;
	memcpy(&KeyState, &lParam, sizeof(UINT32));
	//now to dertermine the msg type for this key msg,and update stat

	if(KeyState.PreviousState == 1 && KeyState.BeingReleased == 1)	// Key up message
	{															//all KEYUP will be post to target
		Msg = WM_KEYUP;

		if (wParam == VK_CONTROL)
		{
			m_ControlState.CtrlPressed = 0;
		}
		else if (wParam == VK_SHIFT)
		{
			if(m_bShiftJustPressed)
			{
				m_bShiftJustPressed = FALSE;
				SendChar(WM_KEYDOWN, VK_USER_SHIFT, lParam);
			}
			m_ControlState.ShiftPressed = 0;
		}
		else if (wParam == VK_CAPITAL)
		{
			m_ControlState.CapsLocked = GetKeyState(20);
		}
	}

	else if (KeyState.PreviousState == 1 && KeyState.BeingReleased == 0) // Key hold message
	{																	//
		Msg = WM_KEYDOWN;
	}

	else if (KeyState.PreviousState == 0 && KeyState.BeingReleased == 0) //key stroke down
	{
		Msg = WM_KEYDOWN;
		m_bShiftJustPressed = FALSE;
		if (m_ControlState.CtrlPressed==0)//(m_ControlState.CtrlPressed|m_ControlState.ShiftPressed) == 0)
		{
			if (wParam == VK_CONTROL)
			{
				m_ControlState.CtrlPressed = 1;
			}
			else if (wParam == VK_SHIFT)
			{
				m_bShiftJustPressed = TRUE;
				m_ControlState.ShiftPressed = 1;
			}
			else if (wParam == VK_CAPITAL)
			{
				m_ControlState.CapsLocked = GetKeyState(20);
			}
		}
	}

	else
		Msg=0; //unkown key state change
	//end of msg analyse
	//deal with the msg
	if(((Msg==WM_KEYDOWN)&&IsEditCtrl&&!m_ControlState.CtrlPressed) )//|| wParam==250)
	{
		EvalCharSize(m_hTargetWnd);
		if(IsKeyWanted(wParam))
		{
			SendChar(Msg, wParam, lParam);
			bCaptured = TRUE;
		}
		else //if(!pComWnd.IsBufNull())
			if(pComWnd.m_bEditInPlace)
			pComWnd.SetTargetWnd(NULL);//is a key we don't need,so clear buf
			else
			{ //send the special keychar to minibuf if !m_bEditInPlace
				SendChar(Msg, wParam, lParam);
				bCaptured = TRUE;
			}
	}

	if((bCaptured == FALSE) && (Msg!=0))
	{
		if( pComWnd.m_bEditInPlace?true:!pComWnd.IsActive())
		PostMessage(m_hTargetWnd, Msg, wParam, lParam);  //all key up messages go through here
	}
	//else routed to SendChar
	return 0L; 
}

////////////////////////////////////////////////////////
void CKeyProcess::SendChar(UINT Msg, WPARAM wParam, LPARAM lParam) //determine how to process the key msg
{
	bool killMsg=false;
	bool isActive=pComWnd.IsActive();//store the status before CharInput
	//if comWnd is not active and this is not a Char msg,don't foward the keymsg to it
	if(pComWnd.m_bEditInPlace)
	{
		if(pComWnd.IsActive()||IsKeyChar(wParam)||wParam==VK_BACK||wParam==VK_SPACE)//||wParam==250)  //backspace is a special char,so it can start a session
			killMsg=CharInput(wParam, lParam); // be consumed in the comWnd ?
		else if(!pComWnd.IsBufNull())
			pComWnd.SetTargetWnd(NULL);
	}
	else
	{
		if(pComWnd.IsActive()||IsKeyChar(wParam))//||wParam==250)  //backspace is a special char,so it can start a session
			killMsg=CharInput(wParam, lParam); // be consumed in the comWnd ?
		else if(!pComWnd.IsBufNull())
			pComWnd.SetTargetWnd(NULL);
	}


	if(!killMsg)
	{
		if( pComWnd.m_bEditInPlace)
		PostMessage(m_hTargetWnd, Msg, wParam, lParam);  //key down messages go where they should go now
		else if(!isActive && !IsKeyChar(wParam))
		PostMessage(m_hTargetWnd, Msg, wParam, lParam);
	}
}

bool CKeyProcess::CharInput(WPARAM wParam, LPARAM lParam)
{
	bool killMsg=false;//the message shouldn't go ahead to the target
	bool isUpperCase=m_ControlState.CapsLocked != m_ControlState.ShiftPressed;
	bool userMF = m_ControlState.ShiftPressed;
	if(IsKeyChar(wParam))  //real char
	{
		killMsg=false;
		pComWnd.SetTargetWnd(m_hTargetWnd);
		LocateCompWnd();
		if(m_ControlState.CapsLocked==m_ControlState.ShiftPressed)
			pComWnd.AppendChar(char(wParam+'a'-'A'));     //append lowercase char regardless of shift/cap states
		else
			pComWnd.AppendChar(char(wParam));
	}
	else if(IsKeyDigit(wParam)&&!isUpperCase) //num
	{
		killMsg=true;
		if(wParam<='9')
			pComWnd.SelectItem(wParam-'0');
		else
			pComWnd.SelectItem(wParam-VK_NUMPAD0);  //key press in num pad
	}
	else if(IsKeyFunctional(wParam))
	{
		switch(wParam)
		{
		case VK_USER_SHIFT:
			killMsg = KeyFunction(pComWnd.m_pProfileOp->m_prmShiftFunction.iValue);
			break;

		case VK_TAB:
			if (userMF && (pComWnd.m_pProfileOp->m_prmUserVK.iValue==0))
				killMsg = KeyFunction(pComWnd.m_pProfileOp->m_prmUserFunction.iValue+1);
			else
				killMsg = KeyFunction(pComWnd.m_pProfileOp->m_prmTabFunction.iValue);
			break;

		case VK_RETURN:
			if (userMF && (pComWnd.m_pProfileOp->m_prmUserVK.iValue==1))
				killMsg = KeyFunction(pComWnd.m_pProfileOp->m_prmUserFunction.iValue+1);
			else
				killMsg = KeyFunction(pComWnd.m_pProfileOp->m_prmReturnFunction.iValue);
			break;

		case VK_SPACE:
			if(!pComWnd.IsBufNull()) //already in INPUT state
			{
				if(pComWnd.IsBufEndWithSpace()) //i'd want to be feeded with too much SPACE
				{
					pComWnd.FlushToTarget();
					killMsg=true;
				}
				else //ok,but just one
				{
					pComWnd.SetTargetWnd(m_hTargetWnd);
					LocateCompWnd();
					pComWnd.AppendChar(' ');
					killMsg=false;
				}
			}//end of case space
			break;

		case VK_ESCAPE:
			pComWnd.SetTargetWnd(NULL);//it's just a trick,but is useful here
			killMsg=true;
			break;

		case VK_BACK: //backspace
			pComWnd.Backspace();
			killMsg=false;
			break;

		case VK_UP:
			pComWnd.cursorUp();
			killMsg=true;
			break;

		case VK_DOWN:
			pComWnd.cursorDown();
			killMsg=true;
			break;

		case VK_PRIOR: //page up
		case VK_LEFT:
			pComWnd.PageUP();
			killMsg=true;
			break;

		case VK_NEXT: //page down
		case VK_RIGHT:
			pComWnd.PageDown();
			killMsg=true;
			break;

		case VK_OEM_MINUS:		// -
			if(pComWnd.m_pProfileOp->m_prmSubFunction.iValue == KF_ARROW)
				pComWnd.cursorUp();
			else if(pComWnd.m_pProfileOp->m_prmSubFunction.iValue == KF_PAGE)
				pComWnd.PageUP();
			killMsg=true;
			break;

		case VK_OEM_PLUS:		// +
			if(pComWnd.m_pProfileOp->m_prmSubFunction.iValue == KF_ARROW)
				pComWnd.cursorDown();
			else if(pComWnd.m_pProfileOp->m_prmSubFunction.iValue == KF_PAGE)
				pComWnd.PageDown();
			killMsg=true;
			break;

		case VK_OEM_4:			// [
			if(pComWnd.m_pProfileOp->m_prmBraFunction.iValue == KF_ARROW)
				pComWnd.cursorUp();
			else if(pComWnd.m_pProfileOp->m_prmBraFunction.iValue == KF_PAGE)
				pComWnd.PageUP();
			killMsg=true;
			break;

		case VK_OEM_6:			// ]
			if(pComWnd.m_pProfileOp->m_prmBraFunction.iValue == KF_ARROW)
				pComWnd.cursorDown();
			else if(pComWnd.m_pProfileOp->m_prmBraFunction.iValue == KF_PAGE)
				pComWnd.PageDown();
			killMsg=true;
			break;


		case VK_OEM_COMMA:
			pComWnd.m_bNeedSpace = FALSE;
			KeyFunction(KF_COMPLETE);
			killMsg = true;
			pComWnd.SetTargetWnd(NULL);
			::PostMessage(m_hTargetWnd, WM_CHAR, ',', 1);
			::PostMessage(m_hTargetWnd, WM_CHAR, ' ', 1);
			break;

		case VK_OEM_PERIOD:
			pComWnd.m_bNeedSpace = FALSE;
			KeyFunction(KF_COMPLETE);
			killMsg = true;
			pComWnd.SetTargetWnd(NULL);
			::PostMessage(m_hTargetWnd, WM_CHAR, '.', 1);
			::PostMessage(m_hTargetWnd, WM_CHAR, ' ', 1);
			break;
	
		case VK_OEM_1:	// ; :
			pComWnd.m_bNeedSpace = FALSE;
			KeyFunction(KF_COMPLETE);
			killMsg = true;
			pComWnd.SetTargetWnd(NULL);
			if(m_ControlState.ShiftPressed)
				::PostMessage(m_hTargetWnd, WM_CHAR, ':', 1);
			else
				::PostMessage(m_hTargetWnd, WM_CHAR, ';', 1);
			::PostMessage(m_hTargetWnd, WM_CHAR, ' ', 1);
			break;

		case VK_OEM_2:	// ? /
			pComWnd.m_bNeedSpace = FALSE;
			KeyFunction(KF_COMPLETE);
			killMsg = true;
			pComWnd.SetTargetWnd(NULL);
			if(m_ControlState.ShiftPressed)
			{
				::PostMessage(m_hTargetWnd, WM_CHAR, '?', 1);
				::PostMessage(m_hTargetWnd, WM_CHAR, ' ', 1);
			}
			else
				::PostMessage(m_hTargetWnd, WM_CHAR, '/', 1);
			break;

		case '1':
			pComWnd.m_bNeedSpace = FALSE;
			KeyFunction(KF_COMPLETE);
			killMsg = true;
			pComWnd.SetTargetWnd(NULL);
			::PostMessage(m_hTargetWnd, WM_CHAR, '!', 1);
			::PostMessage(m_hTargetWnd, WM_CHAR, ' ', 1);
			break;

		default:
			killMsg=false;

		}// end of switch
	}//end of else if(IsKeyFunctional(wParam))
	else if(IsKeyJoint(wParam)&&!isUpperCase)
	{
		pComWnd.SetTargetWnd(m_hTargetWnd);
		LocateCompWnd();
		if(wParam==VK_OEM_MINUS)//--------
			pComWnd.AppendChar('-');

		//else if(wParam==VK_OEM_PERIOD)//........
		//pComWnd.AppendChar('.');

		else if(wParam==VK_OEM_7)//'''''''''''
			pComWnd.AppendChar('\'');

		killMsg=false;

	}
	else
	{//buf is polluted 
		if(pComWnd.m_bEditInPlace)
		pComWnd.SetTargetWnd(NULL);
		else
		{ //for further usage,you can send special char such as *&$ to the minibuf
			
			killMsg=true;
			//pComWnd.SetTargetWnd(m_hTargetWnd);
			//LocateCompWnd();
			//if(m_ControlState.CapsLocked==m_ControlState.ShiftPressed)
			//	pComWnd.AppendChar(char(wParam+'a'-'A'));     //append lowercase char regardless of shift/cap states
			//else
				//pComWnd.AppendChar(char(wParam));
		}
	}

	return killMsg;
}//end of function

bool CKeyProcess::KeyFunction(UINT kf)
{
	bool killMsg = false;
	switch(kf)
	{
	case KF_NOTHING:
		if(!pComWnd.m_bEditInPlace)
		{
			pComWnd.FlushTyped();
			killMsg=true;
		}
		else
		{
			pComWnd.SetTargetWnd(NULL);
			killMsg=false;
		}
		break;
	case KF_COMPLETE:
		pComWnd.FlushToTarget();
		killMsg=true;
		break;
	case KF_STEPCOMPLETE:		// temporary equal to complete
		pComWnd.FlushToTarget(true);
		killMsg=true;
		break;
	default:
		pComWnd.SetTargetWnd(NULL);
		killMsg = false;
	}
	return killMsg;
}
void CKeyProcess::LocateCompWnd(void)
{
	if(m_hTargetWnd!=NULL)
	{
		//get new target font info
		CWnd * targetW=CWnd::FromHandle(m_hTargetWnd);
		CFont * font=targetW->GetFont();//WORD will return null here
		LOGFONT lf;
		if(font!=NULL)
		{
			font->GetLogFont(&lf);
			pComWnd.m_TargetCharHeight=abs(lf.lfHeight);
		}
		else
		{
			char clsName[256];
			GetClassNameA(m_hTargetWnd, clsName, 256);
			if(strcmp("_WwG", clsName)==0)		// MS Word
			{
				CLSID clsid;
				HRESULT hr=CLSIDFromProgID(_T("Word.Application"),&clsid);
				if(FAILED(hr))
					goto ERROR_GETWORD;
				else{
					IUnknown *pUnknown=NULL;
					IDispatch *pDispatch=NULL;
					_Application app = NULL;
					Selection sel = NULL;
					CWordWindow wnd = NULL;
					hr=::GetActiveObject(clsid,NULL,&pUnknown);	//查找是否有WORD程序在运行
					if(FAILED(hr))
					{
						goto ERROR_GETWORD;
					}
					hr=pUnknown->QueryInterface(IID_IDispatch,(LPVOID *)&app);
					if(FAILED(hr))
						goto ERROR_GETWORD;
					pUnknown->Release();	
					pUnknown=NULL;
					sel=app.GetSelection();
					if(!sel)
						goto ERROR_GETWORD;
					CFont0 ft = sel.GetFont();
					VARIANT zoom = sel.GetInformation(19);
					pComWnd.m_TargetCharHeight = (UINT)(ft.get_Size()*1.2*zoom.iVal/100);
					wnd=app.GetActiveWindow();
					if(!wnd)
						goto ERROR_GETWORD;
					long left,top,width,height;
					wnd.GetPoint(&left, &top, &width, &height, sel.GetRange());
					m_CaretPos.x = left;
					m_CaretPos.y = top;
					if(pUnknown)
						pUnknown->Release();
					if(wnd) wnd.ReleaseDispatch();
					if(sel)	sel.ReleaseDispatch();
					if(app)	app.ReleaseDispatch();
				}
			}
			else if(strcmp("paneClassDC", clsName)==0)		// MS PPT
			{
				CLSID clsid;
				HRESULT hr=CLSIDFromProgID(_T("Powerpoint.Application"),&clsid);
				if(FAILED(hr))
					goto ERROR_GETWORD;
				else{
					IUnknown *pUnknown=NULL;
					IDispatch *pDispatch=NULL;
					_ApplicationP app = NULL;
					//CPresentations presentations=NULL;
					//_Presentation presentation=NULL;
					DocumentWindow window=NULL;
					SelectionP sp=NULL;
					TextRange textrange=NULL;
					View vw = NULL;
					hr=::GetActiveObject(clsid,NULL,&pUnknown);	//查找是否有ppt程序在运行
					if(FAILED(hr))
					{
						goto ERROR_GETWORD;
					}
					hr=pUnknown->QueryInterface(IID_IDispatch,(LPVOID *)&app);
					if(FAILED(hr))
						goto ERROR_GETWORD;
					pUnknown->Release();	
					pUnknown=NULL;
					window = app.GetActiveWindow();
					sp = window.GetSelection();
					textrange = sp.GetTextRange();
					FontP ft = textrange.GetFont();
					vw = window.GetView();
					pComWnd.m_TargetCharHeight = (UINT)(ft.GetSize()*1.2*vw.GetZoom()/100);					
					if(pUnknown)
						pUnknown->Release();
					if(app) app.ReleaseDispatch();
					if(window) window.ReleaseDispatch();
					if(textrange) textrange.ReleaseDispatch();
					if(sp) sp.ReleaseDispatch();
					if(vw) vw.ReleaseDispatch();
				}
			}
		}
		//m_TargetCharHeight=tm.tmHeight+tm.tmExternalLeading;
	}
ERROR_GETWORD:
	pComWnd.SetWndPos(m_CaretPos.x,m_CaretPos.y+pComWnd.m_TargetCharHeight*3/2);
}

void CKeyProcess::EvalCharSize(HWND target)
{
	static HWND old=NULL;
	static POINT oldCaret;
	static int caretW=15;
	int tempW=0;
	if(!pComWnd.m_bEditInPlace)
		return;
	if(old==target) //from the second key
	{
		tempW=m_CaretPos.x-oldCaret.x;

		if(tempW>6&&tempW<30) //valid
		{
			caretW=caretW*2/3+tempW/3+1;//shift average
			//TRACE("caretw:%d ,newW:%d \n",caretW,tempW);
		}

	}
	pComWnd.m_TargetCharHeight=caretW*7/3;
	old=target;
	oldCaret=m_CaretPos;
}