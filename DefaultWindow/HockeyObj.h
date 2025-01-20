#pragma once

#include "Obj.h"

class CHockeyObj : public CObj
{
public:
	CHockeyObj();
	~CHockeyObj();

public:
	virtual void	Initialize();
	virtual int		Update();
	virtual	void	Late_Update();
	virtual void	Render(HDC hDC);
	virtual void	Release();

public:
	float		Get_Radius() { return m_fLocalSize; }
	void		Set_MapSize(RECT* _pMapSize) { m_pMapSize = _pMapSize; }

	void		On_Collision(D3DXVECTOR3 _vDir);
	void		Init_LocalSize(float _fSize);

protected:
	void		TranslationLocalToWorld();

protected:
	D3DXVECTOR3 m_vPoint[2];
	D3DXVECTOR3 m_vOriginPoint[2];

	RECT*		m_pMapSize;

protected:
	float		m_fLocalSize;
	float		m_fVelocity;
	float		m_fExcel;
};
