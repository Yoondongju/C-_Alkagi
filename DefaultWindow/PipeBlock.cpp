#include "stdafx.h"
#include "PipeBlock.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Line.h"
class PipeBall;
PipeBlock::PipeBlock()
	: m_e_PipeState(PS_END)
	, m_e_RotationState(RS_12)
	, m_b_ClickFlag(false)
	, m_f_delta_angle(0.f)

{


}
PipeBlock::~PipeBlock()
{
	Release();
}

void PipeBlock::Key_Input()
{

	/*
	클릭하면 회전
	시작 RS_12 -> 03 -> 06 -> 09 -> 12
	*/

	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	m_v_Rect_Point[0] = { m_tInfo.vPos.x - m_fWidth, m_tInfo.vPos.y - m_fWidth, 0.f };
	m_v_Rect_Point[1] = { m_tInfo.vPos.x + m_fWidth, m_tInfo.vPos.y - m_fWidth, 0.f };
	m_v_Rect_Point[2] = { m_tInfo.vPos.x + m_fWidth, m_tInfo.vPos.y + m_fWidth, 0.f };
	m_v_Rect_Point[3] = { m_tInfo.vPos.x - m_fWidth, m_tInfo.vPos.y + m_fWidth, 0.f };

	RECT _rect = { m_tInfo.vPos.x - m_fWidth, m_tInfo.vPos.y - m_fWidth  , m_tInfo.vPos.x + m_fWidth, m_tInfo.vPos.y + m_fWidth };
	


	if (PtInRect(&_rect, pt) && !m_b_ClickFlag)
	{
		if (CKeyMgr::Get_Instance()->Key_Down(0x01))
		{
			m_b_ClickFlag = true;
			m_f_delta_angle = m_fAngle;
		

		}

	}
	

}

void PipeBlock::Initialize()
{
	m_tInfo.vPos = { WINCX / 2.00000f, WINCY / 2.000000f, 0.f }; //시작위치
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_fSpeed = 3.f;
	m_fAngle = 90.f;  //포신각도
	m_f_delta_angle = 0.f;

	m_fWidth = 50.000000f;  //이전 cx cy 개념

	Init_vPoint();


}

int PipeBlock::Update()
{
	//float f_deltaX(0.f);
	//float f_deltaY(0.f);

	//float x_1st = m_p_Player->Get_Info().vPos.x;
	//float y_1st = m_p_Player->Get_Info().vPos.y;
	//f_deltaX	= x_1st;
	//f_deltaY	= y_1st;

	Key_Input();
	//파이브블록의 라인리스트를 플레이어 포인터를 보내서 충돌처리
	/*if (f_deltaX != m_p_Player->Get_Info().vPos.x)
	{*/
	Collision_Player();

	if (m_e_PipeState == PIPE_STATE::PS_END)
	{
		Collision_Player_y();
	}
	/*}
	if (f_deltaY != m_p_Player->Get_Info().vPos.y)
	{
		Collision_Player_y();
	}*/

	if (m_e_PipeState != PIPE_STATE::PS_END)
	{
		Rotate_block();
	}



	return OBJ_NOEVENT;


}

void PipeBlock::Late_Update()
{

}

