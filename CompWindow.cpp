#include "StdAfx.h"

#include "CompWindow.h"
#include ".\compwindow.h"
#include "msword9.h"
#include "msppt.h"
#include "writeassist.h"
#include <Imm.h>
#pragma comment (lib, "imm32.lib")

#include <iostream> 
#include <fstream> 
using namespace std; 
ofstream outfile("input_history.txt",ios::app);

string input_history;

BEGIN_MESSAGE_MAP(CCompWindow, CWnd)
	ON_WM_PAINT()
	//	ON_NOTIFY_EX(TTN_NEEDTEXT, NULL, OnTranslation)
	//ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()
CCompWindow::CCompWindow()
{
	//window init
	//InitWindow();
	m_hTargetWnd=NULL;
	CreateCompWindow();
	m_tip.Create(this);
	m_bNeedSpace = TRUE;
	m_uiScreenCX=::GetSystemMetrics(SM_CXSCREEN);
	m_uiScreenCY=::GetSystemMetrics(SM_CYSCREEN);
	m_TargetCharHeight=20;

	//pure  data init
	m_iInputPosition=-1;
	m_iCompStartPos=0;
	szInputBuf[0]='\0';

	for(UINT i=0;i<DICBUFSIZE;i++)
	{
		pszDicBuf[i]=(char *)malloc(BUFLEN*sizeof(char));
		pszDicBuf[i][0]='\0';
	}

	m_uiCurrentSelectedIndex=1;
	m_uiStartIndex=1;
	TCHAR exeFullPath[MAX_PATH];
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	CString strPath(exeFullPath);
	strPath=strPath.Left(strPath.ReverseFind('\\'));
	m_pPNGMark = Image::FromFile(strPath+_T("\\res\\lock.png"));
	ShowWnd(false);
	isNeedShow=false;
	lockHot = false;
	//m_bEditInPlace=true;
}

//////////////////////////////////////////////
CCompWindow::~CCompWindow(void)
{
	//UnregisterClass(COMPCLASSNAME, NULL);
	//delete pToolTipWnd;
	for(UINT i=0;i<DICBUFSIZE;i++)
	{
		free(pszDicBuf[i]);
	}
}

///////////////////////////////////
CCompWindow & CCompWindow::Instance()
{	
	static CCompWindow mInstance;
	return mInstance;
}

////////////////////////////////////////////////////////
void CCompWindow::CreateCompWindow()
{
	//register wndclass first
	LPCTSTR szWndClass;
	szWndClass = AfxRegisterWndClass(
		CS_VREDRAW | CS_HREDRAW | CS_GLOBALCLASS,
		::LoadCursor(NULL, IDC_HAND),
		(HBRUSH) ::GetStockObject(NULL_BRUSH),
		//NULL,
		NULL);
	//
	CreateEx( WS_EX_NOACTIVATE|WS_EX_TOPMOST ,//| WS_EX_TOOLWINDOW,WS_EX_TOPMOST
		//WS_EX_NOACTIVATE=0x08000000L,// and this style not supported in vc6
		szWndClass,NULL,
		//WS_DISABLED | WS_POPUP | WS_DLGFRAME,
		/*WS_DISABLED|*/WS_POPUP,//WS_DISABLED|WS_POPUP,//|WS_BORDER,
		0,
		0,
		1,
		1,
		NULL,NULL,NULL);

	//pToolTipWnd = new CToolTipWnd(this);
	//pToolTipWnd->Create();
	//ShowWnd(false);
}
//////////////////////////////////////////////////////////////////////

void CCompWindow::ShowWnd(bool show)
{
	if(pszDicBuf[0][0] == '\0'&& m_bEditInPlace)
		show = false;
	ShowWindow(show==true?SW_SHOWNOACTIVATE:SW_HIDE);
	if(show)
	{
		InvalidateRect(NULL,true);
		isActive=true;
		isNeedShow=true;
	}
	else
	{
		m_tip.Hide();
		isActive=false;//DON'T set isNeedShow false here,because when changeing wnd,
		//we will show(false) the com wnd, but it's inner state should be NEED SHOW
		//so when switching back to the working wnd,we can determine what to do with it
	}	
}
/////////////////////////////////////////////////////////////////////
void CCompWindow::ResizeCompWindow()
{
	UINT cx,cy;
	cx=GetWndWidth();
	cy=GetWndHeight();

	//now to check if the window is all in the screen
	if(m_ptPos.x+cx>m_uiScreenCX) //the leftmost point of the window
		m_ptPos.x=m_uiScreenCX-cx;
	if(m_ptPos.y+cy>m_uiScreenCY)
	{
		m_ptPos.y=m_ptPos.y-m_TargetCharHeight*2-cy;
		//m_ptPos.x=m_ptPos.x-cx-3*m_uiCharWidth;
	}
	::SetWindowPos(GetSafeHwnd(), HWND_TOPMOST, m_ptPos.x,m_ptPos.y, cx,cy, SWP_SHOWWINDOW|SWP_NOACTIVATE);
}


