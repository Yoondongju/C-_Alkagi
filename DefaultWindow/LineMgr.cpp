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
	//HANDLE hFile = CreateFile(L"../Data/Line.dat",		// ���� ���(�̸��� ����)
	//	GENERIC_READ,			// ���� ���� ���(GENERIC_READ : �б� ����)
	//	NULL,					// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ������� �����ϰ��� �� �� ����� ���� ���� ����(NULL�� ��� �������� ����)
	//	NULL,					// ���� ���(NULL�� ��� �⺻ ���� ����)
	//	OPEN_EXISTING,			// ���� ���(CREATE_ALWAYS : ������ ������ ����, ������ �����), (OPEN_EXISTING : ������ ���� ���� ����)
	//	FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�ƹ��� Ư�� �Ӽ��� ���� ���� ����)
	//	NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�츮�� ��� ���ϱ� ������ NULL)


	//if (INVALID_HANDLE_VALUE == hFile)
	//{
	//	MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
	//	return;
	//}

	//DWORD	dwByte(0);	// ���� ó�� ����
	//LINE	tInfo{};

	//while (true)
	//{
	//	ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

	//	if (0 == dwByte)
	//		break;

	//	m_LineList.push_back(new CLine(tInfo));
	//}

	//CloseHandle(hFile);

	//MessageBox(g_hWnd, _T("Load �Ϸ�"), L"����", MB_OK);
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
	//		*pY = LineInfo.tLPoint.fY;  // �ĺ� 4�� 
	//		//float fDiagonal = abs(*pY - playerInfo.fY - playerInfo.fCX * 0.5f);  //�÷��̾� CX ������ ,25
	//		float fDiagonal = 0;  //�ӽü���
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
		//	*pY = LineInfo.tLPoint.fY;  // �ĺ� 4�� 
		//	float fDiagonal = abs(*pY - playerInfo.fY - playerInfo.fCX * 0.5f);  //�÷��̾� CX ������ ,25
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



	//		//*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;  // �ĺ� 4�� 
	//		*pY = y1;  // �ĺ� 4�� 
	//		float fDiagonal = abs(*pY - playerInfo.fY - playerInfo.fCY * 0.5f);  //�÷��̾� CX ������ ,25
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