void PipeBlock::Render(HDC hDC)
{

	if (m_e_PipeState != PS_END)
	{
		//HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		//HPEN OldPen = (HPEN)SelectObject(hDC, hPen);
		//SelectObject(hDC, hPen);

		MoveToEx(hDC, (int)m_v_Rect_Point[0].x, (int)m_v_Rect_Point[0].y, nullptr);
		LineTo(hDC, (int)m_v_Rect_Point[1].x, (int)m_v_Rect_Point[1].y);
		LineTo(hDC, (int)m_v_Rect_Point[2].x, (int)m_v_Rect_Point[2].y);
		LineTo(hDC, (int)m_v_Rect_Point[3].x, (int)m_v_Rect_Point[3].y);
		LineTo(hDC, (int)m_v_Rect_Point[0].x, (int)m_v_Rect_Point[0].y);
		//SelectObject(hDC, OldPen);
		//DeleteObject(hPen);




		switch (m_e_PipeState)
		{
		case PS_00:  // 1자
	/*		MoveToEx(hDC, (int)m_vPoint[1].x, (int)m_vPoint[1].y, nullptr);
			LineTo(hDC, (int)m_vPoint[2].x, (int)m_vPoint[2].y);
			MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);
			LineTo(hDC, (int)m_vPoint[3].x, (int)m_vPoint[3].y);*/
			for (auto& iter : m_LineList)
				iter->Render(hDC);

			break;
		case PS_01:  // 1자
			//MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);
			//LineTo(hDC, (int)m_vPoint[5].x, (int)m_vPoint[5].y);
			//LineTo(hDC, (int)m_vPoint[3].x, (int)m_vPoint[3].y);
			//MoveToEx(hDC, (int)m_vPoint[1].x, (int)m_vPoint[1].y, nullptr);
			//LineTo(hDC, (int)m_vPoint[4].x, (int)m_vPoint[4].y);
			//LineTo(hDC, (int)m_vPoint[2].x, (int)m_vPoint[2].y);
			for (auto& iter : m_LineList)
				iter->Render(hDC);
			break;

		case PS_02:  // 10자
	/*		MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);
			LineTo(hDC, (int)m_vPoint[8].x, (int)m_vPoint[8].y);
			LineTo(hDC, (int)m_vPoint[7].x, (int)m_vPoint[7].y);

			MoveToEx(hDC, (int)m_vPoint[1].x, (int)m_vPoint[1].y, nullptr);
			LineTo(hDC, (int)m_vPoint[9].x, (int)m_vPoint[9].y);
			LineTo(hDC, (int)m_vPoint[2].x, (int)m_vPoint[2].y);

			MoveToEx(hDC, (int)m_vPoint[3].x, (int)m_vPoint[3].y, nullptr);
			LineTo(hDC, (int)m_vPoint[11].x, (int)m_vPoint[11].y);
			LineTo(hDC, (int)m_vPoint[4].x, (int)m_vPoint[4].y);

			MoveToEx(hDC, (int)m_vPoint[5].x, (int)m_vPoint[5].y, nullptr);
			LineTo(hDC, (int)m_vPoint[10].x, (int)m_vPoint[10].y);
			LineTo(hDC, (int)m_vPoint[6].x, (int)m_vPoint[6].y);*/

			for (auto& iter : m_LineList)
				iter->Render(hDC);
			break;

		case PS_03:  // ㅗ자
			//MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);
			//LineTo(hDC, (int)m_vPoint[3].x, (int)m_vPoint[3].y);
			//LineTo(hDC, (int)m_vPoint[2].x, (int)m_vPoint[2].y);
			//MoveToEx(hDC, (int)m_vPoint[1].x, (int)m_vPoint[1].y, nullptr);
			//LineTo(hDC, (int)m_vPoint[5].x, (int)m_vPoint[5].y);
			//LineTo(hDC, (int)m_vPoint[4].x, (int)m_vPoint[4].y);
			//MoveToEx(hDC, (int)m_vPoint[6].x, (int)m_vPoint[6].y, nullptr);
			//LineTo(hDC, (int)m_vPoint[7].x, (int)m_vPoint[7].y);
			for (auto& iter : m_LineList)
				iter->Render(hDC);
		default:
			break;
		}
	}
	else
	{
		//MoveToEx(hDC, (int)m_v_Rect_Point_Origin[0].x, (int)m_v_Rect_Point_Origin[0].y, nullptr);
		//LineTo(hDC, (int)m_v_Rect_Point_Origin[1].x, (int)m_v_Rect_Point_Origin[1].y);
		//LineTo(hDC, (int)m_v_Rect_Point_Origin[2].x, (int)m_v_Rect_Point_Origin[2].y);
		//LineTo(hDC, (int)m_v_Rect_Point_Origin[3].x, (int)m_v_Rect_Point_Origin[3].y);
		//LineTo(hDC, (int)m_v_Rect_Point_Origin[0].x, (int)m_v_Rect_Point_Origin[0].y);

		for (auto& iter : m_LineList)
			iter->Render(hDC);
	}



}

