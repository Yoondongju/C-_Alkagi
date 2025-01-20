#include "stdafx.h"
#include "MainGame.h"

#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "New_KeyMgr.h"
#include "CTimeMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"


CMainGame::CMainGame() : m_pPlayer(nullptr), m_pMonster(nullptr),
m_iFPS(0), m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	New_KeyMgr::CreateSingleTonInst()->init();
	CTimeMgr::CreateSingleTonInst()->init();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back_2.bmp", L"Back");
	//CSoundMgr::Get_Instance()->Initialize();
	CSceneMgr::CreateSingleTonInst()->init();

}

void CMainGame::Update()
{
	//m_pPlayer->Update();
	//m_pMonster->Update();
	New_KeyMgr::CreateSingleTonInst()->Update();
	CTimeMgr::CreateSingleTonInst()->update();

	CSceneMgr::CreateSingleTonInst()->Update();

}

void CMainGame::Late_Update()
{


	CSceneMgr::CreateSingleTonInst()->Late_Update();

}

void CMainGame::Render()
{
	

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);


		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
	HDC	hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");

	Rectangle(hBackDC, 0, 0, WINCX, WINCY);

	CSceneMgr::CreateSingleTonInst()->Render(hBackDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);


	//Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	//m_pPlayer->Render(m_hDC);
	//m_pMonster->Render(m_hDC);
}

void CMainGame::Release()
{

	CBmpMgr::Destroy();
	CKeyMgr::Destroy();
	CLineMgr::Destroy();
	CObjMgr::Destroy();

	ReleaseDC(g_hWnd, m_hDC);


	ReleaseDC(g_hWnd, m_hDC);	

	Safe_Delete<CObj*>(m_pMonster);
	Safe_Delete<CObj*>(m_pPlayer);
}