void CCompWindow::CalcWindowWidth(Graphics *pG, Font *pFont)
{
	m_wndWidth = 0;
	LPCSTR text;
	RectF rf;
	for(UINT i=1;i<=10;i++)
	{
		text=pszDicBuf[m_uiStartIndex+i-2];
		pG->MeasureString(CString(text), strlen(text), pFont, PointF(0,0), &rf);
		if(m_wndWidth<rf.Width)
		{
			m_wndWidth = (UINT)rf.Width;
			m_uiCharWidth = m_wndWidth/strlen(text);
		}
	}
	if(!m_bEditInPlace)
	{
		text=szInputBuf+m_iCompStartPos;
		pG->MeasureString(CString(text), strlen(text), pFont, PointF(0,0), &rf);
		if(m_wndWidth<rf.Width)
		{
			m_wndWidth = (UINT)rf.Width;
			m_uiCharWidth = m_wndWidth/strlen(text);
		}
	}
	m_uiCharWidth += m_uiCharWidth/10;
	m_wndWidth += m_uiLeftMargin + 5;
}
#pragma warning (disable:4244)
void CCompWindow::OnPaint()
{
	PAINTSTRUCT ps;
	CDC *pDC = BeginPaint(&ps);
	CRect ClientRect;
	GetClientRect(&ClientRect);
	Graphics g(pDC->m_hDC);
	LPCSTR text;
	FontFamily  fontFamily(m_pProfileOp->m_prmFontName.lpNameValue);
	Font font(&fontFamily, 
		m_pProfileOp->m_prmFontSize.iValue,
		m_pProfileOp->m_prmFontStyle.iValue, (Unit)2);
	Font fontAlt(_T("Times New Roma"), 16);
	Font *pFont = &font;
	if(!font.IsAvailable())
	{
		pFont=&fontAlt;
	}
	CalcWindowWidth(&g, pFont);
	m_uiItemHeight= pFont->GetHeight(&g);
	m_uiLeftMargin=3*m_uiCharWidth;
	m_uiUpperMargin=0.8*m_uiItemHeight;
	ResizeCompWindow();
	CSize ClientSize(ClientRect.Width(),ClientRect.Height());
	RectF theRect(ClientRect.left,ClientRect.top,ClientRect.Width(),ClientRect.Height());
	PointF textPos(0, 0);
	LinearGradientBrush b(theRect, m_clBack1, m_clBack2 ,90.0f);
	Bitmap bm(ClientSize.cx,ClientSize.cy,&g);
	//Get a graphics object for it
	Graphics* bmpg = Graphics::FromImage(&bm);
	//shadow, frame,bg

	//bmpg->Clear(Color(255,255,255,255));
	//bmpg->FillRectangle(&b,theRect);
	//bmpg->DrawRectangle(&Pen(m_clFrame, 2), theRect);
	//int alp=200;
	/*
	ARGB argb1=0x64000000;//
	ARGB argb2=0x80000000;//
	ARGB argb3=0x40000000;//
	ARGB argb4=0x20000000;//
	
	//bmpg->Clear(Color(0,255,255,255));
	Color shadow(argb4);
	bmpg->DrawRectangle(&Pen(shadow, 1), theRect.X+6,theRect.Y+6,theRect.Width-6,theRect.Height-6);
	shadow.SetValue(argb3);
	bmpg->DrawRectangle(&Pen(shadow, 1), theRect.X+5,theRect.Y+5,theRect.Width-6,theRect.Height-6);
	shadow.SetValue(argb2);
	bmpg->DrawRectangle(&Pen(shadow, 1), theRect.X+4,theRect.Y+4,theRect.Width-6,theRect.Height-6);
	bmpg->FillRectangle(&b,theRect.X,theRect.Y,theRect.Width-3,theRect.Height-3);
	shadow.SetValue(argb1);
	bmpg->DrawRectangle(&Pen(shadow, 1), theRect.X,theRect.Y,theRect.Width-3,theRect.Height-3);
	*/
	Color shadow(0x64000000);
	bmpg->FillRectangle(&b,theRect.X,theRect.Y,theRect.Width,theRect.Height);
	bmpg->DrawRectangle(&Pen(shadow, 1), theRect.X,theRect.Y,theRect.Width-1,theRect.Height-1);
	//
	
	bmpg->SetInterpolationMode(InterpolationModeHighQualityBicubic);
	bmpg->SetTextRenderingHint((TextRenderingHint)m_pProfileOp->m_prmClearType.iValue);
	CHAR IndexToShow;
	UINT x=m_uiLeftMargin,y=0;
	Color clTextColor;
	SolidBrush *pBrush;
	SolidBrush brushHot(m_clHotText);
	SolidBrush brushCommon(m_clCommonText);

	//experimental code for compatible UI with chinese IME
	if(!m_bEditInPlace)
	{
		bmpg->DrawString(CString(szInputBuf+m_iCompStartPos)+_T("|"),-1,pFont,textPos,NULL, &brushHot);
		//int len=strlen(szInputBuf+m_iCompStartPos);
		//textPos.X+=len*m_uiCharWidth;
		//bmpg->DrawString(_T("|"),-1,pFont,textPos,NULL, &brushCommon);
	}
	for(UINT i=1;i<=10;i++)
	{
		y=(i-1)*m_uiItemHeight+m_uiUpperMargin;
		text=pszDicBuf[m_uiStartIndex+i-2];

		if(text[0]=='\0') //no valid item left ,so jump out
			break;

		IndexToShow=i%10 + '0';
		if(m_pProfileOp->m_prmShadow.iValue)
		{
			textPos.X = x+1;
			textPos.Y = y+1;
			bmpg->DrawString(CString(text),-1,pFont,textPos,NULL,&SolidBrush(m_clShadow));
		}
		if((i%10)==(m_uiCurrentSelectedIndex%10))  //emphasize the current selection 
		{
			//clTextColor = m_clHotText;
			pBrush = &brushHot;
			bmpg->DrawLine(&Pen(m_clMargin, 1), 
				Point(m_uiCharWidth, y+m_uiItemHeight),
				Point(GetWndWidth()-m_uiCharWidth, y+m_uiItemHeight));
		}
		else
			pBrush = &brushCommon;
		textPos.X = m_uiCharWidth;
		textPos.Y = y;
		bmpg->DrawString(CString(IndexToShow), -1, pFont, textPos, NULL, pBrush);
		//ec label
		if(m_uiStartIndex+i-1>=m_uiECStartIndex &&
			m_uiStartIndex+i-1<m_uiPCStartIndex)
		{
			textPos.X=0;
			bmpg->DrawString(L"!", -1, pFont, textPos, NULL, pBrush);
		}
		else if(m_uiStartIndex+i-1>=m_uiPCStartIndex)
		{
			textPos.X=0;
			bmpg->DrawString(L"?", -1, pFont, textPos, NULL, pBrush);
		}
		textPos.X = m_uiCharWidth*2;
		bmpg->DrawString(L".", -1, pFont, textPos, NULL, pBrush);
		textPos.X = x;
		bmpg->DrawString(CString(text),-1,pFont,textPos,NULL, pBrush);
	}
	g.DrawImage(&bm,theRect,0,0,bm.GetWidth(),bm.GetHeight(),UnitPixel);
	delete bmpg;
	theRect.X = GetWndWidth() - 20;
	theRect.Y = 4;
	theRect.Width = 16;
	theRect.Height = 16;
	g.DrawImage(m_pPNGMark, theRect, lockPos==false?0:32
		, 0, 16, 16, UnitPixel);
	lockHot = false;
	//pDC->DeleteDC();
	EndPaint(&ps);
}

