#include "stdafx.h"
#include "PingPongBall.h"

#include "Player.h"
#include "New_KeyMgr.h"
#include "CTimeMgr.h"

#include "ObjMgr.h"

#include <assert.h>


BYTE CPingPongBall::m_iCount = 0;


CPingPongBall::CPingPongBall()
	: m_pPlayer(nullptr)
	, m_fAngle(0.f)
	, m_fPullGauge(0.f)
	, m_fFrictionforce(1.f)
	, m_bReadyPull(false)
	, m_bStartMove(false)

{
	++m_iCount;
}


CPingPongBall::~CPingPongBall()
{
	--m_iCount;
	Release();
}

void CPingPongBall::Initialize()
{
	m_tInfo.vPos = { WINCX / 2.f - 100, WINCY / 2.f -200, 0.f };
	m_eObjType = OBJID::OBJ_PINGPONGBALL;
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();

	assert(m_pPlayer);

	m_vColliderPos = { m_tInfo.vPos.x, m_tInfo.vPos.y ,0.f};
	m_vColliderSize = { 20.f, 20.f ,0.f};


	m_vPosinPoint = { m_tInfo.vPos.x, m_tInfo.vPos.y ,0.f };
	m_vOriginPosinPoint = m_vPosinPoint;


	m_vPosinLeftPoint = { m_vPosinPoint.x - 20.f, m_vPosinPoint.y - 20.f,0.f };
	m_vOriginPosinLeftPoint = m_vPosinLeftPoint;

	m_vPosinRightPoint = { m_vPosinPoint.x - 20.f, m_vPosinPoint.y + 20.f,0.f };
	m_vOriginPosinRightPoint = m_vPosinRightPoint;




	m_tInfo.vDir = { 0.f,0.f,0.f };
	m_tInfo.vLook = { 0.f,-1.f,0.f };
	m_fSpeed = 30.f;


}

void CPingPongBall::Initialize(D3DXVECTOR3 _v)
{
	m_tInfo.vPos = { _v.x, _v.y, _v.z };
	m_eObjType = OBJID::OBJ_PINGPONGBALL;
	m_vOriginPos = m_tInfo.vPos;
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();

	assert(m_pPlayer);

	m_vColliderPos = { m_tInfo.vPos.x, m_tInfo.vPos.y ,0.f };
	m_vColliderSize = {PINGPONG_RADIUS, PINGPONG_RADIUS, 0.f};


	m_vPosinPoint = { m_tInfo.vPos.x, m_tInfo.vPos.y ,0.f };
	m_vOriginPosinPoint = m_vPosinPoint;


	m_vPosinLeftPoint = { m_vPosinPoint.x - 20.f, m_vPosinPoint.y - 20.f,0.f };
	m_vOriginPosinLeftPoint = m_vPosinLeftPoint;

	m_vPosinRightPoint = { m_vPosinPoint.x - 20.f, m_vPosinPoint.y + 20.f,0.f };
	m_vOriginPosinRightPoint = m_vPosinRightPoint;




	m_tInfo.vDir = { 0.f,0.f,0.f };
	m_tInfo.vLook = { 0.f,-1.f,0.f };
	m_fSpeed = 30.f;
}




int CPingPongBall::Update()
{	
	if (m_tInfo.vPos.x < 0
		|| m_tInfo.vPos.x > WINCX
		|| m_tInfo.vPos.y < 0
		|| m_tInfo.vPos.y > WINCY)
	{
		return OBJ_DEAD;
	}


	CPlayer* pPlayer = (CPlayer*)m_pPlayer;

	if (!pPlayer->IsPlayerTurn())
	{	
		Key_Input();
	}
	
	Move();
	CollisionMove();

	return OBJ_NOEVENT;
}

