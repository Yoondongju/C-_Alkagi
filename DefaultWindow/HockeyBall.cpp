#include "stdafx.h"
#include "HockeyBall.h"

CHockeyBall::CHockeyBall()
{
}

CHockeyBall::~CHockeyBall()
{
	Release();
}

void CHockeyBall::Initialize()
{
	Init_LocalSize(20.f);

	m_tInfo.vPos = { 300.f, 370.f, 0.f};

	//m_tInfo.vDir = { (float)cos(45.f), (float)sin(45.f), 0.f };

	m_tInfo.vDir = { 0.f, 0.f, 0.f };
	m_fSpeed = 8.f;
}

int CHockeyBall::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CHockeyBall::Late_Update()
{
	Collision_Map();
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	TranslationLocalToWorld();
}

void CHockeyBall::Render(HDC hDC)
{
	Ellipse(hDC,
		int(m_vPoint[0].x),
		int(m_vPoint[0].y),
		int(m_vPoint[1].x),
		int(m_vPoint[1].y));
}

void CHockeyBall::Release()
{
}

void CHockeyBall::Collision_Map()
{
	D3DXVECTOR3 _vNormal = {0.f, 0.f, 0.f};
	float fDot = 0.f;

	if (m_tInfo.vPos.x - m_fLocalSize < m_pMapSize->left) // left
	{
		m_tInfo.vPos.x = m_pMapSize->left + m_fLocalSize;
		_vNormal = { -1.f, 0.f, 0.f };
	}
	else if (m_tInfo.vPos.x + m_fLocalSize > m_pMapSize->right) // right
	{
		m_tInfo.vPos.x = m_pMapSize->right - m_fLocalSize;
		_vNormal = { 1.f, 0.f, 0.f };
	}
	else if (m_tInfo.vPos.y - m_fLocalSize < m_pMapSize->top) // top
	{
		m_tInfo.vPos.y = m_pMapSize->top + m_fLocalSize;
		_vNormal = { 0.f, 1.f, 0.f };
	}
	else if (m_tInfo.vPos.y + m_fLocalSize > m_pMapSize->bottom) // bottom
	{
		m_tInfo.vPos.y = m_pMapSize->bottom - m_fLocalSize;
		_vNormal = { 0.f, -1.f, 0.f };
	}

	fDot = D3DXVec3Dot(&_vNormal, &m_tInfo.vDir);
	m_tInfo.vDir += (_vNormal * 2 * -fDot);
}
