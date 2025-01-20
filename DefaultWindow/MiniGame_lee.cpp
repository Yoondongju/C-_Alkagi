#include "stdafx.h"
#include "MiniGame_lee.h"

#include "BmpMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"


#include "KeyMgr.h"
//#include "SoundMgr.h"
#include <algorithm>

#include "SceneMgr.h"

#include "PipeBlock.h"
#include "PipeBall.h"
#include  "Pipe_Button.h"

#include "CollisionMgr.h"
MiniGame_lee::MiniGame_lee()

{

}


MiniGame_lee::~MiniGame_lee()
{
	Release();
}

void MiniGame_lee::Initialize()
{


	//CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	//CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");  //��׶���
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Api/Map/Result_map.bmp", L"Test_map");
	//
	//CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<PipeBall>::Create(100.f, 150.f, 50.f, PIPEBALL_STATE::PB_00));

	m_pPlayer = CAbstractFactory<PipeBall>::Create(100.f, 150.f, 50.f, PIPEBALL_STATE::PB_00);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, m_pPlayer);


	CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, CAbstractFactory<PipeBlock>::Create(200.f, 200.f, 50.f, PS_01,m_pPlayer));
	CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, CAbstractFactory<PipeBlock>::Create(300.f, 200.f, 50.f, PS_01,m_pPlayer));
	CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, CAbstractFactory<PipeBlock>::Create(400.f, 200.f, 50.f, PS_00,m_pPlayer));
	CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, CAbstractFactory<PipeBlock>::Create(500.f, 200.f, 50.f, PS_02,m_pPlayer));
	CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, CAbstractFactory<PipeBlock>::Create(600.f, 200.f, 50.f, PS_01,m_pPlayer));

	CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, CAbstractFactory<PipeBlock>::Create(300.f, 300.f, 50.f, PS_01,m_pPlayer));
	CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, CAbstractFactory<PipeBlock>::Create(400.f, 300.f, 50.f, PS_00,m_pPlayer));
	CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, CAbstractFactory<PipeBlock>::Create(500.f, 300.f, 50.f, PS_01,m_pPlayer));
	CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, CAbstractFactory<PipeBlock>::Create(600.f, 300.f, 50.f, PS_01,m_pPlayer));
	CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, CAbstractFactory<PipeBlock>::Create(700.f, 300.f, 50.f, PS_03,m_pPlayer));

	CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, CAbstractFactory<PipeBlock>::Create(700.f, 500.f, 40.f, PS_END, m_pPlayer));
	CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, CAbstractFactory<Pipe_Button>::Create());



}

int MiniGame_lee::Update()
{

	CObjMgr::Get_Instance()->Update();
	return 0;

}

void MiniGame_lee::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	//CCollisionMgr::
	if (CObjMgr::Get_Instance()->Get_nextScene_lee())
	{
		//ChangeScene();
	}

}

void MiniGame_lee::Render(HDC hDC)
{

	HDC	hMiniGame_01_top_DC = CBmpMgr::Get_Instance()->Find_Image(L"Test_map");
	GdiTransparentBlt(hDC,						// �������� �׸��� �׸� dc
		0,					// ���� ���� ��ġ�� left
		0,					// ���� ���� ��ġ�� top
		WINCX, 							// ���� ���� ���� ����
		WINCY,							// ���� ���� ���� ����
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

void MiniGame_lee::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_UI);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
}




void MiniGame_lee::Enter()
{
	Initialize();
}

void MiniGame_lee::Exit()
{
	CScene::Exit();

}
