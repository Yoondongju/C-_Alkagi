
#include "stdafx.h"
#include "Scene.h"
#include "ObjMgr.h"
#include "LineMgr.h"
CScene::CScene() : m_bSuccess(false)
{
}


CScene::~CScene()
{


	
}

int CScene::Update()
{
	return 0;
}






void CScene::Exit()
{
	list<CObj*>& List_P = CObjMgr::Get_Instance()->find_ObjList(OBJID::OBJ_PLAYER);
	list<CObj*>& List_U = CObjMgr::Get_Instance()->find_ObjList(OBJID::OBJ_UI);


	for (auto& iter : List_P)
	{
		Safe_Delete<CObj*>(iter);
	}
	List_P.clear();


	for (auto& iter : List_U)
	{
		Safe_Delete<CObj*>(iter);
	}
	List_U.clear();


	//list<CLine*>& lineList = CLineMgr::Get_Instance()->GetLineList();

	//for (auto& iter : lineList)
	//{
	//	Safe_Delete<CLine*>(iter);
	//}
	//lineList.clear();

}
