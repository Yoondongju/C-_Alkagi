#include "stdafx.h"
#include "TestScene.h"

#include "BmpMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"


#include "KeyMgr.h"
//#include "SoundMgr.h"
#include <algorithm>

//#include "Obj.h"
#include "SceneMgr.h"

#include "Player.h"
#include "Monster.h"


TestScene::TestScene()

{

}


TestScene::~TestScene()
{
	Release();
}

void TestScene::Initialize()
{


	//CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	//CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");  //백그라운드
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Api/Map/Result_map.bmp", L"Test_map");
	//
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());

}

int TestScene::Update()
{

	CObjMgr::Get_Instance()->Update();
	return 0;

}

void TestScene::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();

}

void TestScene::Render(HDC hDC)
{

	HDC	hMiniGame_01_top_DC = CBmpMgr::Get_Instance()->Find_Image(L"Test_map");
	GdiTransparentBlt(hDC,						// 최종적인 그림을 그릴 dc
		0 ,					// 복사 받을 위치의 left
		0 ,					// 복사 받을 위치의 top
		WINCX, 							// 복사 받을 가로 길이
		WINCY ,							// 복사 받을 세로 길이
		hMiniGame_01_top_DC,					// 비트맵을 가지고 있는 dc
		0,				// 출력할 비트맵의 시작 x좌표
		0,				// 출력할 비트맵의 시작 y좌표
		241,			// 출력할 비트맵의 가로 사이즈
		146,			// 출력할 비트맵의 세로 사이즈
		RGB(0, 128, 128));	// 제거할 픽셀의 색상 값
	//HDC	hMainStageDC = CBmpMgr::Get_Instance()->Find_Image(L"Ending");

	//Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	//m_pPlayer->Render(m_hDC);
	//m_pMonster->Render(m_hDC);

	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	CObjMgr::Get_Instance()->Render(hDC);




}

void TestScene::Release()
{

}




void TestScene::Enter()
{
	Initialize();
}

void TestScene::Exit()
{
	CScene::Exit();

}
