#include "stdafx.h"

#include "Obj.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CTexture.h"


CAnimation::CAnimation()
	: m_Animator(nullptr)
	, m_pTexture(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(GetTickCount())
	, m_bFinish(false)
	, m_fCount(0.f)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Update()
{

	if (m_fAccTime + m_fCount < GetTickCount())
	{
		++m_iCurFrm;
		m_bFinish = false;

		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = 0;
			m_bFinish = true;
		}

		m_fAccTime = GetTickCount();
	}

}

void CAnimation::Render(HDC hDC)
{
	
	INFO Info = GetAnimator()->GetOwner()->Get_Info();
	//RECT rect = GetAnimator()->GetOwner()->Get_Rect();



	//GdiTransparentBlt(hDC,						// �������� �׸��� �׸� dc
	//	rect.left  ,					// ���� ���� ��ġ�� left
	//	rect.top   ,					// ���� ���� ��ġ�� top
	//	(int)Info.vPos.x,							// ���� ���� ���� ����
	//	(int)Info.vPos.y,							// ���� ���� ���� ����

	//	m_pTexture->GetDC(),					// ��Ʈ���� ������ �ִ� dc
	//	m_vecFrm[m_iCurFrm].vLT.fX,				// ����� ��Ʈ���� ���� x��ǥ
	//	m_vecFrm[m_iCurFrm].vLT.fY,				// ����� ��Ʈ���� ���� y��ǥ
	//	m_vecFrm[m_iCurFrm].vSlice.fX,			// ����� ��Ʈ���� ���� ������
	//	m_vecFrm[m_iCurFrm].vSlice.fY,			// ����� ��Ʈ���� ���� ������
	//	m_ExceptColor);	// ������ �ȼ��� ���� ��
}


void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float fDuration, UINT _iFrameCount)
{
	m_pTexture = _pTex;

	tAnimFrm frm = {};

	for (int i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = fDuration;
		frm.vLT = _vLT + (_vStep * i);
		frm.vSlice = _vSliceSize;

		m_vecFrm.push_back(frm);
	}



	OBJID  _eType = GetAnimator()->GetOwner()->GetObjType();
	COLORID	_Color = GetAnimator()->GetOwner()->GetColor();


	switch (_eType)
	{
	case OBJ_PLAYER:
	{
		m_ExceptColor = RGB(255, 255, 255);
		m_fCount = 500.f;
	}
	break;

	case OBJ_MONSTER:
	{
		m_ExceptColor = RGB(255, 0, 255);
		m_fCount = 300.f;
	}
	break;

	case OBJ_BOSS:
	{
		m_ExceptColor = RGB(255, 255, 255);

		if (0 == lstrcmp(m_strKey, L"Boss_Attack_left")
			|| 0 == lstrcmp(m_strKey, L"Boss_Attack_right")
			|| 0 == lstrcmp(m_strKey, L"Boss_Attack2_left")
			|| 0 == lstrcmp(m_strKey, L"Boss_Attack2_right"))
		{
			m_fCount = 100.f;
		}
		else
			m_fCount = 200.f;
	}
	break;

	default:
	{
		m_ExceptColor = RGB(255, 0, 255);
		m_fCount = 30.f;
	}
	break;
	}

	switch (_Color)
	{
	case COLOR_008080:
	{
		m_ExceptColor = RGB(0x00, 0x80, 0x80);
		m_fCount = 500.f;
		//m_fCount = 100.f;
	}
	break;

	case COLOR_000000:
	{
		m_ExceptColor = RGB(0x00, 0x00, 0x00);
		m_fCount = 500.f;
		//m_fCount = 100.f;

	}
	break;

	case COLOR_4D6DF3:
	{
		m_ExceptColor = RGB(0x4D, 0x6D, 0xF3);
		m_fCount = 300.f;
		//m_fCount = 100.f;

	}
	break;

	case COLOR_C1DCFF:
	{
		m_ExceptColor = RGB(0xC1, 0xDC, 0xFF);
		m_fCount = 300.f;
		//m_fCount = 100.f;

	}
	break;

	case COLOR_108C29:
	{
		m_ExceptColor = RGB(0x10, 0x8C, 0x29);
		m_fCount = 300.f;
		//m_fCount = 100.f;

	}
	break;

	case COLOR_8D9CB4:
	{
		m_ExceptColor = RGB(0x8D, 0x9C, 0xB4);
		m_fCount = 300.f;
		//m_fCount = 100.f;

	}
	break;

	case COLOR_F8F8A0:
	{
		m_ExceptColor = RGB(0xF8, 0xF8, 0xA0);
		m_fCount = 300.f;
		//m_fCount = 100.f;
	}
	break;

	case COLOR_7E87A5:
	{
		m_ExceptColor = RGB(0x7E, 0x87, 0xA5);
		m_fCount = 300.f;
		//m_fCount = 100.f;
	}
	break;

	case COLOR_FFFFFF:
	{
		m_ExceptColor = RGB(0xFF, 0xFF, 0xFF);
		m_fCount = 5.f;	
		//m_fCount = 100.f;

	}
	break;

	case COLOR_END:
	{
		m_ExceptColor = RGB(255, 0, 255);
		m_fCount = 300.f;
		//m_fCount = 100.f;

	}
	break;

	default:
	{
		m_ExceptColor = RGB(255, 0, 255);
		m_fCount = 300.f;
	}
	break;
	}

	// 1. �ִϸ����Ͱ� Create�ִϸ��̼��� ȣ��
	// 2. create�ִϸ��̼ǿ��� ������ Ű���� �ִϸ��̼��� �����ϴ��� ����
	// 3. Create�� �Ű������� ���°����� �ִϸ��̼��� ������ ����

}