////////////////////////////////////////////////////
bool CCompWindow::IsBufNull()
{
	return szInputBuf[0]=='\0';
}
///////////////////////////////////////////////////
bool CCompWindow::IsBufEndWithSpace()
{
	return szInputBuf[m_iInputPosition]==' ';
}
//////////////////////////////////////////////////
bool CCompWindow::IsActive()
{
	return isActive;
}

bool CCompWindow::IsNeedShow()
{
	return isNeedShow;
}

//////////////////////////////////////////////////
void CCompWindow::SetTargetWnd(HWND targetWnd)
{
	if(m_hTargetWnd!=targetWnd)  //indicate a target switch
	{
		m_hTargetWnd=targetWnd;
		szInputBuf[0]='\0';   //invalidate the input buf
		m_iInputPosition=-1;
		m_iCompStartPos=0;

		//for(UINT i=0;i<DICBUFSIZE;i++)
		//	pszDicBuf[i][0]='\0';
		m_uiCurrentSelectedIndex=1;
		m_uiStartIndex=1;

		ShowWnd(false);
		m_tip.Hide();
		isNeedShow=false;
	}
}

HWND CCompWindow::GetTargetWnd()
{
	return m_hTargetWnd;
}
///////////////////////////////////////////////
//the latest word will stay in buffer for further completion
void CCompWindow::EndOneCompletion() //end one word/phase
{										
	LPCSTR selected=pszDicBuf[m_uiCurrentSelectedIndex-1];
	if(m_bEditInPlace)
	{
		strcpy(szInputBuf,selected);
		m_iInputPosition=strlen(selected)-1;

		input_history+= szInputBuf; //2017.8.22 将当前用户输入的加入历史。不能加入用户选中的。因为只有输入的才能反映用户的主题兴趣
		outfile<<input_history.c_str()<<endl;	

	}
	else
	{	
		input_history+= szInputBuf; //2017.8.22 将当前用户选中的加入历史
		outfile<<input_history.c_str()<<endl;

		m_iInputPosition=-1;
		szInputBuf[0]='\0';

	}	
	m_iCompStartPos=0;
	isNeedShow=false;

}
///////////////////////////////////////////////
UINT CCompWindow::GetWndHeight()
{
	UINT i;
	LPCSTR text;
	for(i=0;i<10;i++)
	{
		text=pszDicBuf[m_uiStartIndex-1+i];
		if(text[0]=='\0')
			break;
	}
	return (m_uiItemHeight*i+m_uiUpperMargin+m_uiItemHeight/2);
}
//////////////////////////////////////////////
UINT CCompWindow::GetWndWidth()
{
	/*UINT maxLen=0;
	LPCSTR text;
	for(UINT i=1;i<=10;i++)
	{
		text=pszDicBuf[m_uiStartIndex+i-2];
		if(strlen(text)>maxLen)
			maxLen=strlen(text);
	}
	return (m_uiCharWidth*maxLen+m_uiLeftMargin+5);*/
	return m_wndWidth;
}
//////////////////////////////////////////////
void CCompWindow::SetWndPos(UINT x,UINT y)
{
	if(lockPos)
		return;
	m_ptPos.x=x;
	m_ptPos.y=y;
}
///////////////////////////////////////////////
void CCompWindow::AppendChar(char charCode)
{
	if(charCode!=0) //case charCode==0 is just a trick for backspace
	{
		szInputBuf[++m_iInputPosition]=charCode;
		szInputBuf[m_iInputPosition+1]='\0';
	}
	else //backspace
	{
		if(m_iInputPosition>=0)
		{
			szInputBuf[m_iInputPosition--]='\0';
			//if backward beyond the completion's start position
			if(m_iCompStartPos>m_iInputPosition)
			{//go back a word
				m_iCompStartPos=m_iInputPosition-1;
				while(m_iCompStartPos>=0 && szInputBuf[m_iCompStartPos]!=' ') 
					m_iCompStartPos--;

				if(m_iCompStartPos<0) 
					m_iCompStartPos=0;//back to the buf's head
				else m_iCompStartPos++;
			}
		}
		else 
			return;
	}

	if(UpdateDicBuf()<=0)//search in Dic by new szInputBuf,not found
	{
		if(m_bEditInPlace)
		ShowWnd(false);//no result match the style,so hide the comWnd,but keep buf
		else
		{
			m_uiCurrentSelectedIndex=0; //not invalid selection,so flushs nothing when you try to flush
			ShowWnd(szInputBuf[0]!='\0');
		}
			return ;
	}
	//get some result
	m_uiStartIndex=1; 
	m_uiCurrentSelectedIndex=1; //reset displayed frame and def selection

	ShowWnd(true);
	m_tip.Hide();
	//transTip.AddAllItems(this);

}
//////////////////////////////////////////////
void CCompWindow::Backspace(void) //a backspace
{
	AppendChar(0);//a useful trick
}
//////////////////////////////////////////////

