// DefaultWindow.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "DefaultWindow.h"
#include "MainGame.h"


//�߰� 2024 0415 leejunsik
#include "Scene.h"
#include "SceneMgr.h"
#include "CEventMgr.h"
//�߰� 2024 0415 leejunsik

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
HWND	g_hWnd;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);	// â ���(��Ÿ��) ����
BOOL                InitInstance(HINSTANCE, int);			// â�� �����ϴ� �Լ�
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);	// ������ �޼��� ó�� �Լ�
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);		// ���� ����



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,			// �޸𸮿� �Ҵ�Ǵ� ��ü, �� ��ü(���� ���α׷��� ���� �ĺ� ��ȣ)
                     _In_opt_ HINSTANCE hPrevInstance,	// ���� ����Ǿ��� �ν��Ͻ� �ڵ�(���� ��� NULL)
                     _In_ LPWSTR    lpCmdLine,			
                     _In_ int       nCmdShow)			// ������ â�� ��Ÿ��(��� / �ּ�ȭ ���, �ִ�ȭ ��� ���)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULTWINDOW, szWindowClass, MAX_LOADSTRING);
   
	MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
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

    // �⺻ �޽��� �����Դϴ�.
    //while (GetMessage(&msg, nullptr, 0, 0))
    //{
    //    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    //    {	// �޴� ����� ����Ű�� �۵��ϵ��� �˻��ϴ� �Լ�

    //        TranslateMessage(&msg);	// Ű���� �޼����� �����Ͽ� ���α׷����� ����� �� �ֵ��� ���ִ� �Լ�
    //        DispatchMessage(&msg);	// �ý��� �޼��� ť���� ���� �޼����� ���α׷��� �޼��� ó�� �Լ��� �����ϴ� �Լ�
    //    }
    //}

	DWORD		dwTime = GetTickCount();

	while (true)
	{
		// PM_REMOVE : �޼����� �о�Ȱ� ���ÿ� �޼��� ť���� ����
		// PM_NOREMOVE : �޼��� ť�� �޼����� ���� ���θ� �Ǵ�, �޼����� �о������ GetMessage�Լ��� �ٽ� ȣ���ؾ� �Ѵ�.

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{	// �޴� ����� ����Ű�� �۵��ϵ��� �˻��ϴ� �Լ�

				TranslateMessage(&msg);	// Ű���� �޼����� �����Ͽ� ���α׷����� ����� �� �ֵ��� ���ִ� �Լ�
				DispatchMessage(&msg);	// �ý��� �޼��� ť���� ���� �޼����� ���α׷��� �޼��� ó�� �Լ��� �����ϴ� �Լ�
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
	// �����츦 �����ϱ� ���� ������ ��Ƶδ� ����ü
	

    wcex.cbSize = sizeof(WNDCLASSEX);
	// �ڱ� �ڽ��� ����� ������ 

    wcex.style          = CS_HREDRAW | CS_VREDRAW;	// �ʱ�ȭ �Ǵ� ���� �ǹ��ϸ� ������ â�� ���� �Ǵ� ������ ũ�Ⱑ ���� ��� ������ â�� �ٽ� �׸�
	// CS_HREDRAW : ���θ� �ٽ� �׸�
	// CS_VREDRAW : ���θ� �ٽ� �׸�

    wcex.lpfnWndProc    = WndProc;	// �����ص� �Լ��� ȣ��Ǿ� �޼����� ó����Ŵ

    wcex.cbClsExtra     = 0;	// �����찡 Ư���� �������� ����ϴ� ������ ����
    wcex.cbWndExtra     = 0;	// ������ ���� �����̸� ������� ���� ��� 0���� ����

    wcex.hInstance      = hInstance;	// ������ Ŭ������ ����ϴ� ���α׷��� ��ȣ�� ����
										// ���� �Լ����� ������ ���� �״�� ����

    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULTWINDOW));
	// ������ â�� ����� ������ ������ �� ����(���� ǥ����)
	
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	// ���콺 Ŀ���� ����
	
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	// ������ â ��� ����

	wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_DEFAULTWINDOW);
	// â ��ܿ� �ִ� �޴� ����

    wcex.lpszClassName  = szWindowClass;
	// ���� ������ �̸��� ���� : �������̸� ������Ʈ �̸��� ��ġ���� �ۼ��Ͽ� ũ�� �������� ����

    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	// â ��ܿ� �ִ� ���� ������ ����� ����

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   // CreateWindowW : ����� ���� �������� ���� â�� �����ϴ� �۾��� ����

   RECT	rcWnd{ 0, 0, WINCX, WINCY };

   // rcWnd = rcWnd + �⺻ â ��Ÿ�� �ɼ� + �޴� �� ������ ��� ����
   AdjustWindowRect(&rcWnd, WS_OVERLAPPEDWINDOW, FALSE);

   HWND hWnd = CreateWindowW(szWindowClass,		// �ռ� ������ ������ Ŭ������ ������ Ŭ���� �̸��� �״�� �־���
						   szTitle,				// ������ ��ܿ� ��Ÿ�� ���ڿ��� ����
						   WS_OVERLAPPEDWINDOW,	// ������� �ϴ� ������ ��Ÿ���� ����(�⺻ �� : �⺻ ������ ��� ����)
						   CW_USEDEFAULT, 0,	// ��ü ��ũ�� �� ��� ��ġ�� â�� ������ ���ΰ�(X,Y ��ǥ)
						   rcWnd.right - rcWnd.left, 
						   rcWnd.bottom - rcWnd.top,			// â�� ����, ���� ������
						   nullptr,				// �θ� �����찡 �ִٸ� �θ� �������� �ڵ��� ����(�θ� ������ NULL)
						   nullptr,				// �����쿡�� ����� �޴��� �ڵ�(�������Ϳ� ��ϵ� �޴� ���¸� ����Ϸ��� NULL)
						   hInstance,			// �����츦 ����� ��ü, ���α׷��� �ڵ��� ����
						   nullptr);			// �ü���� Ư���� �������� ���(��)

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

