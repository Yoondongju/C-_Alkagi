// DefaultWindow.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "DefaultWindow.h"
#include "MainGame.h"


//추가 2024 0415 leejunsik
#include "Scene.h"
#include "SceneMgr.h"
#include "CEventMgr.h"
//추가 2024 0415 leejunsik

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND	g_hWnd;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);	// 창 모양(스타일) 설정
BOOL                InitInstance(HINSTANCE, int);			// 창을 생성하는 함수
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);	// 윈도우 메세지 처리 함수
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);		// 쓸데 없음



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,			// 메모리에 할당되는 실체, 즉 객체(현재 프로그램의 고유 식별 번호)
                     _In_opt_ HINSTANCE hPrevInstance,	// 전에 실행되었던 인스턴스 핸들(없을 경우 NULL)
                     _In_ LPWSTR    lpCmdLine,			
                     _In_ int       nCmdShow)			// 실행한 창의 스타일(모양 / 최소화 모양, 최대화 모양 등등)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULTWINDOW, szWindowClass, MAX_LOADSTRING);
   
	MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULTWINDOW));

    MSG msg;
	msg.message = WM_NULL;

	//CMainGame		MainGame;
	//MainGame.Initialize();
	CMainGame::CreateSingleTonInst()->Initialize();

    // 기본 메시지 루프입니다.
    //while (GetMessage(&msg, nullptr, 0, 0))
    //{
    //    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    //    {	// 메뉴 기능의 단축키가 작동하도록 검사하는 함수

    //        TranslateMessage(&msg);	// 키보드 메세지를 가공하여 프로그램에서 사용할 수 있도록 해주는 함수
    //        DispatchMessage(&msg);	// 시스템 메세지 큐에서 꺼낸 메세지를 프로그램의 메세지 처리 함수로 전달하는 함수
    //    }
    //}

	DWORD		dwTime = GetTickCount();

	while (true)
	{
		// PM_REMOVE : 메세지를 읽어옴과 동시에 메세지 큐에서 제거
		// PM_NOREMOVE : 메세지 큐에 메세지의 존재 여부만 판단, 메세지를 읽어오려면 GetMessage함수를 다시 호출해야 한다.

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{	// 메뉴 기능의 단축키가 작동하도록 검사하는 함수

				TranslateMessage(&msg);	// 키보드 메세지를 가공하여 프로그램에서 사용할 수 있도록 해주는 함수
				DispatchMessage(&msg);	// 시스템 메세지 큐에서 꺼낸 메세지를 프로그램의 메세지 처리 함수로 전달하는 함수
			}
		}
		else
		{
			// 1050 + 10		< 959
			if (dwTime + 10 < GetTickCount())
			{
				CMainGame::CreateSingleTonInst()->Update();
				CMainGame::CreateSingleTonInst()->Late_Update();
				CMainGame::CreateSingleTonInst()->Render();


				CEventMgr::CreateSingleTonInst()->Update();


				dwTime = GetTickCount();		// 1050
			}
		}

	
	}

    return (int) msg.wParam;
}	 


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
	// 윈도우를 생성하기 위한 정보를 담아두는 구조체
	

    wcex.cbSize = sizeof(WNDCLASSEX);
	// 자기 자신의 사이즈를 저장함 

    wcex.style          = CS_HREDRAW | CS_VREDRAW;	// 초기화 되는 값을 의미하며 윈도우 창의 수직 또는 수평의 크기가 변할 경우 윈도우 창을 다시 그림
	// CS_HREDRAW : 가로를 다시 그림
	// CS_VREDRAW : 세로를 다시 그림

    wcex.lpfnWndProc    = WndProc;	// 저장해둔 함수가 호출되어 메세지를 처리시킴

    wcex.cbClsExtra     = 0;	// 윈도우가 특수한 목적으로 사용하는 여분의 공간
    wcex.cbWndExtra     = 0;	// 일종의 예약 영역이며 사용하지 않을 경우 0으로 지정

    wcex.hInstance      = hInstance;	// 윈도우 클래스를 사용하는 프로그램의 번호를 설정
										// 메인 함수에서 전달한 값을 그대로 대입

    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULTWINDOW));
	// 윈도우 창이 사용할 아이콘 지정할 수 있음(시작 표시줄)
	
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	// 마우스 커서를 지정
	
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	// 윈도우 창 배경 색상

	wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_DEFAULTWINDOW);
	// 창 상단에 있는 메뉴 설정

    wcex.lpszClassName  = szWindowClass;
	// 실행 파일의 이름을 지정 : 가급적이면 프로젝트 이름과 일치시켜 작성하여 크게 변경하지 않음

    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	// 창 상단에 있는 작은 아이콘 모양을 지정

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // CreateWindowW : 등록해 놓은 정보들을 토대로 창을 생성하는 작업을 진행

   RECT	rcWnd{ 0, 0, WINCX, WINCY };

   // rcWnd = rcWnd + 기본 창 스타일 옵션 + 메뉴 바 사이즈 고려 여부
   AdjustWindowRect(&rcWnd, WS_OVERLAPPEDWINDOW, FALSE);

   HWND hWnd = CreateWindowW(szWindowClass,		// 앞서 정의한 윈도우 클래스에 전달할 클래스 이름을 그대로 넣어줌
						   szTitle,				// 윈도우 상단에 나타낼 문자열을 전달
						   WS_OVERLAPPEDWINDOW,	// 만들고자 하는 윈도우 스타일을 지정(기본 값 : 기본 윈도우 모양 설정)
						   CW_USEDEFAULT, 0,	// 전체 스크린 중 어느 위치에 창을 생성할 것인가(X,Y 좌표)
						   rcWnd.right - rcWnd.left, 
						   rcWnd.bottom - rcWnd.top,			// 창의 가로, 세로 사이즈
						   nullptr,				// 부모 윈도우가 있다면 부모 윈도우의 핸들을 지정(부모가 없으면 NULL)
						   nullptr,				// 윈도우에서 사용할 메뉴의 핸들(레지스터에 등록된 메뉴 형태를 사용하려면 NULL)
						   hInstance,			// 윈도우를 만드는 주체, 프로그램의 핸들을 지정
						   nullptr);			// 운영체제가 특수한 목적으로 사용(모름)

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

