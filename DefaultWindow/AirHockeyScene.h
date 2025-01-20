#pragma once
#include "Scene.h"

#include "Obj.h"

class CAirHockeyScene : public CScene
{
public:
	CAirHockeyScene();
	virtual ~CAirHockeyScene();

public:
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void Enter();
	virtual void Exit();

private:
	void		Init_Map(int _iBorder, int _iScoreSize);
	void		Spawn_Object();
	void		Goal();
	void		End_Game(HDC hDC);

private:
	bool	m_bContinue;

	CObj*	m_pBall;

	int		m_iBorder; // ����
	RECT	m_tScore; // ������
	RECT	m_tMap; // ��
	int		m_GoalPoint[2];

	TCHAR	szScore[32] = L"";

	int		m_iPlayerScore;
	int		m_iEnemyScore;
};
