#include "stdafx.h"
#include "Player.h"

#include "New_KeyMgr.h"

#include "CTimeMgr.h"

#include "PingPongBall.h"
#include "ObjMgr.h"

bool CPlayer::m_bPlayerTurn = true;
BYTE CPlayer::m_iCount = 0;

CPlayer::CPlayer()
	: m_fAngle(0.f)	
	, m_fPullGauge(0.f)
	, m_fFrictionforce(1.f)
	, m_bReadyPull(false)
	, m_bStartMove(false)
	, m_bCopying(false)
	, m_bCopyInstance(false)
{
	++m_iCount;
}

CPlayer::~CPlayer()
{
	--m_iCount;
	Release();
}

void CPlayer::Key_Input()
{
	if (New_KeyMgr::CreateSingleTonInst()->GetKeyState(KEY::LBUTTON) == KEY_STATE::TAP)
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		float fLeftX = m_tInfo.vPos.x - m_vColliderSize.x / 2.f;
		float fTopY = m_tInfo.vPos.y - m_vColliderSize.y / 2.f;
		float fRightX = m_tInfo.vPos.x + m_vColliderSize.x / 2.f;
		float fBottomY = m_tInfo.vPos.y + m_vColliderSize.y / 2.f;

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


		float fLength = D3DXVec3Length(&vPosin);    // �̰�  0 ~ 100���� ġȯ�ϰ� ���� 		
		float fRatio = (fLength / fMaxpull) * 100;
		m_fPullGauge = m_fSpeed * fRatio;			// ���� ���ư� ���� �� 


		// ������ ���� �̻��ϰ�
		// ���⵵ �̻��� 

		D3DXVec3Normalize(&vPosinNor, &vPosin);
		m_tInfo.vDir = (vPosinNor * -1);			// ���� ���ư� ������ ���� ��交���� �ݴ� ����

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
		m_vPosinPoint.x = m_tInfo.vPos.x;	   // ��� �ɰŰ����� ���� ������ 
		m_vPosinPoint.y = m_tInfo.vPos.y;	   // ��� �ɰŰ����� ���� ������ 

		if (m_bReadyPull)
		{
			m_bStartMove = true;
			m_bReadyPull = false;

		}
	}

	if (New_KeyMgr::CreateSingleTonInst()->GetKeyState(KEY::Z) == KEY_STATE::TAP)
	{
		if(m_vSize.x < 3.f
			&& m_vSize.y < 3.f)
				m_vSize *= 3.f;
	}

	if (New_KeyMgr::CreateSingleTonInst()->GetKeyState(KEY::X) == KEY_STATE::TAP)
	{
		m_bCopying = true;	
	}

	if (New_KeyMgr::CreateSingleTonInst()->GetKeyState(KEY::C) == KEY_STATE::TAP)
	{
		D3DXMATRIX matScale, matRotZ, matTrans;

		D3DXMatrixIdentity(&m_tInfo.matWorld);
		D3DXMatrixTranslation(&matTrans, m_vOriginPos.x, m_vOriginPos.y, 0.f);
		m_tInfo.matWorld = matTrans;


		m_tInfo.vPos -= { m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f};		// �������� �̵��� 
		D3DXVec3TransformCoord(&m_tInfo.vPos, &m_tInfo.vPos, &m_tInfo.matWorld);


		for (int i = 0; i < 4; ++i)
		{
			m_vPoint[i] = m_vOriginPoint[i];
			m_vPoint[i] -= {m_vOriginPos.x, m_vOriginPos.y, m_vOriginPos.z};
			D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
		}




	}

}



void CPlayer::Initialize()
{

}

void CPlayer::Initialize(D3DXVECTOR3 _v , D3DXVECTOR3 _Dir)
{
	m_tInfo.vPos = { _v.x,  _v.y,  _v.z };
	m_vOriginPos = m_tInfo.vPos;

	m_vSize = { 1.f,1.f,0.f };

	m_eObjType = OBJID::OBJ_PLAYER;







	m_vColliderPos = { m_tInfo.vPos.x, m_tInfo.vPos.y ,0.f };
	m_vColliderSize = { PLAYER_SIZE,PLAYER_SIZE ,0.f };
	m_vColliderOriginSize = m_vColliderSize;


	m_vPoint[0] = {m_vOriginPos.x - PLAYER_SIZE / 2.f ,m_vOriginPos.y -PLAYER_SIZE / 2.f, m_tInfo.vPos.z };
	m_vPoint[1] = {m_vOriginPos.x + PLAYER_SIZE / 2.f ,m_vOriginPos.y -PLAYER_SIZE / 2.f, m_tInfo.vPos.z };
	m_vPoint[2] = {m_vOriginPos.x + PLAYER_SIZE / 2.f ,m_vOriginPos.y +PLAYER_SIZE / 2.f, m_tInfo.vPos.z };
	m_vPoint[3] = {m_vOriginPos.x - PLAYER_SIZE / 2.f ,m_vOriginPos.y +PLAYER_SIZE / 2.f, m_tInfo.vPos.z };


	for (int i = 0; i < 4; ++i)
	{
		m_vOriginPoint[i]  =  m_vPoint[i];
	}





	m_vPosinPoint = { m_tInfo.vPos.x, m_tInfo.vPos.y ,0.f };
	m_vOriginPosinPoint = m_vPosinPoint;


	m_vPosinLeftPoint = { m_vPosinPoint.x - 20.f, m_vPosinPoint.y - 20.f,0.f };
	m_vOriginPosinLeftPoint = m_vPosinLeftPoint;

	m_vPosinRightPoint = { m_vPosinPoint.x - 20.f, m_vPosinPoint.y + 20.f,0.f };
	m_vOriginPosinRightPoint = m_vPosinRightPoint;




	m_tInfo.vDir = _Dir;
	m_tInfo.vLook = { 0.f,-1.f,0.f };
	m_fSpeed = 30.f;

}

