#include "stdafx.h"
#include "Obj.h"


#include "CAnimator.h"

CObj::CObj() : m_fSpeed(0.f), m_eDir(DIR_END),
m_bDead(false), m_fAngle(0.f)  , m_fWidth(0.f) , m_eColorid(COLOR_END)
, m_pCollisionObj(nullptr) //¿±µø¡÷
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
//	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));

	ZeroMemory(&m_vOriginPos, sizeof(D3DXVECTOR3));
}

CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	//m_tRect.T_left		= float(m_tInfo.vPos.x - m_fWidth);
	//m_tRect.T_top		= float(m_tInfo.vPos.y - m_fWidth);
	//m_tRect.T_right		= float(m_tInfo.vPos.x + m_fWidth);
	//m_tRect.T_bottom	= float(m_tInfo.vPos.y + m_fWidth);
}

void CObj::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;


	}

}


void CObj::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;

}