void PipeBlock::Release()
{
}

void PipeBlock::Init_vPoint() //enum에 따라세팅
{
	if (m_e_PipeState != PS_END)
	{

		m_v_Rect_Point[0] = { m_tInfo.vPos.x - m_fWidth, m_tInfo.vPos.y - m_fWidth, 0.f };
		m_v_Rect_Point[1] = { m_tInfo.vPos.x + m_fWidth, m_tInfo.vPos.y - m_fWidth, 0.f };
		m_v_Rect_Point[2] = { m_tInfo.vPos.x + m_fWidth, m_tInfo.vPos.y + m_fWidth, 0.f };
		m_v_Rect_Point[3] = { m_tInfo.vPos.x - m_fWidth, m_tInfo.vPos.y + m_fWidth, 0.f };
		for (int i = 0; i < 4; ++i)
			m_v_Rect_Point_Origin[i] = m_v_Rect_Point[i];

		switch (m_e_PipeState)
		{
		case PS_00:  // 1자
			m_fAngle = 0.f;  //포신각도
			m_vPoint[0] = { m_tInfo.vPos.x - m_fWidth / 6.0f, m_tInfo.vPos.y - m_fWidth , 0.f };
			m_vPoint[1] = { m_tInfo.vPos.x + m_fWidth / 6.0f, m_tInfo.vPos.y - m_fWidth , 0.f };
			m_vPoint[2] = { m_tInfo.vPos.x + m_fWidth / 6.0f, m_tInfo.vPos.y + m_fWidth , 0.f };
			m_vPoint[3] = { m_tInfo.vPos.x - m_fWidth / 6.0f, m_tInfo.vPos.y + m_fWidth , 0.f };
			for (int i = 0; i < 4; ++i)
				m_vPoint_Origin[i] = m_vPoint[i];

		


			break;
		case PS_01:
			m_fAngle = 90.f;  //포신각도
			m_vPoint[0] = { m_tInfo.vPos.x - m_fWidth / 6.0f, m_tInfo.vPos.y - m_fWidth , 0.f };
			m_vPoint[1] = { m_tInfo.vPos.x + m_fWidth / 6.0f, m_tInfo.vPos.y - m_fWidth , 0.f };
			m_vPoint[2] = { m_tInfo.vPos.x + m_fWidth , m_tInfo.vPos.y - m_fWidth / 6.0f, 0.f };
			m_vPoint[3] = { m_tInfo.vPos.x + m_fWidth , m_tInfo.vPos.y + m_fWidth / 6.0f, 0.f };
			m_vPoint[4] = { m_tInfo.vPos.x + m_fWidth / 6.0f, m_tInfo.vPos.y - m_fWidth / 6.0f, 0.f };
			m_vPoint[5] = { m_tInfo.vPos.x - m_fWidth / 6.0f, m_tInfo.vPos.y + m_fWidth / 6.0f, 0.f };

			for (int i = 0; i < 6; ++i)
				m_vPoint_Origin[i] = m_vPoint[i];
			break;

		case PS_02:
			m_vPoint[0] = { m_tInfo.vPos.x - m_fWidth / 6.0f, m_tInfo.vPos.y - m_fWidth , 0.f };
			m_vPoint[1] = { m_tInfo.vPos.x + m_fWidth / 6.0f, m_tInfo.vPos.y - m_fWidth , 0.f };
			m_vPoint[2] = { m_tInfo.vPos.x + m_fWidth , m_tInfo.vPos.y - m_fWidth / 6.0f, 0.f };
			m_vPoint[3] = { m_tInfo.vPos.x + m_fWidth , m_tInfo.vPos.y + m_fWidth / 6.0f, 0.f };
			m_vPoint[4] = { m_tInfo.vPos.x + m_fWidth / 6.0f, m_tInfo.vPos.y + m_fWidth , 0.f };
			m_vPoint[5] = { m_tInfo.vPos.x - m_fWidth / 6.0f, m_tInfo.vPos.y + m_fWidth , 0.f };
			m_vPoint[6] = { m_tInfo.vPos.x - m_fWidth , m_tInfo.vPos.y + m_fWidth / 6.0f, 0.f };
			m_vPoint[7] = { m_tInfo.vPos.x - m_fWidth , m_tInfo.vPos.y - m_fWidth / 6.0f, 0.f };
			m_vPoint[8] = { m_tInfo.vPos.x - m_fWidth / 6.0f, m_tInfo.vPos.y - m_fWidth / 6.0f, 0.f };
			m_vPoint[9] = { m_tInfo.vPos.x + m_fWidth / 6.0f, m_tInfo.vPos.y - m_fWidth / 6.0f, 0.f };
			m_vPoint[10] = { m_tInfo.vPos.x - m_fWidth / 6.0f, m_tInfo.vPos.y + m_fWidth / 6.0f, 0.f };
			m_vPoint[11] = { m_tInfo.vPos.x + m_fWidth / 6.0f, m_tInfo.vPos.y + m_fWidth / 6.0f, 0.f };


			for (int i = 0; i < 12; ++i)
				m_vPoint_Origin[i] = m_vPoint[i];
			break;

		case PS_03:
			m_fAngle = 90.f;  //포신각도
			m_vPoint[0] = { m_tInfo.vPos.x - m_fWidth / 6.0f, m_tInfo.vPos.y - m_fWidth , 0.f };
			m_vPoint[1] = { m_tInfo.vPos.x + m_fWidth / 6.0f, m_tInfo.vPos.y - m_fWidth , 0.f };
			m_vPoint[2] = { m_tInfo.vPos.x - m_fWidth , m_tInfo.vPos.y - m_fWidth / 6.0f, 0.f };
			m_vPoint[3] = { m_tInfo.vPos.x - m_fWidth / 6.0f, m_tInfo.vPos.y - m_fWidth / 6.0f, 0.f };
			m_vPoint[4] = { m_tInfo.vPos.x + m_fWidth , m_tInfo.vPos.y - m_fWidth / 6.0f, 0.f };
			m_vPoint[5] = { m_tInfo.vPos.x + m_fWidth / 6.0f, m_tInfo.vPos.y - m_fWidth / 6.0f, 0.f };
			m_vPoint[6] = { m_tInfo.vPos.x - m_fWidth , m_tInfo.vPos.y + m_fWidth / 6.0f, 0.f };
			m_vPoint[7] = { m_tInfo.vPos.x + m_fWidth , m_tInfo.vPos.y + m_fWidth / 6.0f, 0.f };
			for (int i = 0; i < 8; ++i)
				m_vPoint_Origin[i] = m_vPoint[i];
			break;
		default:
			break;


		}

	}
	else
	{

		m_v_Rect_Point[0] = { m_tInfo.vPos.x - m_fWidth, m_tInfo.vPos.y - m_fWidth, 0.f };
		m_v_Rect_Point[1] = { m_tInfo.vPos.x + m_fWidth, m_tInfo.vPos.y - m_fWidth, 0.f };
		m_v_Rect_Point[2] = { m_tInfo.vPos.x + m_fWidth * 0.5f, m_tInfo.vPos.y + m_fWidth * 0.5f, 0.f };
		m_v_Rect_Point[3] = { m_tInfo.vPos.x - m_fWidth * 0.5f, m_tInfo.vPos.y + m_fWidth * 0.5f, 0.f };
		for (int i = 0; i < 4; ++i)
			m_v_Rect_Point_Origin[i] = m_v_Rect_Point[i];
	}

	Update_lineList();
}

