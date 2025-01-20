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

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");  //��׶���
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
	GdiTransparentBlt(hDC,						// �������� �׸��� �׸� dc
		0 ,					// ���� ���� ��ġ�� left
		0 ,					// ���� ���� ��ġ�� top
		WINCX, 							// ���� ���� ���� ����
		WINCY ,							// ���� ���� ���� ����
		hMiniGame_01_top_DC,					// ��Ʈ���� ������ �ִ� dc
		0,				// ����� ��Ʈ���� ���� x��ǥ
		0,				// ����� ��Ʈ���� ���� y��ǥ
		241,			// ����� ��Ʈ���� ���� ������
		146,			// ����� ��Ʈ���� ���� ������
		RGB(0, 128, 128));	// ������ �ȼ��� ���� ��
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
