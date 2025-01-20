#include "stdafx.h"
#include "HockeyObj.h"

CHockeyObj::CHockeyObj()
	:	m_fLocalSize(0.f), m_pMapSize(nullptr)
{
}

CHockeyObj::~CHockeyObj()
{
	Release();
}

void CHockeyObj::Initialize()
{
}

int CHockeyObj::Update()
{
	return OBJ_NOEVENT;
}

void CHockeyObj::Late_Update()
{
}

void CHockeyObj::Render(HDC hDC)
{
}

void CHockeyObj::Release()
{
}

void CHockeyObj::Init_LocalSize(float _fSize)
{// ·ÎÄÃ ½ºÆäÀÌ½º »ó¿¡¼­ÀÇ RECT ÁÂÇ¥ º¤ÅÍ ÃÊ±âÈ­
	// ÁÂÇ¥ º¤ÅÍ
	m_fLocalSize = _fSize;
	m_vOriginPoint[0] = { -m_fLocalSize, -m_fLocalSize, 1.f }; // left-top
	m_vOriginPoint[1] = { m_fLocalSize, m_fLocalSize, 1.f }; // right-bottom
}

void CHockeyObj::On_Collision(D3DXVECTOR3 _vDir)
{
	m_tInfo.vDir = (m_tInfo.vDir * -1 + _vDir);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
}

void CHockeyObj::TranslationLocalToWorld()
{// ·ÎÄÃ ÁÂÇ¥ º¤ÅÍ¸¦ ¿ùµå ÁÂÇ¥ º¤ÅÍ·Î º¯È¯ OriginPoint -> Point
	D3DXMATRIX	matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0.f));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 2; i++)
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vOriginPoint[i], &m_tInfo.matWorld);
}
