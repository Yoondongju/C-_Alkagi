#pragma once

#include "Define.h"
#include "Player.h"

#include "Monster.h"


class CMainGame
{

	SINGLE(CMainGame)

//public:
//	CMainGame();
//	~CMainGame();


public:
	HDC	GetMainGameDC() { return m_hDC; }
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render();
	void		Release();

private:
	HDC			m_hDC;

	DWORD		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[32];

	CObj*		m_pPlayer;
	CObj*		m_pMonster;

};

//���ؽ� -> ������ -> ����� -> �޽�


// �׸��� ������ �ּ� ���� : ���ؽ�(����)
// �׸��� �ּ� ���� : ������(�ﰢ��, ��)


// ���ؽ� ���μ���