void CPingPongBall::Late_Update()
{
	m_vColliderPos.x = m_tInfo.vPos.x;
	m_vColliderPos.y = m_tInfo.vPos.y;


	D3DXMATRIX PosinmatWorld, PosinmatScale, PosinmatRotZ, PosinmatTrans;

	D3DXMatrixIdentity(&PosinmatWorld); // 항등 행렬로 만들어준다 
	D3DXMatrixRotationZ(&PosinmatRotZ, D3DXToRadian(-m_fAngle));
	D3DXMatrixTranslation(&PosinmatTrans, m_vPosinPoint.x, m_vPosinPoint.y, 0.f);



	PosinmatWorld = PosinmatRotZ * PosinmatTrans;

	m_vPosinPoint = m_vOriginPosinPoint;
	m_vPosinPoint -= { m_vOriginPos.x, m_vOriginPos.y, 0.f};
	D3DXVec3TransformCoord(&m_vPosinPoint, &m_vPosinPoint, &PosinmatWorld);

	m_vPosinLeftPoint = m_vOriginPosinLeftPoint;
	m_vPosinLeftPoint -= {m_vOriginPos.x, m_vOriginPos.y, 0.f};
	D3DXVec3TransformCoord(&m_vPosinLeftPoint, &m_vPosinLeftPoint, &PosinmatWorld);			// 회전을 해야함 

	m_vPosinRightPoint = m_vOriginPosinRightPoint;
	m_vPosinRightPoint -= {m_vOriginPos.x, m_vOriginPos.y, 0.f};
	D3DXVec3TransformCoord(&m_vPosinRightPoint, &m_vPosinRightPoint, &PosinmatWorld);
}

void CPingPongBall::Render(HDC hDC)
{
	//Ellipse(hDC,
	//	(int)(m_tInfo.vPos.x - PINGPONG_RADIUS / 2.f)
	//	, (int)(m_tInfo.vPos.y - PINGPONG_RADIUS / 2.f)
	//	, (int)(m_tInfo.vPos.x + PINGPONG_RADIUS / 2.f)
	//	, (int)(m_tInfo.vPos.y + PINGPONG_RADIUS / 2.f));


	HPEN hMyPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hMyPen);

	Ellipse(hDC,
		(int)(m_vColliderPos.x - m_vColliderSize.x / 2.f)
		, (int)(m_vColliderPos.y - m_vColliderSize.y / 2.f)
		, (int)(m_vColliderPos.x + m_vColliderSize.x / 2.f)
		, (int)(m_vColliderPos.y + m_vColliderSize.y / 2.f));

	SelectObject(hDC, hOldPen);
	DeleteObject(hMyPen);



	if (m_bReadyPull)
	{
		MoveToEx(hDC, m_tInfo.vPos.x, m_tInfo.vPos.y, nullptr);
		LineTo(hDC, m_vPosinPoint.x, m_vPosinPoint.y);

		LineTo(hDC, m_vPosinLeftPoint.x, m_vPosinLeftPoint.y);				// 왼쪽
		MoveToEx(hDC, m_vPosinPoint.x, m_vPosinPoint.y, nullptr);
		LineTo(hDC, m_vPosinRightPoint.x, m_vPosinRightPoint.y);			// 오른쪽

	}

}


void CPingPongBall::Release()
{

}

