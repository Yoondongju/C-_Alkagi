#include "stdafx.h"
#include "AirHockeyScene.h"

#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"

#include "HockeyPlayer.h"
#include "HockeyBall.h"
#include "HockeyEnemy.h"

CAirHockeyScene::CAirHockeyScene()
	:	m_iBorder(0), m_iPlayerScore(0), m_iEnemyScore(0), m_pBall(nullptr), m_bContinue(true)
{
	ZeroMemory(&m_tScore, sizeof(m_tScore));
	ZeroMemory(&m_tMap, sizeof(m_tMap));
}

CAirHockeyScene::~CAirHockeyScene()
{
}

void CAirHockeyScene::Initialize()
{
	Init_Map(40, 120);
	Spawn_Object();

	int	iGoalLength = 180;
	m_GoalPoint[0] = m_tMap.top + int(float(m_tMap.bottom - m_tMap.top) * 0.5f - (iGoalLength * 0.5f));
	m_GoalPoint[1] = m_GoalPoint[0] + iGoalLength;
}

int CAirHockeyScene::Update()
{
	if (!m_bContinue)
		return OBJ_NOEVENT;

	if (nullptr == m_pBall)
	{
		m_pBall = CAbstractFactory<CHockeyBall>::Create();
		static_cast<CHockeyObj*>(m_pBall)->Set_MapSize(&m_tMap);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, m_pBall);
	}

	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CAirHockeyScene::Late_Update()
{
	if (!m_bContinue)
		return;

	CObjMgr::Get_Instance()->Late_Update();
	Goal();
}

void CAirHockeyScene::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY); // back

	// score
	Rectangle(hDC, m_tScore.left, m_tScore.top, m_tScore.right, m_tScore.bottom); // score

	swprintf_s(szScore, L"Player: %d", m_iPlayerScore);
	TextOut(hDC, 50, 100, szScore, lstrlen(szScore));

	swprintf_s(szScore, L"Enemy: %d", m_iEnemyScore);
	TextOut(hDC, WINCX - 110, 100, szScore, lstrlen(szScore));

	// map
	Rectangle(hDC, m_tMap.left, m_tMap.top, m_tMap.right, m_tMap.bottom);

	// goal
	Rectangle(hDC, 0, m_GoalPoint[0], m_iBorder, m_GoalPoint[1]);
	Rectangle(hDC, m_tMap.right, m_GoalPoint[0], m_tMap.right + m_iBorder, m_GoalPoint[1]);

	MoveToEx(hDC, int((float)WINCX * 0.5f), m_tMap.top, nullptr); // Áß¾Ó ¼±
	LineTo(hDC, int((float)WINCX * 0.5f), m_tMap.bottom);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CAirHockeyScene::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BULLET);
}

void CAirHockeyScene::Enter()
{
	Initialize();
}

void CAirHockeyScene::Exit()
{
	Release();
}

void CAirHockeyScene::Init_Map(int _iBorder, int _iScoreSize)
{
	m_iBorder = _iBorder;
	m_tScore = { m_iBorder, m_iBorder, WINCX - m_iBorder, _iScoreSize };
	m_tMap = { m_iBorder, m_iBorder + m_tScore.bottom, WINCX - m_iBorder, WINCY - m_iBorder };
}

void CAirHockeyScene::Spawn_Object()
{
	CObj* pObj = CAbstractFactory<CHockeyPlayer>::Create();
	static_cast<CHockeyObj*>(pObj)->Set_MapSize(&m_tMap);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pObj); // player

	m_pBall = CAbstractFactory<CHockeyBall>::Create();
	static_cast<CHockeyObj*>(m_pBall)->Set_MapSize(&m_tMap);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, m_pBall); // ball

	pObj = CAbstractFactory<CHockeyEnemy>::Create();
	static_cast<CHockeyObj*>(pObj)->Set_MapSize(&m_tMap);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pObj); // enemy

	pObj = CAbstractFactory<CHockeyEnemy>::Create();
	static_cast<CHockeyObj*>(pObj)->Set_MapSize(&m_tMap);
	static_cast<CHockeyObj*>(pObj)->Init_LocalSize(20.f);
	//pObj->Get_Info().vPos = { WINCX * 0.5f + 100.f, 370.f ,0.f };
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pObj); // enemy
}

void CAirHockeyScene::Goal()
{
	if (nullptr == m_pBall)
		return;

	if (m_pBall->Get_Info().vPos.x - 20.f <= (float)m_iBorder) // left
	{
		if (m_GoalPoint[0] <= m_pBall->Get_Info().vPos.y &&
			m_pBall->Get_Info().vPos.y <= m_GoalPoint[1])
		{
			m_pBall->Set_Dead();
			m_pBall = nullptr;
			++m_iPlayerScore;
		}
	}

	else if (m_pBall->Get_Info().vPos.x + 20.f >= (float)(WINCX - m_iBorder)) // right
	{
		if (m_GoalPoint[0] <= m_pBall->Get_Info().vPos.y &&
			m_pBall->Get_Info().vPos.y <= m_GoalPoint[1])
		{
			m_pBall->Set_Dead();
			m_pBall = nullptr;
			++m_iEnemyScore;
		}
	}
}
//
//void CAirHockeyScene::End_Game(HDC hDC)
//{
//	if (m_iPlayerScore + m_iEnemyScore < 5)
//		return;
//
//	bool bPlayer = m_iPlayerScore > m_iEnemyScore ? true : false;
//
//	if (bPlayer)
//		TextOut(hDC, WINCX * 0.5f, WINCY * 0.5f, L"Player Win", lstrlen(L"Player Win"));
//	else
//		TextOut(hDC, WINCX * 0.5f, WINCY * 0.5f, L"Player Win", lstrlen(L"Player Win"));
//}
