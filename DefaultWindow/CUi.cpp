#include "stdafx.h"
#include "CUi.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "BmpMgr.h"

CUi::CUi() 
	:m_ePreState(UI_END), m_eCurState(UI_END)
{
	m_tInfo = { 100.f, WINCY / 2.f, 200.f, 200.f }; //�⺻��

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

	// ��Ʈ�� ��� �Լ�
	/*BitBlt(hDC,		// �������� �׸��� �׸� dc
		m_tRect.left + iScrollX,	// ���� ���� ��ġ�� left
		m_tRect.top,				// ���� ���� ��ġ�� top
		m_tInfo.fCX,				// ���� ���� ���� ����
		m_tInfo.fCY,				// ���� ���� ���� ����
		hMemDC,	// ��Ʈ���� ������ �ִ� dc
		0,							// ����� ��Ʈ���� ���� x��ǥ
		0,							// ����� ��Ʈ���� ���� y��ǥ
		SRCCOPY);					// ��� ȿ��(�׷��� ���)
		*/

	GdiTransparentBlt(hDC, // �������� �׸��� �׸� dc
		m_tRect.left , // ���� ���� ��ġ�� left
		m_tRect.top ,			 // ���� ���� ��ġ�� top
		(int)m_tInfo.fCX,			 // ���� ���� ���� ����
		(int)m_tInfo.fCY,			 // ���� ���� ���� ����
		hMemDC,					// ��Ʈ���� ������ �ִ� dc
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,						// ����� ��Ʈ���� ���� x��ǥ
		m_tFrame.iMotion * (int)m_tInfo.fCY,						// ����� ��Ʈ���� ���� y��ǥ
		(int)m_tInfo.fCX,			// ����� ��Ʈ���� ���� ������
		(int)m_tInfo.fCY,			// ����� ��Ʈ���� ���� ������
		RGB(0, 128, 128));	// ������ �ȼ��� ���� ��
}

void CUi::Release()
{
}