//////////////////////////////////////////////
void CCompWindow::FlushToTarget(bool bStep, bool IsUpperCase)
{
	LPCSTR selected;
	if(m_uiCurrentSelectedIndex==0||m_uiCurrentSelectedIndex>DICBUFSIZE) //invalid index
	{
		if(!m_bEditInPlace)
			FlushTyped();
		return;
	}
	selected=pszDicBuf[m_uiCurrentSelectedIndex-1];
	Learn(selected);
	//TCHAR buf[256];
	//GetTranslation(selected, buf);
	//MessageBox(buf);
	UINT len=strlen(selected);
	char c;
	bool bStepToEnd=true;//we seek 'step' by space,but the last word of the candidate followed with nothing,

	//error check case
	// Error checking completion
	if(m_uiCurrentSelectedIndex>=m_uiECStartIndex) //is a ec candidate??
	{
		//clear error word you have typed first
		
		for(int i=m_iCompStartPos;i<=m_iInputPosition && m_bEditInPlace;i++) //if !m_bEditInPlace,we don't need backspaces 
		{
			if(!m_bNeedSpecialBack)
				::PostMessage(m_hTargetWnd, WM_CHAR, VK_BACK, 1);
			else
			{
				::PostMessage(m_hTargetWnd, WM_KEYDOWN, VK_BACK, 0x000e0001);
				::PostMessage(m_hTargetWnd, WM_KEYUP, VK_BACK, 0xC00e0001);
			}
		}
		//flush the first chars of the selected[] corresponding to the cleared
		for(UINT i=0;/*i<m_iInputPosition+1-m_iCompStartPos && */i<len;i++)
		{
			c=selected[i];

			if(IsUpperCase&&c>='a'&&c<='z')
				c=c -'a'+'A';
			::PostMessage(m_hTargetWnd, WM_CHAR, c, 1);
		}

	}
	//end fo ec fix up
	// Normal completion
	else
	{
		for(UINT i=m_bEditInPlace?(m_iInputPosition+1-m_iCompStartPos):0;i<len;i++)  //send the rest of the candidate word to target
		{
			c=selected[i];

			if(IsUpperCase&&c>='a'&&c<='z')
				c=c -'a'+'A';

			//if(m_bEditInPlace?true:(!bStep))        //if step completion&& using minibuf,don't post anything
			::PostMessage(m_hTargetWnd, WM_CHAR, c, 1);
			//send this char to the target
			//lParam=1<<0||0<<16||0<<24||0<<29<<||0<<30||0<<31

			if (bStep && c==' ')
			{
				if(!m_bEditInPlace)
					continue; //no step completion performed when use minibuf
				bStepToEnd=false;//space finded,so there must be something followed

				// Step Complete code!!just flush the first word
				int flushed=i-(m_iInputPosition+1-m_iCompStartPos)+1;
				//treat the step completion as your own input


				memcpy(&szInputBuf[m_iInputPosition+1],&selected[m_iInputPosition+1-m_iCompStartPos],flushed);


				m_iInputPosition+=flushed;
				break;
			}
		}
	}
	
	//::MessageBox(NULL,selected,"flush",MB_OK);
	//update state

	if(!bStep||bStepToEnd)  //if this step marchs to the end ,also treat it as a normal completion
	{
		EndOneCompletion();
		ShowWnd(false);
	}
	if(m_pProfileOp->m_prmAutoAddSpace.iValue && m_bNeedSpace)
	{
		if(m_bEditInPlace)
			AppendChar(' ');
		::PostMessage(m_hTargetWnd, WM_CHAR, ' ', 1);
	}
	m_bNeedSpace = TRUE;
	m_tip.Hide();
}
/////////////////////////////////////////////
void CCompWindow::FlushTyped(void)
{
	for(int i=m_iCompStartPos;i<=m_iInputPosition;i++)
		::PostMessage(m_hTargetWnd, WM_CHAR, szInputBuf[i], 1);
	EndOneCompletion();
	ShowWnd(false);
	m_tip.Hide();
}
////////////////////////////////////////////
void CCompWindow::SelectItem(UINT i)
{
	if(i>=0&&i<=9)
	{
		if(i==0) 
			i=10;
		m_uiCurrentSelectedIndex=m_uiStartIndex+i-1;
		if(pszDicBuf[m_uiCurrentSelectedIndex-1][0]!='\0')
			FlushToTarget();
	}
}
void CCompWindow::cursorUp(INT times)
{
	if(times<0) 
	{
		cursorDown(-times);
		return;
	}
	while(times-->0&&m_uiCurrentSelectedIndex>=2)
	{
		m_uiCurrentSelectedIndex--;
		if(m_uiCurrentSelectedIndex%10==0) //scroll to the upper page
		{
			m_uiCurrentSelectedIndex++;//reset it,and let pageup do it
			PageUP();
			//ResizeCompWindow();
		}
		else
			ShowWnd(true);
	}
	MouseMoveToItem((m_uiCurrentSelectedIndex-1)%10+1);
}
void CCompWindow::cursorDown(INT times)
{
	if(times<0) 
	{
		cursorUp(-times);
		return;
	}
	while(times-->0&&pszDicBuf[m_uiCurrentSelectedIndex][0]!='\0')
	{
		m_uiCurrentSelectedIndex++;
		if(m_uiCurrentSelectedIndex%10==1)//scroll to the next page
		{
			m_uiCurrentSelectedIndex--;//reset it,and let pagedown do it
			PageDown();
			//ResizeCompWindow(); 
		}
		else
			ShowWnd(true);
	}
	MouseMoveToItem((m_uiCurrentSelectedIndex-1)%10+1);
}
void CCompWindow::PageUP(void)
{
	if(m_uiStartIndex>10)
	{
		m_uiStartIndex-=10;
		m_uiCurrentSelectedIndex=m_uiStartIndex+9; //when puageup done,select the lowest as def
	}
	ShowWnd(true);

}
void CCompWindow::PageDown(void)
{
	if(pszDicBuf[m_uiStartIndex-1+10][0]!='\0'&&(m_uiStartIndex<DICBUFSIZE-10))
	{
		m_uiStartIndex+=10;
		m_uiCurrentSelectedIndex=m_uiStartIndex;//when puageup done,select the highest as def
	}
	ShowWnd(true);
}


