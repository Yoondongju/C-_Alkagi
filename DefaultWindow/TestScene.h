#pragma once


#pragma once
#include "Scene.h"
#include "Obj.h"


class TestScene : public CScene
{
public:
	TestScene();
	virtual ~TestScene();

public:
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void		Enter();
	virtual void		Exit();

	//virtual void Exit()		 override;

public:
	HDC			m_hDC;
	CObj* m_pPlayer;
	CObj* m_pMonster;





};

