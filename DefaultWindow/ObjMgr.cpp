#include "stdafx.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "CollisionMgr.h"
#include <algorithm>
#include <string>
#include <time.h>
//#include "SoundMgr.h"
CObjMgr*		CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr() : 
	m_eAnime_State(GS_IDLE)
	, m_iGold(200)
	,m_iScore(1)
	,m_b_Player_visible(false)

{

}


CObjMgr::~CObjMgr()
{
	Release();
}


CObj * CObjMgr::Get_Target(OBJID eID, CObj * pObj)
{
	if(m_ObjList[eID].empty())
		return nullptr;

	CObj*	pTarget = nullptr;

	float	fDistance(0.f);

	//for (auto& iter : m_ObjList[eID])
	//{
	//	if(iter->Get_Dead())
	//		continue;

	//	float	fWidth	  = pObj->Get_Info().fX - iter->Get_Info().fX;
	//	float	fHeight	  = pObj->Get_Info().fY - iter->Get_Info().fY;
	//	float	fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);

	//	if ((!pTarget) || (fDistance > fDiagonal))
	//	{
	//		pTarget = iter;
	//		fDistance = fDiagonal;
	//	}
	//}

	return pTarget;
}


CObj* CObjMgr::Get_Target_Mouse(OBJID eID, POINT* px)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj* pTarget = nullptr;

	float	fDistance(0.f);

	for (auto& iter : m_ObjList[eID])
	{
		if (iter->Get_Dead())
			continue;


		//if    (iter->Get_Rect().left		<= px->x
		//	&& iter->Get_Rect().right		>= px->x
		//	&& iter->Get_Rect().top			<= px->y
		//	&& iter->Get_Rect().bottom		>= px->y
		//	)
		//{
		//	pTarget = iter;
		//}

	}

	return pTarget;
}
void CObjMgr::Add_Object(OBJID eID, CObj * pObj)
{
	if (OBJ_END <= eID || nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);
}

void CObjMgr::Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int		iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}
	CCollisionMgr::Collision_HockeyBall(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BULLET]);

	//CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_PINGPONGBALL]);
}

void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(hDC);
	}

}

void CObjMgr::Release()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
	



}

void CObjMgr::Delete_ID(OBJID eID)
{
	for (auto& pObj : m_ObjList[eID])
		Safe_Delete(pObj);

	m_ObjList[eID].clear();
}