// 라이브러리 : 바이너리로 번역(컴파일)된 함수들을 모아놓은 파일
// 
// 코드 재사용을 위한 초창기 방법 중 하나로 다른 프로그램에서 사용할 수 있도록 운영체제나 소프트웨어 개발자에 의해 제공
// 라이브러리의 대다수 함수들은 함수의 정의 및 선언들을 필요로 하기 때문에 링크되기 전 전처리기에 의해 해당 헤더 파일을 프로그램에 포함 시켜야 함
// 라이브러리들은 사용자의 프로그램과 링크되어 실행이 가능한 완전한 프로그램을 이루게 됨

// window 필수 라이브러리

// 1. kernel : 메모리를 관리하고 프로그램을 실행
// 2. user : 유저 인터페이스와 윈도우 창을 관리
// 3. gdi : 화면 처리와 그래픽을 담당

RECT	rc{ 400, 400, 500, 500 };
list<RECT>		BulletList;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	//case WM_CREATE:

	//	SetTimer(hWnd, 0, 0, NULL);
	//	// 2인자 : 타이머의 id 번호, 윈도우에서 여러 개의 타이머가 생성될 수 있으므로 구분하기 위한 타이머 번호
	//	// 3인자 : 타이머 주기, 0으로 지정하면 1000당 1초 꼴로 시간 값을 발생
	//	// 4인자 : NULL인 경우 설정한 주기(3인자)대로 WM_TIMER 메세지를 발생시킴
	//	break;

	//case WM_TIMER:
	//	InvalidateRect(hWnd, NULL, TRUE);
	//	// 윈도우 갱신 함수

	///*	2인자 : 윈도우 안에서 갱신할 범위를 지정(RECT 구조체 주소를 받으며, NULL인 경우 윈도우 전체 영역에 적용)
	//	3인자 : FALSE - 새로 그리는 부분만 갱신
	//			TRUE - 그려져 있지 않는 부분도 갱신*/
	//	break;


    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

   // case WM_PAINT:
   //     {
   //         PAINTSTRUCT ps;

			//// HDC : 출력에 관한 정보를 저장하는 구조체
   //         HDC hdc = BeginPaint(hWnd, &ps);

			//// 2, 3인자 : 커서 포인터의 위치 좌표(x,y)
			//// 4인자 : 커서를 이동하기 전 위치를 output으로 반환
			//// MoveToEx(hdc, 100, 100, nullptr);
			//// 
			//// LineTo(hdc, 200, 100);
			//// LineTo(hdc, 200, 200);
			//// LineTo(hdc, 100, 200);
			//// LineTo(hdc, 100, 100);
			//// LineTo(hdc, 200, 200);
			//// 
			//// MoveToEx(hdc, 200, 100, nullptr);
			//// LineTo(hdc, 100, 200);

			//// 사각형 그리기 함수
			////Rectangle(hdc, 100, 100, 200, 200);

			//// 원 그리기 함수
			////Ellipse(hdc, 300, 300, 400, 400);
			//
			//Rectangle(hdc, 
			//		rc.left,
			//		rc.top, 
			//		rc.right, 
			//		rc.bottom);

			//for (auto& iter : BulletList)
			//{
			//	Ellipse(hdc, iter.left, iter.top, iter.right, iter.bottom);

			//	iter.top	-= 10;
			//	iter.bottom -= 10;
			//}

			//	
   //         EndPaint(hWnd, &ps);
   //     }
   //     break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;

		/*case VK_RIGHT:
			rc.left  += 10;
			rc.right += 10;
			break;

		case VK_LEFT:
			rc.left  -= 10;
			rc.right -= 10;
			break;

		case VK_UP:
			rc.top    -= 10;
			rc.bottom -= 10;
			break;

		case VK_DOWN:
			rc.top	  += 10;
			rc.bottom += 10;
			
			break;

		case VK_SPACE:
			BulletList.push_back(rc);
			break;*/
		}

		break;


    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// 함수 호출 규약

// - 함수의 실행이 종료되면 할당되었던 스택 메모리를 해제해야 함
// - 함수를 호출한 호출원(caller)에서 정리할 것인지 아니면 호출 받은 피호출자(callee)에서 할 것인가에 대한 약속, 또는 규약

// __cdecl : c / c++ 기본 함수 호출 규약, __cdecl만 호출원이 stack을 정리, 가변 인자 함수(정작 자기 자신에게 어떤 매개 변수가 얼마나 들어올지 모름), 본인이 스택을 정리 할 수 없다

// __stdcall : WINAPI 기본 함수 호출 규약, 피호출자인 callee가 stack을 정리, 고정 인자 함수(매개 변수가 고정되어 있어 피호출자가 어떤 값이 들어올 지 알고 있음), 본인 스스로 stack을 정리할 수 있다
// __fastcall : 함수 호출을 빠르게 처리하기 위한 규약, ecx와 edx라는 레지스터를 통해 저장, 레지스터를 사용하고 있는 점에서 함수 호출이 빨라지는 근거
// __thiscall : this 포인터를 매개 변수로 넘겨 받았을 때 사용하는 호출 규약

