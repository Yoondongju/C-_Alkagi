#include "stdafx.h"
#include "CollisionMgr.h"

#include "HockeyObj.h"
#include "HockeyBall.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src)
{
	RECT	rcRect{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			//임시주석
			/*if (IntersectRect(&rcRect, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}*/
		}
	}
}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src)
{
	float	fX(0.f), fY(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fX, &fY))
			{
				if (fX > fY) // 상하 충돌
				{
					// 상 충돌
					if (Dst->Get_Info().vPos.y < Src->Get_Info().vPos.y)
					{
					//	Dst->Set_PosY(-fY);
					}
					// 하 충돌
					else 
					{
					//	Dst->Set_PosY(fY);
					}
				}

				else 		// 좌우 충돌
				{
					// 좌 충돌
					if (Dst->Get_Info().vPos.x < Src->Get_Info().vPos.x)
					{
					//	Dst->Set_PosX(-fX);
					}
					// 우 충돌
					else
					{
					//	Dst->Set_PosX(fX);
					}
				}
			}
		}
	}

}

bool CCollisionMgr::Check_Rect(CObj * pDst, CObj * pSrc, float * pX, float * pY)
{
	//임시주석
	//float	fWidth  = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	//float	fHeight = abs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	//float	fRadiusX = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	//float	fRadiusY = (pDst->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;

	//if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))
	//{
	//	*pX = fRadiusX - fWidth;
	//	*pY = fRadiusY - fHeight;

	//	return true;
	//}

	return false;
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dst, Src))
			{
				Dst->SetCollisionObj(Src);
				Src->SetCollisionObj(Dst);
			}
			else
			{

			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj * pDst, CObj * pSrc)
{
	if (OBJID::OBJ_PLAYER == pDst->GetObjType()
		&& OBJID::OBJ_PINGPONGBALL == pSrc->GetObjType())
	{
		D3DXVECTOR3 vPlayerColliPos = pDst->GetColliPos();
		D3DXVECTOR3 vPlayerColliSize = pDst->GetColliSize();

		D3DXVECTOR3 vPingPongBallColliPos = pSrc->GetColliPos();
		D3DXVECTOR3 vPingPongBallColliSize = pSrc->GetColliSize();

		float fWidth = abs(vPlayerColliPos.x - vPingPongBallColliPos.x);
		float fHeight = abs(vPlayerColliPos.y - vPingPongBallColliPos.y);

		float fDistance = sqrt(fWidth * fWidth + fHeight * fHeight);


		if (fDistance <= vPlayerColliSize.x / 2.f + vPingPongBallColliSize.x / 2.f) // 원 충돌
		{
			return true;
		}
		else
		{
			return false;
		}

	}
}


void CCollisionMgr::Collision_HockeyBall(list<CObj*> _Dst, list<CObj*> _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_HockeyBall(Dst, Src))
			{
				static_cast<CHockeyBall*>(Src)->On_Collision(Dst->Get_Info().vDir);
			}
		}
	}
}

bool CCollisionMgr::Check_HockeyBall(CObj* pDst, CObj* pSrc)
{
	float	fWidth = abs(pDst->Get_Info().vPos.x - pSrc->Get_Info().vPos.x);
	float	fHeight = abs(pDst->Get_Info().vPos.y - pSrc->Get_Info().vPos.y);

	float	fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);

	float	fDstLength = static_cast<CHockeyObj*>(pDst)->Get_Radius();
	float	fSrcLength = static_cast<CHockeyObj*>(pSrc)->Get_Radius();

	float	fRadius = (fDstLength + fSrcLength); //임시주석

	return fRadius >= fDiagonal;
}