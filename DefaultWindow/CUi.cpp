#include "stdafx.h"
#include "CUi.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "BmpMgr.h"

CUi::CUi() 
	:m_ePreState(UI_END), m_eCurState(UI_END)
{
	m_tInfo = { 100.f, WINCY / 2.f, 200.f, 200.f }; //기본값

	m_eCurState = UI_IDLE;
}


CUi::~CUi()
{
	Release();
}



void CUi::Initialize()
{
	m_tInfo = { 100.f, WINCY / 2.f, 200.f, 200.f };
	m_fSpeed = 5.f;



	m_tFrame = { 0, 3, 0, 200, GetTickCount() };
	m_pFrameKey = L"CUI";

	m_eRender = RENDER_GAMEOBJECT;

}
int CUi::Update()
{


	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CUi::Late_Update()
{

	__super::Move_Frame();

}

void CUi::Render(HDC hDC)
{


	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	// 비트맵 출력 함수
	/*BitBlt(hDC,		// 최종적인 그림을 그릴 dc
		m_tRect.left + iScrollX,	// 복사 받을 위치의 left
		m_tRect.top,				// 복사 받을 위치의 top
		m_tInfo.fCX,				// 복사 받을 가로 길이
		m_tInfo.fCY,				// 복사 받을 세로 길이
		hMemDC,	// 비트맵을 가지고 있는 dc
		0,							// 출력할 비트맵의 시작 x좌표
		0,							// 출력할 비트맵의 시작 y좌표
		SRCCOPY);					// 출력 효과(그래도 출력)
		*/

	GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
		m_tRect.left , // 복사 받을 위치의 left
		m_tRect.top ,			 // 복사 받을 위치의 top
		(int)m_tInfo.fCX,			 // 복사 받을 가로 길이
		(int)m_tInfo.fCY,			 // 복사 받을 세로 길이
		hMemDC,					// 비트맵을 가지고 있는 dc
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,						// 출력할 비트맵의 시작 x좌표
		m_tFrame.iMotion * (int)m_tInfo.fCY,						// 출력할 비트맵의 시작 y좌표
		(int)m_tInfo.fCX,			// 출력할 비트맵의 가로 사이즈
		(int)m_tInfo.fCY,			// 출력할 비트맵의 세로 사이즈
		RGB(0, 128, 128));	// 제거할 픽셀의 색상 값
}

void CUi::Release()
{
}