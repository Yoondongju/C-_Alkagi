#include "stdafx.h"
#include "HockeyEnemy.h"

CHockeyEnemy::CHockeyEnemy()
{
}

CHockeyEnemy::~CHockeyEnemy()
{
	Release();
}

void CHockeyEnemy::Initialize()
{
	Init_LocalSize(40.f);

	m_tInfo.vPos = { (float)WINCX - 120.f, ((float)WINCY * 0.5f), 0.f };
	m_tInfo.vLook = { 1.f, 0.f,0.f };
	m_tInfo.vDir = { 0.f, 1.f, 0.f };
	m_fSpeed = 8.f;
}

int CHockeyEnemy::Update()
{
	return OBJ_NOEVENT;
}

void CHockeyEnemy::Late_Update()
{
	if (m_tInfo.vPos.y - m_fLocalSize < m_pMapSize->top + 20 ||
		m_tInfo.vPos.y + m_fLocalSize > m_pMapSize->bottom - 20)
		m_tInfo.vDir *= -1;

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	TranslationLocalToWorld();
}

void CHockeyEnemy::Render(HDC hDC)
{
	Ellipse(hDC,
		m_vPoint[0].x,
		m_vPoint[0].y,
		m_vPoint[1].x,
		m_vPoint[1].y);
}

void CHockeyEnemy::Release()
{
}