void CPingPongBall::Key_Input()
{
	if (New_KeyMgr::CreateSingleTonInst()->GetKeyState(KEY::LBUTTON) == KEY_STATE::TAP)
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		float fLeftX = m_tInfo.vPos.x - PINGPONG_RADIUS / 2.f;
		float fTopY = m_tInfo.vPos.y - PINGPONG_RADIUS / 2.f;
		float fRightX = m_tInfo.vPos.x + PINGPONG_RADIUS / 2.f;
		float fBottomY = m_tInfo.vPos.y + PINGPONG_RADIUS / 2.f;

		if (pt.x > fLeftX
			&& pt.x < fRightX
			&& pt.y > fTopY
			&& pt.y < fBottomY)
		{
			m_bReadyPull = true;
		}
	}

	if (New_KeyMgr::CreateSingleTonInst()->GetKeyState(KEY::LBUTTON) == KEY_STATE::HOLD)
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		if (m_bReadyPull)
		{
			m_vPosinPoint.x = pt.x;
			m_vPosinPoint.y = pt.y;
		}


		D3DXVECTOR3 vPosin = { m_vPosinPoint.x - m_tInfo.vPos.x, m_vPosinPoint.y - m_tInfo.vPos.y, 0.f };
		D3DXVECTOR3 vPerpendicular = { m_tInfo.vPos.x + 1 - m_tInfo.vPos.x , m_tInfo.vPos.y - m_tInfo.vPos.y , 0.f };

		D3DXVECTOR3 vPosinNor;
		D3DXVECTOR3 vPerpendicularNor;


		float fLength = D3DXVec3Length(&vPosin);    // 이걸  0 ~ 100으로 치환하고 싶음 		
		float fRatio = (fLength / fMaxpull) * 100;
		m_fPullGauge = m_fSpeed * fRatio;			// 내가 날아갈 힘의 양 


		// 게이지 값도 이상하고
		// 방향도 이상함 

		D3DXVec3Normalize(&vPosinNor, &vPosin);
		m_tInfo.vDir = (vPosinNor * -1);			// 내가 날아갈 방향은 내가 당긴벡터의 반대 방향

		D3DXVec3Normalize(&vPerpendicularNor, &vPerpendicular);

		float fDot = D3DXVec3Dot(&vPosinNor, &vPerpendicularNor);
		float fRadian = acos(fDot);

		m_fAngle = D3DXToDegree(fRadian);


		if (m_vPosinPoint.y > m_tInfo.vPos.y)
		{
			m_fAngle *= -1;
		}

	}

	if (New_KeyMgr::CreateSingleTonInst()->GetKeyState(KEY::LBUTTON) == KEY_STATE::AWAY)
	{
		m_vPosinPoint.x = m_tInfo.vPos.x;	   // 없어도 될거같은데 이해 못했으 
		m_vPosinPoint.y = m_tInfo.vPos.y;	   // 없어도 될거같은데 이해 못했으 
		
		if (m_bReadyPull)
		{
			m_bReadyPull = false;
			m_bStartMove = true;
		}

	}
}

void CPingPongBall::Move()
{
	if (!m_bStartMove)
		return;

	// 각도 알고있고
	// 얼마나 당겼는지 알아야함   (m_f게이지 알고있고)
	D3DXMATRIX matScale, matRotZ, matTrans;

	D3DXMatrixIdentity(&m_tInfo.matWorld);


	m_tInfo.vPos += (m_tInfo.vDir * m_fPullGauge * m_fFrictionforce) * fDT;		// 델타 타임필요 // 여기수정필요

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matTrans;


	m_tInfo.vPos -= { m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f};		// 원점으로 이동후 
	D3DXVec3TransformCoord(&m_tInfo.vPos, &m_tInfo.vPos, &m_tInfo.matWorld);


	if (m_fFrictionforce < 0.001)
	{
		m_fFrictionforce = 1.f;
		m_bStartMove = false;

		CPlayer* pPlayer = (CPlayer*)m_pPlayer;
		pPlayer->SetPlayerTurn(true);
	}

	m_fFrictionforce *= 0.8f;
}


void CPingPongBall::CollisionMove()
{
	if (m_pCollisionObj)
	{
		m_bStartMove = false;

		CPlayer* pPlayer = (CPlayer*)m_pPlayer;

		if (pPlayer->IsPlayerTurn())  // 상대 턴일때 
		{
			m_tInfo.vPos += (m_pCollisionObj->Get_Info().vDir * (((CPlayer*)m_pCollisionObj)->GetGauge() * 2) * m_fFrictionforce) * fDT;

			if (m_fFrictionforce < 0.001)
			{
				m_fFrictionforce = 1.f;
				m_pCollisionObj = nullptr;
			}
			else
				m_fFrictionforce *= 0.8f;
		}
		else
		{
			m_tInfo.vPos -= (m_tInfo.vDir * (m_fPullGauge / 0.4f) * m_fFrictionforce) * fDT;

			if (m_fFrictionforce < 0.001)
			{
				m_fFrictionforce = 1.f;
				m_pCollisionObj = nullptr;
			}
			else
				m_fFrictionforce *= 0.8f;
		}
	}

	


}
