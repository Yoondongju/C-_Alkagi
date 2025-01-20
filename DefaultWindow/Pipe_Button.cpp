#include "stdafx.h"
#include "Pipe_Button.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "MiniGame_lee.h"
Pipe_Button::Pipe_Button()
{


}
Pipe_Button::~Pipe_Button()
{
	Release();
}

void Pipe_Button::Key_Input()
{
;	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	RECT rect = { m_tInfo.vPos.x - m_fWidth  , m_tInfo.vPos.y - m_fWidth * 0.5f,
				m_tInfo.vPos.x   + m_fWidth,   m_tInfo.vPos.y + m_fWidth * 0.5f };

	if (PtInRect(&rect, pt) )
	{
		if (CKeyMgr::Get_Instance()->Key_Down(0x01))
		{
			CObjMgr::Get_Instance()->Set_Player_visible(true);
		}

	}


}

void Pipe_Button::Initialize()
{
	
	//m_tInfo.vPos = { WINCX / 2.00000f, WINCY / 2.000000f, 0.f };
	m_tInfo.vPos = { 700.f, 100.f, 0.f };

	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_fSpeed = 3.f;
	m_fAngle = 0.f;  //포신각도

	m_fWidth = 50.000000f;  //이전 cx cy 개념


	



}

int Pipe_Button::Update()
{


	Key_Input();





	return OBJ_NOEVENT;


}

void Pipe_Button::Late_Update()
{

}

void Pipe_Button::Render(HDC hDC)
{
	RECT rect = { m_tInfo.vPos.x - m_fWidth  , m_tInfo.vPos.y - m_fWidth * 0.5f,
					m_tInfo.vPos.x + m_fWidth, m_tInfo.vPos.y + m_fWidth * 0.5f };

	Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
	
	wstring _wstr2 = L"Start";
	TextOut(hDC, m_tInfo.vPos.x - 15 , m_tInfo.vPos.y-5, _wstr2.c_str(), _wstr2.size());


}

void Pipe_Button::Release()
{
}