BOOL CCompWindow::PreTranslateMessage(MSG* pMsg)
{
	//if(pMsg->message==WM_MOUSEMOVE)//||pMsg->message==WM_LBUTTONUP)
	//	transTip.RelayEvent (pMsg);
	return CWnd::PreTranslateMessage(pMsg);
}


UINT CCompWindow::UpdateDicBuf()
{
	bool hasSpace;
	int NumofSpace;
	UINT getNum=0;
	UINT ECnum=0;//ec condidate num

TRY4NEW:
	////outfile<<"start pos:"<<m_iCompStartPos<<endl;
	////outfile<<"input pos:"<<m_iInputPosition<<endl;
	hasSpace=false;
	NumofSpace=0;
	
	//查看是否有空格。以及空格的个数（如果空格个数超过4个，将启动句子提示展示）
	for(INT i=m_iCompStartPos;i<=m_iInputPosition;i++)
		if(szInputBuf[i]==' ')
		{
			hasSpace=true;
			NumofSpace++;
			//break;
		}

		getNum=0;
		if(szInputBuf[m_iCompStartPos]!='\0'&&szInputBuf[m_iCompStartPos]!=' ')//do nothing for null str
		{

			//if(hasSpace)
			if(hasSpace && NumofSpace < 4)
				getNum=GetPhraseHint_New(szInputBuf+m_iCompStartPos, 
				pszDicBuf, m_pProfileOp->m_prmPhraseHintNum.iValue);
			else if (NumofSpace >= 4)
				getNum=GetSentenceHint_New(szInputBuf+m_iCompStartPos, 
				pszDicBuf, m_pProfileOp->m_prmPhraseHintNum.iValue);
			else if(strlen(szInputBuf+m_iCompStartPos) >= m_pProfileOp->m_prmStartHintLetter.iValue)
				getNum=GetWordHint_New(szInputBuf+m_iCompStartPos,
				pszDicBuf, m_pProfileOp->m_prmWordHintNum.iValue);			

		}
		//outfile<<"返回的:"<<*pszDicBuf<<endl;
		//outfile<<"getNum:"<<getNum<<endl;

		if(getNum==0) //this str has no corresponding results
		{
			INT old=m_iCompStartPos;
			//get a shorter str to search again
			while(szInputBuf[m_iCompStartPos]!=' '&& m_iCompStartPos<m_iInputPosition) 
				m_iCompStartPos++;

			m_iCompStartPos++; //move to the next word 's head, after a space

			if(m_iCompStartPos>m_iInputPosition) //find nothing new,so go back
			{
				m_iCompStartPos=old;
				//ADD TO THE DIC
				if(szInputBuf[m_iInputPosition]==' ') //catch a strange new word(?)
				{
					szInputBuf[m_iInputPosition]='\0';//a little tricky,as Learn() need a null terminated str
					Learn(&szInputBuf[m_iCompStartPos]);
					//::MessageBoxA(NULL,&szInputBuf[m_iCompStartPos],"Learned new word:",MB_OK);
					szInputBuf[m_iInputPosition]=' ';
				}

			}
			else //need a new try
				if(m_bEditInPlace)
				goto TRY4NEW; //recursive is also ok,but goto is a better choice
		}//end of if getnum==0

		//start error check etc.
		m_uiECStartIndex=10000;
		m_uiPCStartIndex = 10000;
		if(!hasSpace && (getNum< m_pProfileOp->m_prmStartECNum.iValue||
			getNum-ECnum< m_pProfileOp->m_prmStartPCNum.iValue))
		{
			if(!IsStringExist(szInputBuf+m_iCompStartPos))
			{
				if(m_pProfileOp->m_prmEnableErrorCheck.iValue && getNum< m_pProfileOp->m_prmStartECNum.iValue)//need EC
				{
					m_uiECStartIndex=getNum+1;
					ECnum=GetErrorCheck(szInputBuf+m_iCompStartPos,
						pszDicBuf+getNum, m_pProfileOp->m_prmECMaxHint.iValue);
					getNum+=ECnum;

				}
				//pronounce check
				if(m_pProfileOp->m_prmEnablePronunCheck.iValue && (getNum-ECnum)< m_pProfileOp->m_prmStartPCNum.iValue)//need EC
				{
					if(m_uiECStartIndex==10000)//no ec
						m_uiECStartIndex=getNum+1;
					m_uiPCStartIndex = getNum+1;
					getNum+=GetMetaPhoneHint(szInputBuf+m_iCompStartPos,
						pszDicBuf+getNum,m_pProfileOp->m_prmPCMaxHint.iValue);
				}
			}
		}
		
		//end ec
		for(UINT i=getNum;i<DICBUFSIZE;i++) //make the unused buf space invalid
		{
			pszDicBuf[i][0]='\0';
		}
		if(!m_bEditInPlace)
			m_iCompStartPos=0;  //don't shift start pos when !m_bEditInPlace
		return getNum;
}

void CCompWindow::MouseMoveToItem(int i)
{
	m_tip.Hide();
	static CPoint here;
	UINT x=GetWndWidth();
	UINT y=i*m_uiItemHeight+m_uiUpperMargin;
	/*	for(int j=0;j<10;j++)
	PostMessage(WM_MOUSEMOVE,0,(y<<16)+(x+j));
	*/
	here.x=x;
	here.y=y;
	m_tip.InformCompWindowSize(here);
	ClientToScreen(&here);
	UINT transItemIndex=m_uiStartIndex+i-1;//to global id
	if(m_pProfileOp->m_prmEnableTranslation.iValue)
	{
		BOOL getIt = GetTranslation(pszDicBuf[transItemIndex-1], transBuf);
		if(wcslen(transBuf) == 0)
			m_tip.Hide();
		else
		{
			if(!getIt && m_pProfileOp->m_prmShowUnmatched.iValue==1) //can't find ,but i have some suggestion
			{
				FormatTransBuf();
				getIt=true;
			}
			if(getIt)
			{
				FormatTransWidth();
				m_tip.Show(transBuf, &here);
			}
		}
	}
}

void CCompWindow::FormatTransBuf(void)
{
	int i=0,j=0;
	while(transBuf[i]!='\0')
	{
		if(transBuf[i]=='?') //find the separator between origin and translation
		{
			j=i+1;
			while(transBuf[j]!='\0') //find the end of this term
			{
				if((transBuf[j]&0xFF00)==0) //is english char,so we have found the next term
					break;
				j++;
			}
			wmemmove(&transBuf[i],&transBuf[i+1],j-i-1);
			if(transBuf[j]!='\0') //not to the end
				transBuf[j-1]='\n';  //append a new line
			else
				transBuf[j-1]='\0';
			i=j-1;//step to the next term
		}
		i++;
	}
}

