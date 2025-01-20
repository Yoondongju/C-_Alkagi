#pragma once
#include "HockeyObj.h"

class CHockeyBall : public CHockeyObj
{
public:
	CHockeyBall();
	virtual ~CHockeyBall();

public:
	virtual void Initialize() override;
	virtual int	Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void		Collision_Map();
};