void PipeBlock::Rotate_block() //enum에 따라 회전
{
	if (m_b_ClickFlag)
	{
		m_fAngle += (3.f);

		if (m_fAngle - m_f_delta_angle >= 90.f)
		{
			m_f_delta_angle = 0.f;
			m_b_ClickFlag = false;
			RotationState_update();

		}

		D3DXMATRIX	matScale, matRotZ, matTrans;

		D3DXMatrixScaling(&matScale, -1.f, 1.f, 1.f);
		// // 크기 변환 행렬을 만들어주는 함수
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
		// // 이동 변환 행렬을 만들어주는 함수

		m_tInfo.matWorld = matScale * matRotZ * matTrans;
		for (int i = 0; i < 4; ++i)
		{
			m_v_Rect_Point[i] = m_v_Rect_Point_Origin[i];
			m_v_Rect_Point[i] -= {m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f};

			D3DXVec3TransformCoord(&m_v_Rect_Point[i], &m_v_Rect_Point[i], &m_tInfo.matWorld);	
		}

		switch (m_e_PipeState)
		{
		case PS_00:  // 1자
			for (int i = 0; i < 4; ++i)
			{
				m_vPoint[i] = m_vPoint_Origin[i];
			//	m_vPoint[i] -= { WINCX * 0.5f, WINCY * 0.5f, 0.f};
				m_vPoint[i] -= { m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f};
				D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);


			}
			break;
		case PS_01:  // 1자
			for (int i = 0; i < 6; ++i)
			{
				m_vPoint[i] = m_vPoint_Origin[i];
				m_vPoint[i] -= { m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f};

				D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
			}
			break;

		case PS_02:  // 1자
			for (int i = 0; i < 12; i++)
			{
				m_vPoint[i] = m_vPoint_Origin[i];
				m_vPoint[i] -= { m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f};

				D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
			}

		case PS_03:  // 1자
			for (int i = 0; i < 8; i++)
			{
				m_vPoint[i] = m_vPoint_Origin[i];
				m_vPoint[i] -= { m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f};

				D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
			}
			break;
		}

		Update_lineList();
	}
}

