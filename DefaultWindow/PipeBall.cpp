#include "stdafx.h"
#include "PipeBall.h"
#include	"ObjMgr.h"
PipeBall::PipeBall()
	:m_b_W_flag(false)
	, m_b_S_flag(false)
{


}
PipeBall::~PipeBall()
{
	Release();
}

void PipeBall::Key_Input()
{

	/*w,s :포신방향으로 위아래
	a,d : 포신 회전
	<-,-> : 플레이어 좌우회전
	up,down ,보는 방향으로 위아래*/

	if (GetAsyncKeyState(0x57)) // W  - 포신으 보는쪽 
	{
		m_tInfo.vPos.y -= m_fSpeed;

		//m_b_W_flag = true;
	/*	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;*/
	}
	/*else
	{
		m_b_W_flag = false;
	}*/
	if (GetAsyncKeyState(0x53)) //s 
	{
		m_tInfo.vPos.y += m_fSpeed;
		//m_b_S_flag = true;
		/*D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * -m_fSpeed;*/
	}
	else
	{
		//m_b_S_flag = false;
	}

	if (GetAsyncKeyState(0x41)) // a
	{
		m_tInfo.vPos.x -= m_fSpeed;
	}
		//m_fAngle += D3DXToRadian(3.f);

	if (GetAsyncKeyState(0x44)) //d 
	{
		m_tInfo.vPos.x += m_fSpeed;
	}
								//m_fAngle -= D3DXToRadian(3.f);




}

void PipeBall::Initialize()
{
	m_b_S_flag = false;
	m_b_W_flag = false;
	//m_tInfo.vPos = { WINCX / 2.00000f, WINCY / 2.000000f, 0.f };
	m_tInfo.vPos = { 100.f, 100.f, 0.f };
	m_start_x = m_tInfo.vPos.x;
	m_start_y = m_tInfo.vPos.y;
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_fSpeed = 3.f;
	m_fAngle = 0.f;  //포신각도

	m_fWidth = 6.000000f;  //이전 cx cy 개념


	m_vPoint[0] = { m_tInfo.vPos.x - m_fWidth, m_tInfo.vPos.y - m_fWidth, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + m_fWidth, m_tInfo.vPos.y - m_fWidth, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + m_fWidth, m_tInfo.vPos.y + m_fWidth, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - m_fWidth, m_tInfo.vPos.y + m_fWidth, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vPoint_Origin[i] = m_vPoint[i];




}

int PipeBall::Update()
{


	Key_Input();




	//D3DXMATRIX	matScale, matRotZ, matTrans;

	//D3DXMatrixScaling(&matScale, -1.f, 1.f, 1.f);
	//// // 크기 변환 행렬을 만들어주는 함수
	//D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	//D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	//// // 이동 변환 행렬을 만들어주는 함수

	//m_tInfo.matWorld = matScale * matRotZ * matTrans;
	//for (int i = 0; i < 4; ++i)
	//{
	//	m_vPoint[i] = m_vPoint_Origin[i];
	//	//m_vPoint[i] -= { WINCX * 0.5f, WINCY * 0.5f, 0.f};
	//	//m_vPoint[i] -= { m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f};
	//	m_vPoint[i] -= { m_start_x, m_start_y, 0.f};

	//	D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	//	/*if (m_b_W_flag)
	//	{
	//		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	//		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	//	}
	//	if (m_b_S_flag)
	//	{
	//		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	//		m_tInfo.vPos += m_tInfo.vDir * -m_fSpeed;
	//	}*/
	//}

	return OBJ_NOEVENT;


}

void PipeBall::Late_Update()
{

}

void PipeBall::Render(HDC hDC)
{
	if (CObjMgr::Get_Instance()->Get_Player_visible())
	{


		m_vPoint[0] = { m_tInfo.vPos.x - m_fWidth, m_tInfo.vPos.y - m_fWidth, 0.f };
		m_vPoint[2] = { m_tInfo.vPos.x + m_fWidth, m_tInfo.vPos.y + m_fWidth, 0.f };

		RECT rect = { m_tInfo.vPos.x - m_fWidth, m_tInfo.vPos.y - m_fWidth,
						m_tInfo.vPos.x + m_fWidth, m_tInfo.vPos.y + m_fWidth };

		Ellipse(hDC, rect.left, rect.top, rect.right, rect.bottom);
	}
	/*HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN OldPen = (HPEN)SelectObject(hDC, hPen);
	SelectObject(hDC, hPen);

	MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);
	LineTo(hDC, (int)m_vPoint[1].x, (int)m_vPoint[1].y);
	SelectObject(hDC, OldPen);
	DeleteObject(hPen);

	for (int i = 2; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

		if (i > 0)
			continue;

	}
	LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);*/



}

void PipeBall::Release()
{
}