int CPlayer::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	if (m_tInfo.vPos.x < 0
		|| m_tInfo.vPos.x > WINCX
		|| m_tInfo.vPos.y < 0
		|| m_tInfo.vPos.y > WINCY)
	{
		return OBJ_DEAD;
	}




	if (m_bPlayerTurn)
	{
		Key_Input();
	}





	Move();
	CollisionMove();


	return OBJ_NOEVENT;
}



void CPlayer::Move()
{
	if (!m_bStartMove)
		return;

	// ���� �˰��ְ�
	// �󸶳� ������ �˾ƾ���   (m_f������ �˰��ְ�)
	D3DXMATRIX matScale, matRotZ, matTrans;

	D3DXMatrixIdentity(&m_tInfo.matWorld);


	m_tInfo.vPos += (m_tInfo.vDir * m_fPullGauge * m_fFrictionforce) * fDT;		// ��Ÿ Ÿ���ʿ� // ��������ʿ�

	D3DXMatrixScaling(&matScale, m_vSize.x, m_vSize.y, m_vSize.z);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matTrans;

	m_tInfo.vPos -= { m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f};		// �������� �̵��� 
	D3DXVec3TransformCoord(&m_tInfo.vPos, &m_tInfo.vPos, &m_tInfo.matWorld);



	if (m_fFrictionforce < 0.001)
	{
		m_fFrictionforce = 1.f;
		m_bStartMove = false;
		m_bPlayerTurn = false;			// �浹���ϰ� �����Ÿ� ���������ܿ� �� �Ѿ�� ����

		m_vSize = { 1.f,1.f,0.f };		// �� ������ ��ų ������ ������ �����·� ������������ ��
	}

	if (m_bCopying && m_fFrictionforce < 0.5f)
	{		
		D3DXVECTOR3 vLeftDir = m_tInfo.vDir;
		D3DXVECTOR3 vRightDir = m_tInfo.vDir;
		D3DXMATRIX matRotZ;

		D3DXMatrixIdentity(&m_tInfo.matWorld);
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(-45.f));		
		m_tInfo.matWorld = matRotZ;
		D3DXVec3TransformNormal(&vLeftDir, &m_tInfo.vDir, &m_tInfo.matWorld);
		
		D3DXMatrixIdentity(&m_tInfo.matWorld);
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(45.f));
		m_tInfo.matWorld = matRotZ;
		D3DXVec3TransformNormal(&vRightDir, &m_tInfo.vDir, &m_tInfo.matWorld);


		CPlayer* pCopyLeftPlayer = new CPlayer;
		pCopyLeftPlayer->Initialize(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), vLeftDir);
		pCopyLeftPlayer->m_bStartMove = true;
		pCopyLeftPlayer->m_fPullGauge = (this->m_fPullGauge) * 1.5f;
		pCopyLeftPlayer->m_bCopyInstance = true;
		CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PLAYER, pCopyLeftPlayer);


		CPlayer* pCopyRightPlayer = new CPlayer;
		pCopyRightPlayer->Initialize(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), vRightDir);
		pCopyRightPlayer->m_bStartMove = true;
		pCopyRightPlayer->m_fPullGauge = (this->m_fPullGauge) * 1.5f;
		pCopyRightPlayer->m_bCopyInstance = true;
		CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PLAYER, pCopyRightPlayer);

		m_bCopying = false;
	}


	m_fFrictionforce *= 0.8f;
}

void CPlayer::CollisionMove()
{
	if (m_pCollisionObj)
	{
		m_bStartMove = false;
		if (!m_bPlayerTurn)		// ������϶�  ��밡 ������ �ϴ� �������� ���ĳ�����
		{
			m_tInfo.vPos += (m_pCollisionObj->Get_Info().vDir * (((CPingPongBall*)m_pCollisionObj)->GetGauge() * 2) * m_fFrictionforce) * fDT;

			if (m_fFrictionforce < 0.001)
			{
				m_fFrictionforce = 1.f;
				m_pCollisionObj = nullptr;

				m_bPlayerTurn = true;
			}
			else
				m_fFrictionforce *= 0.8f;
		}
		else					// ���� �϶� ���� ���� �浹�� �ڷ� �з�������
		{
			m_tInfo.vPos -= (m_tInfo.vDir * (m_fPullGauge * 0.4f) * m_fFrictionforce) * fDT;

			if (m_fFrictionforce < 0.001)
			{
			
				m_fFrictionforce = 1.f;
				m_pCollisionObj = nullptr;
				m_bPlayerTurn = false;

				

				m_vSize = { 1.f,1.f,0.f };
			}
			else
				m_fFrictionforce *= 0.8f;
		}
	}




	
}




