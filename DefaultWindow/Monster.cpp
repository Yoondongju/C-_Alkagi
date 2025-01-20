#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_tInfo.vPos = { 100.f, 100.f, 0.f };
	m_fSpeed = 2.f;
}

int CMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	m_tInfo.vDir = m_pPlayer->Get_Info().vPos - m_tInfo.vPos;

	// 벡터의 정규화 : 벡터의 크기를 1로 만들어주는 과정
	float	fLength = sqrt(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);

	m_tInfo.vDir.x /= fLength;
	m_tInfo.vDir.y /= fLength;
	m_tInfo.vDir.z = 0.f;

	// 단위 벡터인 m_tInfo.vDir;
	//m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	return OBJ_NOEVENT;
}

void CMonster::Render(HDC hDC)
{
	Ellipse(hDC,
		int(m_tInfo.vPos.x - 50.f),
		int(m_tInfo.vPos.y - 50.f),
		int(m_tInfo.vPos.x + 50.f),
		int(m_tInfo.vPos.y + 50.f));
}

void CMonster::Release()
{
}