// ���̺귯�� : ���̳ʸ��� ����(������)�� �Լ����� ��Ƴ��� ����
// 
// �ڵ� ������ ���� ��â�� ��� �� �ϳ��� �ٸ� ���α׷����� ����� �� �ֵ��� �ü���� ����Ʈ���� �����ڿ� ���� ����
// ���̺귯���� ��ټ� �Լ����� �Լ��� ���� �� ������� �ʿ�� �ϱ� ������ ��ũ�Ǳ� �� ��ó���⿡ ���� �ش� ��� ������ ���α׷��� ���� ���Ѿ� ��
// ���̺귯������ ������� ���α׷��� ��ũ�Ǿ� ������ ������ ������ ���α׷��� �̷�� ��

// window �ʼ� ���̺귯��

// 1. kernel : �޸𸮸� �����ϰ� ���α׷��� ����
// 2. user : ���� �������̽��� ������ â�� ����
// 3. gdi : ȭ�� ó���� �׷����� ���

RECT	rc{ 400, 400, 500, 500 };
list<RECT>		BulletList;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	//case WM_CREATE:

	//	SetTimer(hWnd, 0, 0, NULL);
	//	// 2���� : Ÿ�̸��� id ��ȣ, �����쿡�� ���� ���� Ÿ�̸Ӱ� ������ �� �����Ƿ� �����ϱ� ���� Ÿ�̸� ��ȣ
	//	// 3���� : Ÿ�̸� �ֱ�, 0���� �����ϸ� 1000�� 1�� �÷� �ð� ���� �߻�
	//	// 4���� : NULL�� ��� ������ �ֱ�(3����)��� WM_TIMER �޼����� �߻���Ŵ
	//	break;

	//case WM_TIMER:
	//	InvalidateRect(hWnd, NULL, TRUE);
	//	// ������ ���� �Լ�

	///*	2���� : ������ �ȿ��� ������ ������ ����(RECT ����ü �ּҸ� ������, NULL�� ��� ������ ��ü ������ ����)
	//	3���� : FALSE - ���� �׸��� �κи� ����
	//			TRUE - �׷��� ���� �ʴ� �κе� ����*/
	//	break;


    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �޴� ������ ���� �м��մϴ�.
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

			//// HDC : ��¿� ���� ������ �����ϴ� ����ü
   //         HDC hdc = BeginPaint(hWnd, &ps);

			//// 2, 3���� : Ŀ�� �������� ��ġ ��ǥ(x,y)
			//// 4���� : Ŀ���� �̵��ϱ� �� ��ġ�� output���� ��ȯ
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

			//// �簢�� �׸��� �Լ�
			////Rectangle(hdc, 100, 100, 200, 200);

			//// �� �׸��� �Լ�
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

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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

// �Լ� ȣ�� �Ծ�

// - �Լ��� ������ ����Ǹ� �Ҵ�Ǿ��� ���� �޸𸮸� �����ؾ� ��
// - �Լ��� ȣ���� ȣ���(caller)���� ������ ������ �ƴϸ� ȣ�� ���� ��ȣ����(callee)���� �� ���ΰ��� ���� ���, �Ǵ� �Ծ�

// __cdecl : c / c++ �⺻ �Լ� ȣ�� �Ծ�, __cdecl�� ȣ����� stack�� ����, ���� ���� �Լ�(���� �ڱ� �ڽſ��� � �Ű� ������ �󸶳� ������ ��), ������ ������ ���� �� �� ����

// __stdcall : WINAPI �⺻ �Լ� ȣ�� �Ծ�, ��ȣ������ callee�� stack�� ����, ���� ���� �Լ�(�Ű� ������ �����Ǿ� �־� ��ȣ���ڰ� � ���� ���� �� �˰� ����), ���� ������ stack�� ������ �� �ִ�
// __fastcall : �Լ� ȣ���� ������ ó���ϱ� ���� �Ծ�, ecx�� edx��� �������͸� ���� ����, �������͸� ����ϰ� �ִ� ������ �Լ� ȣ���� �������� �ٰ�
// __thiscall : this �����͸� �Ű� ������ �Ѱ� �޾��� �� ����ϴ� ȣ�� �Ծ�

