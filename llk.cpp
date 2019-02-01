// llk.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include <stdio.h>
#include <Mmsystem.h>
#include <Windows.h>
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_LLK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_LLK);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_LLK);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_LLK;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, "我的第一个游戏：fyd连连看", WS_OVERLAPPEDWINDOW,
    0 , 0,700 ,650 , NULL, NULL, hInstance, NULL);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
 int i=0;
int x1,y1,x2,y2;
int Times=0;
char * BackGroudImage = "llkboss.bmp";
char * wall = "bmp\\wall.bmp";
char * Carton1 = "bmp\\1.bmp";
char * Carton2 = "bmp\\2.bmp";
char * Carton3 = "bmp\\3.bmp";
char * Carton4 = "bmp\\4.bmp";
char * Carton5 = "bmp\\5.bmp";
char * Ground = "bmp\\ground.bmp";
char MapData[8][8]={{0,0,0,0,0,0,0,0},
					{0,3,5,1,2,3,2,0},
					{0,5,1,3,2,1,4,0},
					{0,4,2,3,2,4,5,0},
					{0,3,2,1,5,2,2,0},		
					{0,5,1,3,1,4,4,0},					
					{0,4,3,4,4,5,3,0},
					{0,0,0,0,0,0,0,0},
					};
char (*a)[8]=MapData;
char MapData1[8][8]={{0,0,0,0,0,0,0,0},
					{0,3,5,1,2,3,2,0},
					{0,5,1,3,2,1,4,0},
					{0,4,2,3,2,4,5,0},
					{0,3,2,1,5,2,2,0},		
					{0,5,1,3,1,4,4,0},					
					{0,4,3,4,4,5,3,0},
					{0,0,0,0,0,0,0,0},
					};
char (*b)[8]=MapData1;
char MapData2[8][8]={{0,0,0,0,0,0,0,0},
					{0,3,5,1,2,3,2,0},
					{0,5,1,3,2,1,4,0},
					{0,4,2,3,2,4,5,0},
					{0,3,2,1,5,2,2,0},		
					{0,5,1,3,1,4,4,0},					
					{0,4,3,4,4,5,3,0},
					{0,0,0,0,0,0,0,0},
					};
char (*c)[8]=MapData2;

UINT ID_TIMER1=1,ID_TIMER2=2,ID_TIMER3=3;

