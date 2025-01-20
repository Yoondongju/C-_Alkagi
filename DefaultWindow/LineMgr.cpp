#include "stdafx.h"
#include "LineMgr.h"

#include "ObjMgr.h"
CLineMgr*	CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

bool CLineMgr::Collision_Line(float & fX, float * pY)
{
	if (m_LineList.empty())
		return false;

	//CLine*		pTargetLine = nullptr;

	//for (auto& iter : m_LineList)
	//{
	//	if (fX >= iter->Get_Info().tLPoint.x &&
	//		fX < iter->Get_Info().tRPoint.x)
	//	{
	//		pTargetLine = iter;
	//	}
	//}

	//if (!pTargetLine)
	//	return false;

	////Y - y1 = ((y2 - y1) / (x2 - x1)) * (X - x1)
	//// Y = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

	//float x1 = pTargetLine->Get_Info().tLPoint.x;
	//float y1 = pTargetLine->Get_Info().tLPoint.y;
	//float x2 = pTargetLine->Get_Info().tRPoint.x;
	//float y2 = pTargetLine->Get_Info().tRPoint.y;

	//*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;

	return true;
}

void CLineMgr::Initialize(SCENEID _type)
{
	Load_Line_type(_type);
	
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);
}

void CLineMgr::Release()
{
//	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	m_LineList.clear();
}