//Rotation  enum update
void PipeBlock::RotationState_update()
{
	switch (m_e_RotationState)
	{
	case RS_12:
		m_e_RotationState = RS_03;
		break;
	case RS_03:
		m_e_RotationState = RS_06;
		break;

	case RS_06:
		m_e_RotationState = RS_09;
		break;
	case RS_09:
		m_e_RotationState = RS_12;
		break;
	default:
		m_e_RotationState = RS_END;
		break;


	}

}



void PipeBlock::Update_lineList()
{
	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	m_LineList.clear();

	LINEPOINT	tLine[12];
	switch (m_e_PipeState)
	{
	case PS_00:  // 1자
		tLine[0] = { m_vPoint[0].x, m_vPoint[0].y };
		tLine[1] = { m_vPoint[3].x, m_vPoint[3].y };
		tLine[2] = { m_vPoint[1].x, m_vPoint[1].y };
		tLine[3] = { m_vPoint[2].x, m_vPoint[2].y };


		m_LineList.push_back(new CLine(tLine[0], tLine[1], LINE_TYPE::LT_NONPASS));
		m_LineList.push_back(new CLine(tLine[2], tLine[3], LINE_TYPE::LT_NONPASS));


		break;
	case PS_01:
		tLine[0] = { m_vPoint[0].x, m_vPoint[0].y };
		tLine[1] = { m_vPoint[5].x, m_vPoint[5].y };
		tLine[2] = { m_vPoint[3].x, m_vPoint[3].y };
		tLine[3] = { m_vPoint[1].x, m_vPoint[1].y };
		tLine[4] = { m_vPoint[4].x, m_vPoint[4].y };
		tLine[5] = { m_vPoint[2].x, m_vPoint[2].y };

		m_LineList.push_back(new CLine(tLine[0], tLine[1], LINE_TYPE::LT_NONPASS));
		m_LineList.push_back(new CLine(tLine[1], tLine[2], LINE_TYPE::LT_NONPASS));
		m_LineList.push_back(new CLine(tLine[3], tLine[4], LINE_TYPE::LT_NONPASS));
		m_LineList.push_back(new CLine(tLine[4], tLine[5], LINE_TYPE::LT_NONPASS));

		break;

	case PS_02:
		tLine[0]  = { m_vPoint[0].x	, m_vPoint[0].y };
		tLine[1]  = { m_vPoint[8].x	, m_vPoint[8].y };
		tLine[2]  = { m_vPoint[7].x	, m_vPoint[7].y };

		tLine[3]  = { m_vPoint[1].x	, m_vPoint[1].y };
		tLine[4]  = { m_vPoint[9].x	, m_vPoint[9].y };
		tLine[5]  = { m_vPoint[2].x	, m_vPoint[2].y };

		tLine[6]  = { m_vPoint[3].x	, m_vPoint[3].y };
		tLine[7]  = { m_vPoint[11].x, m_vPoint[11].y };
		tLine[8]  = { m_vPoint[4].x	, m_vPoint[4].y };

		tLine[9]  = { m_vPoint[5].x	, m_vPoint[5].y };
		tLine[10] = { m_vPoint[10].x, m_vPoint[10].y };
		tLine[11] = { m_vPoint[6].x	, m_vPoint[6].y };

		m_LineList.push_back(new CLine(tLine[0], tLine[1], LINE_TYPE::LT_NONPASS));
		m_LineList.push_back(new CLine(tLine[1], tLine[2], LINE_TYPE::LT_NONPASS));

		m_LineList.push_back(new CLine(tLine[3], tLine[4], LINE_TYPE::LT_NONPASS));
		m_LineList.push_back(new CLine(tLine[4], tLine[5], LINE_TYPE::LT_NONPASS));
		
		m_LineList.push_back(new CLine(tLine[6], tLine[7], LINE_TYPE::LT_NONPASS));
		m_LineList.push_back(new CLine(tLine[7], tLine[8], LINE_TYPE::LT_NONPASS));

		m_LineList.push_back(new CLine(tLine[9], tLine[10], LINE_TYPE::LT_NONPASS));
		m_LineList.push_back(new CLine(tLine[10], tLine[11], LINE_TYPE::LT_NONPASS));




		break;

	case PS_03:
		tLine[0] = { m_vPoint[0].x	, m_vPoint[0].y };
		tLine[1] = { m_vPoint[3].x	, m_vPoint[3].y };
		tLine[2] = { m_vPoint[2].x	, m_vPoint[2].y };

		tLine[3] = { m_vPoint[1].x	, m_vPoint[1].y };
		tLine[4] = { m_vPoint[4].x	, m_vPoint[4].y };
		tLine[5] = { m_vPoint[5].x	, m_vPoint[5].y };

		tLine[6] = { m_vPoint[6].x	, m_vPoint[6].y };
		tLine[7] = { m_vPoint[7].x  , m_vPoint[7].y };


		m_LineList.push_back(new CLine(tLine[0], tLine[1], LINE_TYPE::LT_NONPASS));
		m_LineList.push_back(new CLine(tLine[1], tLine[2], LINE_TYPE::LT_NONPASS));

		m_LineList.push_back(new CLine(tLine[3], tLine[5], LINE_TYPE::LT_NONPASS));
		m_LineList.push_back(new CLine(tLine[5], tLine[4], LINE_TYPE::LT_NONPASS));

		m_LineList.push_back(new CLine(tLine[6], tLine[7], LINE_TYPE::LT_NONPASS));



		break;

	case PS_END:

		tLine[0] = { m_v_Rect_Point[0].x, m_v_Rect_Point[0].y };
		tLine[1] = { m_v_Rect_Point[1].x, m_v_Rect_Point[1].y };
		tLine[2] = { m_v_Rect_Point[2].x, m_v_Rect_Point[2].y };
		tLine[3] = { m_v_Rect_Point[3].x, m_v_Rect_Point[3].y };


		m_LineList.push_back(new CLine(tLine[0], tLine[1], LINE_TYPE::LT_NONPASS));
		m_LineList.push_back(new CLine(tLine[1], tLine[2], LINE_TYPE::LT_NONPASS));
		m_LineList.push_back(new CLine(tLine[2], tLine[3], LINE_TYPE::LT_NONPASS));
		m_LineList.push_back(new CLine(tLine[3], tLine[0], LINE_TYPE::LT_NONPASS));


		break;
	}
}