void CPlayer::Late_Update()
{
	D3DXMATRIX matScale, matRotZ, matTrans;

	D3DXMatrixIdentity(&m_tInfo.matWorld);

	D3DXMatrixScaling(&matScale, m_vSize.x, m_vSize.y, m_vSize.z);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);


	m_tInfo.matWorld = matScale * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= {m_vOriginPos.x, m_vOriginPos.y, m_vOriginPos.z};
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}


	m_vColliderPos.x = m_tInfo.vPos.x;
	m_vColliderPos.y = m_tInfo.vPos.y;

	m_vColliderSize.x = m_vPoint[1].x - m_vPoint[0].x;
	m_vColliderSize.y = m_vPoint[2].y - m_vPoint[1].y;






	D3DXMATRIX PosinmatWorld, PosinmatScale, PosinmatRotZ, PosinmatTrans;

	D3DXMatrixIdentity(&PosinmatWorld); // �׵� ��ķ� ������ش� 
	D3DXMatrixRotationZ(&PosinmatRotZ, D3DXToRadian(-m_fAngle));
	D3DXMatrixTranslation(&PosinmatTrans, m_vPosinPoint.x, m_vPosinPoint.y, 0.f);



	PosinmatWorld = PosinmatRotZ * PosinmatTrans;

	m_vPosinPoint = m_vOriginPosinPoint;
	m_vPosinPoint -= {m_vOriginPos.x, m_vOriginPos.y, 0.f};
	D3DXVec3TransformCoord(&m_vPosinPoint, &m_vPosinPoint, &PosinmatWorld);

	m_vPosinLeftPoint = m_vOriginPosinLeftPoint;
	m_vPosinLeftPoint -= { m_vOriginPos.x, m_vOriginPos.y, 0.f};
	D3DXVec3TransformCoord(&m_vPosinLeftPoint, &m_vPosinLeftPoint, &PosinmatWorld);			// ȸ���� �ؾ��� 

	m_vPosinRightPoint = m_vOriginPosinRightPoint;
	m_vPosinRightPoint -= {m_vOriginPos.x, m_vOriginPos.y, 0.f};
	D3DXVec3TransformCoord(&m_vPosinRightPoint, &m_vPosinRightPoint, &PosinmatWorld);


	if (m_bCopyInstance)
	{
		if(!m_bStartMove && !m_pCollisionObj)
			Set_Dead();
	}
		

}

void CPlayer::Render(HDC hDC)
{
	// 0 -> 1 -> 2 -> 3 

	//for (int i = 0; i < 4; ++i)
	//{
	//	MoveToEx(hDC, m_vPoint[i].x, m_vPoint[i].y, nullptr);
	//	LineTo(hDC, m_vPoint[(i + 1) % 4].x, m_vPoint[(i + 1) % 4].y);
	//}
	//
	//
	//MoveToEx(hDC, m_tInfo.vPos.x, m_tInfo.vPos.y, nullptr);
	//LineTo(hDC, m_vPosinPoint.x, m_vPosinPoint.y);


	Ellipse(hDC,
		  (int)(m_tInfo.vPos.x -  PLAYER_SIZE / 2.f)
		, (int)(m_tInfo.vPos.y - PLAYER_SIZE / 2.f)
		, (int)(m_tInfo.vPos.x + PLAYER_SIZE / 2.f)
		, (int)(m_tInfo.vPos.y + PLAYER_SIZE / 2.f));


	HPEN hMyPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hMyPen);

	Ellipse(hDC,
		  (int)(m_vPoint[0].x)
		, (int)(m_vPoint[1].y)
		, (int)(m_vPoint[2].x)
		, (int)(m_vPoint[3].y));

	SelectObject(hDC, hOldPen);
	DeleteObject(hMyPen);



	if (m_bReadyPull)
	{
		MoveToEx(hDC, m_tInfo.vPos.x, m_tInfo.vPos.y, nullptr);
		LineTo(hDC, m_vPosinPoint.x, m_vPosinPoint.y);

		LineTo(hDC, m_vPosinLeftPoint.x, m_vPosinLeftPoint.y);				// ����
		MoveToEx(hDC, m_vPosinPoint.x, m_vPosinPoint.y, nullptr);
		LineTo(hDC, m_vPosinRightPoint.x, m_vPosinRightPoint.y);			// ������

	}


	RenderChargingUI(hDC);
}


void CPlayer::Release()
{
}

void CPlayer::RenderChargingUI(HDC hDC)
{

}