void CLineMgr::Load_Line()
{
	//HANDLE hFile = CreateFile(L"../Data/Line.dat",		// 파일 경로(이름을 포함)
	//	GENERIC_READ,			// 파일 접근 모드(GENERIC_READ : 읽기 전용)
	//	NULL,					// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세서에서 오픈하고자 할 때 허용할 지에 대한 여부(NULL인 경우 공유하지 않음)
	//	NULL,					// 보안 모드(NULL인 경우 기본 보안 상태)
	//	OPEN_EXISTING,			// 생성 방식(CREATE_ALWAYS : 파일이 없으면 생성, 있으면 덮어쓰기), (OPEN_EXISTING : 파일이 있을 때만 열기)
	//	FILE_ATTRIBUTE_NORMAL,  // 파일 속성(아무런 특수 속성이 없는 파일 생성)
	//	NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(우리는 사용 안하기 때문에 NULL)


	//if (INVALID_HANDLE_VALUE == hFile)
	//{
	//	MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
	//	return;
	//}

	//DWORD	dwByte(0);	// 예외 처리 변수
	//LINE	tInfo{};

	//while (true)
	//{
	//	ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

	//	if (0 == dwByte)
	//		break;

	//	m_LineList.push_back(new CLine(tInfo));
	//}

	//CloseHandle(hFile);

	//MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}


void CLineMgr::Load_Line_type(SCENEID _type)
{
	switch (_type)
	{
	//case SCENE_TYPE::MAIN_STAGE_00:
	//	Load_MainStage_00();
	//	break;

	//case STAGE_TYPE::MAIN_STAGE_01:
	//	Load_MainStage_01();
	//	break;


	default:
		break;
	}
}



bool CLineMgr::Collision_Line_Vertical_down(CObj* pObj, float* pY)
{
	if (m_LineList.empty())
		return false;

	CLine* pTargetLine = nullptr;

	//for (auto& iter : m_LineList)
	//{


	//	INFO playerInfo = pObj->Get_Info();
	//	LINE LineInfo = iter->Get_Info();
	//	float YDistance = 0.f;
	//	if (playerInfo.vPos.x + playerInfo.fCX >= LineInfo.tLPoint.x &&
	//		playerInfo.vPos.x - playerInfo.fCX <= LineInfo.tRPoint.x
	//		)
	//	{
	//		*pY = LineInfo.tLPoint.fY;  // 후보 4개 
	//		//float fDiagonal = abs(*pY - playerInfo.fY - playerInfo.fCX * 0.5f);  //플레이어 CX 의절반 ,25
	//		float fDiagonal = 0;  //임시수정
	//		if (   playerInfo.vPos.y <= LineInfo.tLPoint.fY
	//			&& playerInfo.vPos.y >= LineInfo.tRPoint.fY)
	//		{
	//		/*	if (*pY > playerInfo.fY - playerInfo.fCY * 0.5f)
	//			{*/
	//				if (!pTargetLine || YDistance > fDiagonal)
	//				{
	//					YDistance = fDiagonal;
	//					pTargetLine = iter;
	//				}
	//			//}
	//		}
	//	}
	//}


	//if (!pTargetLine)
	//	return false;

	//*pY = pTargetLine->Get_Info().tLPoint.fY;

	return true;
}


bool CLineMgr::Collision_Line_Vertical_up(CObj* pObj, float* pY)
{
	if (m_LineList.empty())
		return false;

	CLine* pTargetLine = nullptr;

	for (auto& iter : m_LineList)
	{


		//INFO playerInfo = pObj->Get_Info();
		//LINE LineInfo = iter->Get_Info();
		//float YDistance = 0.f;
		//if (playerInfo.fX + playerInfo.fCX >= LineInfo.tLPoint.fX &&
		//	playerInfo.fX - playerInfo.fCX <= LineInfo.tRPoint.fX
		//	)
		//{
		//	*pY = LineInfo.tLPoint.fY;  // 후보 4개 
		//	float fDiagonal = abs(*pY - playerInfo.fY - playerInfo.fCX * 0.5f);  //플레이어 CX 의절반 ,25
		//	if (playerInfo.fY - playerInfo.fCY *0.5f <= LineInfo.tLPoint.fY
		//	 && playerInfo.fY >= LineInfo.tRPoint.fY)
		//	{
		//		if (*pY > playerInfo.fY - playerInfo.fCY * 0.5f)
		//		{
		//			if (!pTargetLine || YDistance > fDiagonal)
		//			{
		//				YDistance = fDiagonal;
		//				pTargetLine = iter;
		//			}
		//		}
		//	}
		//}
	}


	//if (!pTargetLine)
	//	return false;

	//*pY = pTargetLine->Get_Info().tLPoint.fY;

	return true;
}




bool CLineMgr::Collision_Line_WALL(CObj* pObj, float* pX, float* pY)
{
	//CLine* pTargetLine = nullptr;
	//float YDistance = 0.f;

	//if (m_LineList.empty())
	//	return false;

	//for (auto& iter : m_LineList)
	//{
	//	INFO playerInfo = pObj->Get_Info();
	//	LINE LineInfo = iter->Get_Info();

	//	float x1 = iter->Get_Info().tLPoint.fX;
	//	float y1 = iter->Get_Info().tLPoint.fY;
	//	float x2 = iter->Get_Info().tRPoint.fX;
	//	float y2 = iter->Get_Info().tRPoint.fY;

	//	if (playerInfo.fX + playerInfo.fCX >= x1 &&
	//		playerInfo.fX - playerInfo.fCX <= x2
	//		&& iter->Get_LineType() == LINETYPE::WALL)
	//	{



	//		//*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;  // 후보 4개 
	//		*pY = y1;  // 후보 4개 
	//		float fDiagonal = abs(*pY - playerInfo.fY - playerInfo.fCY * 0.5f);  //플레이어 CX 의절반 ,25
	//		if (playerInfo.fY  <= y1 && playerInfo.fY >= y2)
	//		{
	//			if (*pY > playerInfo.fY - playerInfo.fCY * 0.5f)
	//			{
	//				if (!pTargetLine || YDistance > fDiagonal)
	//				{
	//					YDistance = fDiagonal;
	//					pTargetLine = iter;
	//				}
	//			}
	//		}

	//	}
	//}

	//if (!pTargetLine)
	//	return false;




	//float x1_Target = pTargetLine->Get_Info().tLPoint.fX;
	//float y2_Target = pTargetLine->Get_Info().tRPoint.fY;



//	*pX = x1_Target;

	return true;

}