void PipeBlock::Collision_Player_x()
{
	for (auto& iter : m_LineList)
	{
		float f_deltaX(0.f);
		float f_deltaY(0.f);

		float x_1st = m_p_Player->Get_Info().vPos.x;
		float y_1st = m_p_Player->Get_Info().vPos.y;
		bool bLineCol = false;

		float right_x, left_x, right_y, left_y;
		if (iter->Get_Info().tLPoint.fY <= iter->Get_Info().tRPoint.fY)
		{
			left_y = iter->Get_Info().tLPoint.fY;
			right_y = iter->Get_Info().tRPoint.fY;
		}
		else
		{
			right_y = iter->Get_Info().tLPoint.fY;
			left_y = iter->Get_Info().tRPoint.fY;
		}

		if (iter->Get_Info().tLPoint.fX <= iter->Get_Info().tRPoint.fX)
		{
			left_x = iter->Get_Info().tLPoint.fX;
			right_x = iter->Get_Info().tRPoint.fX;
		}
		else 
		{
			right_x = iter->Get_Info().tLPoint.fX;
			left_x  = iter->Get_Info().tRPoint.fX;
		}


		if (   left_y	>= m_p_Player->Get_Info().vPos.y - m_p_Player->Get_width()
			&& right_y	<= m_p_Player->Get_Info().vPos.y + m_p_Player->Get_width()
			&& left_x	>= m_p_Player->Get_Info().vPos.x - m_p_Player->Get_width()
			&& left_y	<= m_p_Player->Get_Info().vPos.x + m_p_Player->Get_width()
			&& iter->Get_LineType() == LINE_TYPE::LT_NONPASS)
		{
			bLineCol = true;
			f_deltaX = m_p_Player->Get_Info().vPos.x;
			f_deltaY = m_p_Player->Get_Info().vPos.y;
		}

		if (bLineCol)
		{

			if (x_1st <= f_deltaX)  //
			{
				f_deltaX = f_deltaX - m_p_Player->Get_width() * 0.5f;
			}
			else
			{
				f_deltaX = f_deltaX + m_p_Player->Get_width() * 0.5f;
			}

			if (y_1st <= f_deltaY)  //
			{
				f_deltaY = f_deltaY - m_p_Player->Get_width() * 0.5f;
			}
			else
			{
				f_deltaY = f_deltaY + m_p_Player->Get_width() * 0.5f;
			}

			m_p_Player->Set_Pos(f_deltaX, f_deltaY);
		}

	}

	float	fX(0.f), fY(0.f);

	//for (auto& Dst : _Dst)
	//{
	//	for (auto& Src : _Src)
	//	{
	//		if (Check_Rect(Dst, Src, &fX, &fY))
	//		{
	//			if (fX > fY) // 상하 충돌
	//			{
	//				// 상 충돌
	//				if (Dst->Get_Info().fY < Src->Get_Info().fY)
	//				{
	//					Dst->Set_PosY(-fY);
	//				}
	//				// 하 충돌
	//				else
	//				{
	//					Dst->Set_PosY(fY);
	//				}
	//			}

	//			else 		// 좌우 충돌
	//			{
	//				// 좌 충돌
	//				if (Dst->Get_Info().fX < Src->Get_Info().fX)
	//				{
	//					Dst->Set_PosX(-fX);
	//				}
	//				// 우 충돌
	//				else
	//				{
	//					Dst->Set_PosX(fX);
	//				}
	//			}
	//		}
	//	}
	//}

}

