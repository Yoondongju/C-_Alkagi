#pragma once

#include "HockeyObj.h"

class CHockeyEnemy : public CHockeyObj
{
public:
	CHockeyEnemy();
	virtual ~CHockeyEnemy();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};