void CCompWindow::FormatTransWidth()
{
	int i=0;
	int iWidth=0;
	TCHAR buf[2048];
	while (transBuf[i] != _T('\0'))
	{
		if(transBuf[i] == _T('\n'))
			iWidth=0;
		if((transBuf[i]&0xFF00)==0)	// letter
			iWidth+=1;
		else
			iWidth+=2;
		i++;
		if(iWidth >= 50)	// insert enter
		{
			wcscpy(buf, _T("\n"));
			wcscat(buf, transBuf+i);
			wcscpy(transBuf+i, buf);
			iWidth = 0;
		}
	}
}

void CCompWindow::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	static CPoint lastPoint;
	static UINT oldFlags;
	int deltX,deltY;
	//if(nFlags!=0)
	//	TRACE("%d  ",nFlags);
	//CPoint scrPoint;
	RECT rt;
	POINT pt;
	pt.x = point.x;
	pt.y = point.y;
	rt.left = GetWndWidth()-20;
	rt.top = 4;
	rt.right = rt.left+16;
	rt.bottom = rt.top+16;
	if((nFlags&MK_LBUTTON)==0)//just mousemove
	{
		HDC hDC = ::GetDC(GetSafeHwnd());
		Graphics g(hDC);
		RectF theRect(GetWndWidth()-20, 4, 16, 16);
		if(PtInRect(&rt, pt))
		{
			if(!lockHot)
			{
				g.DrawImage(m_pPNGMark, theRect, 16+(lockPos==false?0:32)
					, 0, 16, 16, UnitPixel);
				lockHot = true;
			}
		}
		else
		{
			if(lockHot)
			{
				g.DrawImage(m_pPNGMark, theRect, lockPos==false?0:32
					, 0, 16, 16, UnitPixel);
				lockHot=false;
			}
		}
		::ReleaseDC(GetSafeHwnd(), hDC);
		if((oldFlags&MK_LBUTTON)==1) //releasing lbutton
		{
			HWND	hWnd = m_hTargetWnd;//::GetForegroundWindow();
			DWORD   FormThreadID   =   GetCurrentThreadId();
			DWORD   CWndThreadID   =   GetWindowThreadProcessId(hWnd,   NULL);  

			AttachThreadInput(CWndThreadID,   FormThreadID,   true);  
			HWND ret=::SetFocus(m_hTargetWnd);
			//TRACE("compwnd regains focus?%x->%x\n",ret,m_hTargetWnd);
			AttachThreadInput(CWndThreadID,   FormThreadID,   false);  
		}
		//TRACE("x:%d ,y:%d\n",point.x,point.y);
		lastPoint.x=0;//indicator
		oldFlags=nFlags;
		return;
	}
	else //drag
	{
		ClientToScreen(&point);
		if(lastPoint.x==0)//not valid,first mouse drag point
		{
			lastPoint=point;
			oldFlags=nFlags;
			return;
		}

		deltX=point.x-lastPoint.x;
		deltY=point.y-lastPoint.y;
		m_ptPos.x+=deltX;
		m_ptPos.y+=deltY;

		lastPoint=point;
		oldFlags=nFlags;

		//TRACE("drag");
		//if ((nFlags&MK_CONTROL)==0) //not lock
		//	lockPos=false;
		//else 
		//	lockPos=true;
		ResizeCompWindow();
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CCompWindow::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	OnLButtonUp(nFlags,point);
	CWnd::OnRButtonUp(nFlags, point);
}

void CCompWindow::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	HWND	hWnd = m_hTargetWnd;//::GetForegroundWindow();
	DWORD   FormThreadID   =   GetCurrentThreadId();
	DWORD   CWndThreadID   =   GetWindowThreadProcessId(hWnd,   NULL);  

	AttachThreadInput(CWndThreadID,   FormThreadID,   true);  
	HWND ret=::SetFocus(m_hTargetWnd);
	//TRACE("compwnd regains focus?%x->%x\n",ret,m_hTargetWnd);
	AttachThreadInput(CWndThreadID,   FormThreadID,   false);
	RECT rt;
	rt.left = GetWndWidth()-20;
	rt.top = 4;
	rt.right = rt.left+16;
	rt.bottom = rt.top+16;
	if(PtInRect(&rt, point))
	{
		lockPos=!lockPos;
		Invalidate();
	}
	CWnd::OnLButtonUp(nFlags, point);
}
