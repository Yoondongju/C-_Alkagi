#pragma once

#include "Define.h"
class CAnimator;


class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void			Set_Pos(float _fX, float _fY)
	{
		m_tInfo.vPos.x = _fX;
		m_tInfo.vPos.y = _fY;
	}

	void	SetCollisionObj(CObj* _pObj) { m_pCollisionObj = _pObj; }
	//¿±µø¡÷

	void			Set_Dir(DIRECTION eDir)
	{
		m_eDir = eDir;
	}

	float			Get_width() { return m_fWidth; }
	void			Set_width(float _w) { m_fWidth = _w; }


	bool			Get_Dead() { return m_bDead; }
	void			Set_Dead() { m_bDead = true; }

	INFO			Get_Info() { return m_tInfo; }
	void			Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void			Set_Target(CObj* pTarget) { m_pTarget = pTarget; }
	void			Set_speed(float _f) { m_fSpeed = _f; }

	const INFO&		Get_Info() const { return m_tInfo; }
	void			Update_Rect();

public: 
	//¿±µø¡÷
	D3DXVECTOR3	GetColliPos() { return m_vColliderPos; }
	D3DXVECTOR3	GetColliSize() { return m_vColliderSize; }


	// js lee
	void			Move_Frame();
	void			CreateAnimator();
	CAnimator*		GetAnimator()		{ return m_pAnimator; }
	
	void			SetObjType(OBJID _e)	{ m_eObjType = _e; }
	OBJID			GetObjType()			{ return m_eObjType; }
	COLORID			GetColor() { return m_eColorid; }  
	void			Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
	const TCHAR* Get_FrameKey()
	{
		if (this != nullptr)
			return m_pFrameKey;
		else
			return 0;
	}

public:
	virtual void	Initialize()	PURE;
	virtual int		Update()		PURE;
	virtual	void	Late_Update()	PURE;
	virtual void	Render(HDC hDC) PURE;
	virtual void	Release()		PURE;

protected:
	INFO		m_tInfo;
	float		m_fSpeed = 0.f;
	float		m_fWidth; //qπ›¡ˆÉE∞≥≥‰


	DIRECTION	m_eDir;
	float		m_fAngle;
	bool		m_bDead;

	// add leejunsik
	FRAME		m_tFrame;
	CObj* m_pTarget;
	const TCHAR* m_pFrameKey = L"";
	OBJID		m_eObjType;
	CAnimator* m_pAnimator;
	COLORID		m_eColorid;
	
	//¿±µø¡÷
	CObj* m_pCollisionObj;
	D3DXVECTOR3		m_vColliderPos;
	D3DXVECTOR3		m_vColliderSize;
	D3DXVECTOR3		m_vColliderOriginSize;
	D3DXVECTOR3		m_vOriginPos;


};

