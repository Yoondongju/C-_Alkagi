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

//버텍스 -> 폴리곤 -> 서브셋 -> 메쉬


// 그리기 연산의 최소 단위 : 버텍스(정점)
// 그리기 최소 단위 : 폴리곤(삼각형, 면)


// 버텍스 프로세싱