//显示图片
void ShowBmp(HWND hWnd, char * FileName, int x, int y , int w, int h)
{
	HBITMAP m_bmp = (HBITMAP)LoadImage(NULL,_T(FileName),IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
	HDC m_DestDC = GetDC(hWnd);
	HDC m_SrcDC = CreateCompatibleDC(m_DestDC);
	SelectObject(m_SrcDC,m_bmp);
	BitBlt(m_DestDC , x , y , w, h , m_SrcDC , 0 , 0 , SRCCOPY);
	DeleteObject(m_bmp);
	DeleteDC(m_SrcDC);
	ReleaseDC(hWnd, m_DestDC);
}
void loadmap(HWND hWnd)
{
int row,int col;
		for(row=0; row<8;row++)
					{
						for(col=0;col<8;col++)
						{
							switch(MapData[row][col])
							{
								case 0:
									{
										ShowBmp(hWnd,wall , row*48+50 ,col*48+50, 48,48);
										break;
									}
								case 1:
									{
										ShowBmp(hWnd,Carton1 , row*48+50 ,col*48+50, 48,48);
										break;
									}
								case 2:
									{
										ShowBmp(hWnd,Carton2, row*48+50 ,col*48+50, 48,48);
										break;
									}
								case 3:
									{
										ShowBmp(hWnd,Carton3, row*48+50 ,col*48+50, 48,48);
										break;
									}
								case 4:
									{
										ShowBmp(hWnd, Carton4, row*48+50 ,col*48+50, 48,48);
										break;
									}
								case 5:
									{
										ShowBmp(hWnd, Carton5, row*48+50 ,col*48+50, 48,48);
										
										break;
									}
							
							}
						}
					}
}
//消失两张图片
// 画线
//void Draweline（）
//{
 // if(x1=x2 && y1!=y2)
//		{
//		  if(y1>y2)
///				{
//					switch(y1-y2)
//					{
//					case 1:{}
///					case 2:{}
//					case 3:{}
//					case 4:{}
//					case 5:{}
//					}
//				}
//		  else
//				  {	
//					switch(y2-y1)
//					{
//					case 1:{}
//					case 2:{}
//					case 3:{}
//					case 4:{}
//					case 5:{}
//					}
//
//				  }
//		}//x同y不同
//   if(y1=y2 && x1!=x2)
//		 {
//			if(x1>x2)
//				{
//					switch(x1-x2)
//					{
//					case 1:{}
//					case 2:{}
//					case 3:{}
//					case 4:{}
//					case 5:{}
//					}
//				}
//		  else
//				  {	
//					switch(x2-x1)
//					{
//					case 1:{}
//					case 2:{}
//					case 3:{}
//					case 4:{}
//					case 5:{}
//					}
//
//				  }
//		 }//y同x不同
      //连接同向的图片0个拐点
//       if(MapData[x1][y2]==0)
//	      {
//		     if(x1>x2)
//			 {
//				 if(y1<y2)
//				 {}
//				 else
//				 {}
//			 }
//			 else
//			 {
//				if(y1<y2)
//				 {}
//				 else
//				 {}
//
//			 }
//
//			}//一个拐点
//		 if(MapData[x1][y2]==0)
//	      {
//				if(x1>x2)
//				 {
//					 if(y1<y2)
//					 {}
//					 else
//					 {}
//				 }
//				 else
//				 {
//					if(y1<y2)
//					 {}
//					 else
//					 {}
//
//				 }
//			}//一个拐点
	//void Line(HWND hWnd,int pointx1,int pointy1,int pointx2,int pointy2)
//	{
//	HDC m_DestDC = GetDC(hWnd)
//	HPEN m_Pen = CreatePen(PS_SOLID,1,RGB_(255,255,255));
//	SelectObject(m_DestDC,m_Pen);
//	}			
//
//}
//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
	int	x = LOWORD(lParam); 
	int	y = HIWORD(lParam); 
   	switch (message) 
	{         case WM_LBUTTONDOWN:
					{       
								
											x1=(int)((x-50)/48);
											y1=(int)((y-50)/48);
									break;
					}
				case WM_RBUTTONDOWN:
					{
											x2=(int)((x-50)/48);
											y2=(int)((y-50)/48);
											
										  if((x2>0 && x2<7) && (y2>0 && y2<7))
											  {  
												if((MapData[x1][y1]==MapData[x2][y2])&&(x1!=x2 || y1!=y2))
												{
												ShowBmp(hWnd,Ground , x1*48+50 ,y1*48+50, 48,48);
												ShowBmp(hWnd,Ground , x2*48+50 ,y2*48+50, 48,48);
												
													Times++;
												
												     if(Times==18)
													 {
															Times=0;
														if( MessageBox(hWnd,"恭喜！！过关！！","提示",MB_OKCANCEL)==IDOK)
														{
															ShowBmp(hWnd, BackGroudImage, 0,0, 800,600);
														KillTimer(hWnd,ID_TIMER1);
														KillTimer(hWnd,ID_TIMER2);
														KillTimer(hWnd,ID_TIMER3);
														}
													 }
												}
										  }
							  break;
					}
		case WM_TIMER: 
				{
				if(wParam==ID_TIMER1)
					{	
						loadmap(hWnd);
						if(Times<18)
						{
								if(MessageBox(hWnd,"可惜！！\n失败了！！\n再来一次？","提示",MB_OKCANCEL)==IDOK)
									{	Times=0;
									loadmap(hWnd);
									}
							
								else
									{
									ShowBmp(hWnd, BackGroudImage, 0,0, 800,600);
									KillTimer(hWnd,ID_TIMER1);
									}	
						}
					}
				if(wParam==ID_TIMER2)
					{
							loadmap(hWnd);
							if(Times<18)
							{
									Times=0;
								if(MessageBox(hWnd,"可惜！！\n失败了！！\n再来一次？","提示",MB_OKCANCEL)==IDOK)
										{
											loadmap(hWnd);
										}
									else
										{
										ShowBmp(hWnd, BackGroudImage, 0,0, 800,600);
										KillTimer(hWnd,ID_TIMER2);
										}
							}
					}
						if(wParam==ID_TIMER3)
							{
								loadmap(hWnd);
									if(Times<18)
									{
											if(MessageBox(hWnd,"可惜！！\n失败了！！\n再来一次？","提示",MB_OKCANCEL)==IDOK)
												{
															Times=0;
														loadmap(hWnd);
												}
									
												else
													{
													ShowBmp(hWnd, BackGroudImage, 0,0, 800,600);
															KillTimer(hWnd,ID_TIMER3);
													}
						
									}
							}
		break;
				}
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{   case ID_MENUITEM32771:
					{
						SetTimer(hWnd,ID_TIMER1,250000,NULL);
	
							loadmap(hWnd);
						break;
					}
					case ID_MENUITEM32773:	
					{
						SetTimer(hWnd,ID_TIMER2,35000,NULL);

						loadmap(hWnd);
						break;	
					}
					case ID_MENUITEM32774:
					{	
						loadmap(hWnd);
						SetTimer(hWnd,ID_TIMER3,40000,NULL);

						break;
					}
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
            ShowBmp(hWnd, BackGroudImage, 0,0, 800,600);
			HINSTANCE hInstance;
			CreateWindow(szWindowClass, "我的第一个游戏：fyd连连看", WS_OVERLAPPEDWINDOW,
    0 , 0,100 ,150 , NULL, NULL, hInstance, NULL);
				
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
