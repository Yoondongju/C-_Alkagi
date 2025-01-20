#pragma once

#include "Scene.h"
#include "Obj.h"


class PingPongScene : public CScene
{
public:
	PingPongScene();
	virtual ~PingPongScene();

public:
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void		Enter();
	virtual void		Exit();



public:
	HDC			m_hDC;
	CObj*		m_pPlayer;
	CObj*		m_pMonster;


};