void PipeBlock::Collision_Player_y()
{
	
	for (auto iter : m_LineList)
	{
		float f_deltaX(0.f);
		float f_deltaY(0.f);

		float x_1st = m_p_Player->Get_Info().vPos.x;
		float y_1st = m_p_Player->Get_Info().vPos.y;
		
		bool bLineCol = false;

		float right_x, left_x, right_y, left_y;
		if (iter->Get_Info().tLPoint.fY <= iter->Get_Info().tRPoint.fY) // 작거나 같다 = 위에 있다
		{
			left_y = iter->Get_Info().tLPoint.fY; // 작은쪽이 left -LPoint
			right_y = iter->Get_Info().tRPoint.fY;
		}
		else //
		{
			left_y = iter->Get_Info().tRPoint.fY;   // tRPoint 가  left
			right_y = iter->Get_Info().tLPoint.fY; 
		}

		if (iter->Get_Info().tLPoint.fX <= iter->Get_Info().tRPoint.fX)
		{
			left_x = iter->Get_Info().tLPoint.fX;
			right_x = iter->Get_Info().tRPoint.fX;
		}
		else
		{
			right_x = iter->Get_Info().tLPoint.fX;
			left_x = iter->Get_Info().tRPoint.fX;
		}


		if (   left_y  <= m_p_Player->Get_Info().vPos.y - m_p_Player->Get_width()
			&& right_y >= m_p_Player->Get_Info().vPos.y + m_p_Player->Get_width()
			)
		{
			if (	left_x <= m_p_Player->Get_Info().vPos.x - m_p_Player->Get_width()
				&& right_x >= m_p_Player->Get_Info().vPos.x + m_p_Player->Get_width()
				)
			{
				CObjMgr::Get_Instance()->Set_nextScene_lee(true);

			}
		}
	}
}

