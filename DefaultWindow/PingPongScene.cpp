#include "stdafx.h"
#include "PingPongScene.h"

#include "BmpMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"


#include "KeyMgr.h"
//#include "SoundMgr.h"
#include <algorithm>

//#include "Obj.h"
#include "SceneMgr.h"

#include "Player.h"
#include "PingPongBall.h"


PingPongScene::PingPongScene()

{

}


PingPongScene::~PingPongScene()
{
	Release();
}

void PingPongScene::Initialize()
{
	CPlayer* pPlayer1 = new CPlayer;
	pPlayer1->Initialize(D3DXVECTOR3(WINCX / 4.f, WINCY - 200.f, 0.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PLAYER, pPlayer1);

	CPlayer* pPlayer2 = new CPlayer;
	pPlayer2->Initialize(D3DXVECTOR3(WINCX / 2.f, WINCY - 200.f, 0.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PLAYER, pPlayer2);
	
	CPlayer* pPlayer3 = new CPlayer;
	pPlayer3->Initialize(D3DXVECTOR3(WINCX / 2.f + WINCX / 4.f, WINCY - 200.f, 0.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PLAYER, pPlayer3);
	
	
	
	
	CPingPongBall* pEumeyBall = new CPingPongBall;
	pEumeyBall->Initialize(D3DXVECTOR3(WINCX / 4.f,  200.f, 0.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PINGPONGBALL, pEumeyBall);
	
	CPingPongBall* pEumeyBall1 = new CPingPongBall;
	pEumeyBall1->Initialize(D3DXVECTOR3(WINCX / 2.f, 200.f, 0.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PINGPONGBALL, pEumeyBall1);

	CPingPongBall* pEumeyBall2 = new CPingPongBall;
	pEumeyBall2->Initialize(D3DXVECTOR3(WINCX / 2.f + WINCX / 4.f, 200.f, 0.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PINGPONGBALL, pEumeyBall2);

}

int PingPongScene::Update()
{

	CObjMgr::Get_Instance()->Update();
	return 0;

}

void PingPongScene::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();

}

void PingPongScene::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);


	if (CPingPongBall::GetCount() <= 0)
	{
		wstring playerWin = L"Player 승리!";
		RECT rt3 = { (WINCX / 2.f) - 50 , (WINCY / 2.f) - 50, (WINCX / 2.f) + 200, (WINCY / 2.f) + 200 };

		DrawTextW(hDC
			, playerWin.c_str() 			// 변수가 들어가야함
			, -1
			, &rt3
			, DT_LEFT | DT_WORDBREAK);

		return;
	}

	else if (CPlayer::GetCount() <= 0)
	{
		wstring TargetWin = L"Target 승리!";
		RECT rt4 = { (WINCX / 2.f) - 50 , (WINCY / 2.f) - 50, (WINCX / 2.f) + 200, (WINCY / 2.f) + 200 };

		DrawTextW(hDC
			, TargetWin.c_str() 			// 변수가 들어가야함
			, -1
			, &rt4
			, DT_LEFT | DT_WORDBREAK);

		return;
	}




	RECT rt1 = { 3 , WINCY - 55, 170, WINCY - 35 };
	RECT rt2 = { 3 , WINCY - 30, 170, WINCY - 10 };

	RECT rtZ = { WINCX-300 , WINCY - 70, WINCX- 220, WINCY - 10 };
	RECT rtX = { WINCX-220 , WINCY - 70, WINCX-120, WINCY - 10 };
	RECT rtC = { WINCX-110 , WINCY - 70, WINCX-3, WINCY - 10 };

	wstring player = L"Player 남은 바둑알: ";
	wstring Target = L"Target 남은 바둑알: ";



	wstring playerZ = L"Z: 크기 Up";
	wstring playerX = L"X: 분신만들기";
	wstring playerC = L"C: 초기위치로";


	player += to_wstring(CPlayer::GetCount()) + L"개";
	Target += to_wstring(CPingPongBall::GetCount()) + L"개";



	DrawTextW(hDC
		, player.c_str() 			// 플레이어 바둑돌 갯수 UI
		, -1
		, &rt1
		, DT_LEFT | DT_WORDBREAK);

	DrawTextW(hDC
		, Target.c_str()			// Target 바둑돌 갯수 UI
		, -1
		, &rt2
		, DT_LEFT | DT_WORDBREAK);



	DrawTextW(hDC
		, playerZ.c_str()			//  스킬 입 니다 
		, -1						//  스킬 입 니다 
		, &rtZ						//  스킬 입 니다 
		, DT_LEFT | DT_WORDBREAK);	//  스킬 입 니다 
									//  스킬 입 니다 
									//  스킬 입 니다 
	DrawTextW(hDC					//  스킬 입 니다 
		, playerX.c_str()			//  스킬 입 니다 
		, -1						//  스킬 입 니다 
		, &rtX						//  스킬 입 니다 
		, DT_LEFT | DT_WORDBREAK);	//  스킬 입 니다 
									//  스킬 입 니다 
									//  스킬 입 니다 
	DrawTextW(hDC					//  스킬 입 니다 
		, playerC.c_str()			//  스킬 입 니다 
		, -1
		, &rtC
		, DT_LEFT | DT_WORDBREAK);

	

	Rectangle(hDC,
		0,
		WINCY / 2.f - 10,
		30,
		WINCY / 2.f + 10);

	Rectangle(hDC,
		WINCX - 30,
		WINCY / 2.f  - 10,
		WINCX,
		WINCY / 2.f + 10);



	MoveToEx(hDC, 0.f, WINCY/2.f ,nullptr);
	LineTo(hDC, WINCX,WINCY/2.f);

}

void PingPongScene::Release()
{

}




void PingPongScene::Enter()
{
	Initialize();
}

void PingPongScene::Exit()
{
	CScene::Exit();

}
