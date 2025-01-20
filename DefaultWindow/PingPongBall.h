#pragma once
#include "Obj.h"

#define	PINGPONG_RADIUS 20.f

class CPingPongBall : public CObj
{
public:
	CPingPongBall();
	virtual ~CPingPongBall();

public:
	void		Set_Player(CObj* pPlayer) { m_pPlayer = pPlayer; }

public:
	virtual void Initialize() override;
	virtual void Initialize(D3DXVECTOR3 _v);

	virtual int Update() override;
	virtual void Late_Update()override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void		Key_Input();
	void		Move();
	void		CollisionMove();


public:

	float       GetGauge() { return m_fPullGauge; }
	static BYTE	GetCount() { return m_iCount; }

private:
	CObj*		m_pPlayer;

	D3DXVECTOR3	m_vPosinPoint;
	D3DXVECTOR3	m_vOriginPosinPoint;

	D3DXVECTOR3	m_vPosinLeftPoint;
	D3DXVECTOR3	m_vOriginPosinLeftPoint;

	D3DXVECTOR3	m_vPosinRightPoint;
	D3DXVECTOR3	m_vOriginPosinRightPoint;


	float		m_fAngle;
	float		m_fPullGauge;
	float		m_fFrictionforce;

	bool		m_bReadyPull;
	bool		m_bStartMove;

	static BYTE		m_iCount;
};