void PipeBlock::Collision_Player()
{
	for (auto& iter : m_LineList)
	{
		float f_deltaX(0.f);
		float f_deltaY(0.f);

		float x_1st = m_p_Player->Get_Info().vPos.x;
		float y_1st = m_p_Player->Get_Info().vPos.y;
		bool bLineCol = false;

		float right_x, left_x, right_y, left_y;
		if (iter->Get_Info().tLPoint.fY <= iter->Get_Info().tRPoint.fY)
		{
			left_y = iter->Get_Info().tLPoint.fY;
			right_y = iter->Get_Info().tRPoint.fY;
		}
		else
		{
			right_y = iter->Get_Info().tLPoint.fY;
			left_y = iter->Get_Info().tRPoint.fY;
		}

		if (iter->Get_Info().tLPoint.fX <= iter->Get_Info().tRPoint.fX)
		{
			left_x = iter->Get_Info().tLPoint.fX;
			right_x = iter->Get_Info().tRPoint.fX;
		}
		else
		{
			right_x = iter->Get_Info().tLPoint.fX;
			left_x = iter->Get_Info().tRPoint.fX;
		}


		if (left_y >= m_p_Player->Get_Info().vPos.y - m_p_Player->Get_width()
			&& right_y <= m_p_Player->Get_Info().vPos.y + m_p_Player->Get_width()
			&& left_x >= m_p_Player->Get_Info().vPos.x - m_p_Player->Get_width()
			&& left_y <= m_p_Player->Get_Info().vPos.x + m_p_Player->Get_width()
			&& iter->Get_LineType() == LINE_TYPE::LT_NONPASS)
		{
			bLineCol = true;
			f_deltaX = m_p_Player->Get_Info().vPos.x;
			f_deltaY = m_p_Player->Get_Info().vPos.y;
		}

		if (bLineCol)
		{

			if (x_1st <= f_deltaX)  //
			{
				f_deltaX = f_deltaX - m_p_Player->Get_width() * 0.5f;
			}
			else
			{
				f_deltaX = f_deltaX + m_p_Player->Get_width() * 0.5f;
			}

			if (y_1st <= f_deltaY)  //
			{
				f_deltaY = f_deltaY - m_p_Player->Get_width() * 0.5f;
			}
			else
			{
				f_deltaY = f_deltaY + m_p_Player->Get_width() * 0.5f;
			}

			m_p_Player->Set_Pos(x_1st, y_1st);
		}
	}
}