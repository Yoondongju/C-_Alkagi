#include "stdafx.h"
#include "HockeyPlayer.h"

CHockeyPlayer::CHockeyPlayer()
{
}

CHockeyPlayer::~CHockeyPlayer()
{
	Release();
}

void CHockeyPlayer::Initialize()
{
	Init_LocalSize(30.f);

	m_tInfo.vPos = { 100.f, ((float)WINCY * 0.5f), 0.f};
	m_tInfo.vLook = { 1.f, 0.f,0.f };
	m_fSpeed = 5.f;
	m_vTargetPoint = ::Get_Mouse();
}

int CHockeyPlayer::Update()
{
	if (m_pMapSize->left <= ::Get_Mouse().x && (::Get_Mouse().x <= WINCX * 0.5f) &&
		m_pMapSize->top <= ::Get_Mouse().y && ::Get_Mouse().y <= m_pMapSize->bottom)
		m_vTargetPoint = ::Get_Mouse();

	/*if (::Get_Mouse().x - m_fLocalSize < m_pMapSize->left || (WINCX * 0.5f - m_fLocalSize < ::Get_Mouse().x))
		return OBJ_NOEVENT;

	if (::Get_Mouse().y - m_fLocalSize < m_pMapSize->top || (m_pMapSize->bottom + m_fLocalSize < ::Get_Mouse().y))
		return OBJ_NOEVENT;*/

	m_tInfo.vDir = m_vTargetPoint - m_tInfo.vPos;

	if (D3DXVec3Length(&m_tInfo.vDir) <= 5.f) // Èçµé¸² º¸Á¤
		return OBJ_NOEVENT;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	float _fAngle = acos(fDot);

	if (m_tInfo.vPos.y < ::Get_Mouse().y)
		_fAngle = D3DX_PI * 2.f - _fAngle;

	m_tInfo.vPos.x += cos(_fAngle) * m_fSpeed;
	m_tInfo.vPos.y -= sin(_fAngle) * m_fSpeed;

	return OBJ_NOEVENT;
}

void CHockeyPlayer::Late_Update()
{
	TranslationLocalToWorld();
}

void CHockeyPlayer::Render(HDC hDC)
{
	Ellipse(hDC,
		m_vPoint[0].x,
		m_vPoint[0].y,
		m_vPoint[1].x,
		m_vPoint[1].y);
}

void CHockeyPlayer::Release()
{
}
