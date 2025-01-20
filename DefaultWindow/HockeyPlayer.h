#pragma once

#include "HockeyObj.h"

class CHockeyPlayer : public CHockeyObj
{
public:
	CHockeyPlayer();
	virtual ~CHockeyPlayer();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	D3DXVECTOR3	m_vTargetPoint;
};
