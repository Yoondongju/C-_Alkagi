#include "stdafx.h"
#include "SceneMgr.h"

#include "ObjMgr.h"

//SceneList

#include "TestScene.h"
#include	"MiniGame_lee.h"
#include	"AirHockeyScene.h"
#include	"PingPongScene.h"



CSceneMgr::CSceneMgr() : m_pScene(nullptr) , m_pScene_Pre(nullptr)
, m_ePreScene(SC_END), m_eCurScene(SC_END)

{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::init()
{
	m_vecGameScene.push_back(new TestScene);
	m_vecGameScene.push_back(new MiniGame_lee);
	m_vecGameScene.push_back(new CAirHockeyScene);
	m_vecGameScene.push_back(new PingPongScene);



	m_pScene = m_vecGameScene[SCENEID::SC_PINGPONG];  // ¾À ÀüÈ¯¼ø¼­   2->1->0->3
	m_pScene->Enter();
}

void CSceneMgr::Scene_Change(SCENEID _e)
{
	m_pScene->Exit();
	m_ePreScene = _e;
	m_pScene_Pre = m_pScene;

	m_pScene = m_vecGameScene[_e];
	m_pScene->Enter();
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}


void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
	

}
