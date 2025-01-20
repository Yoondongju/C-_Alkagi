#include "stdafx.h"
#include "Line_lee.h"



CLine_lee::CLine_lee() //:m_eLineType(LINETYPE::LINEEND)
{
	ZeroMemory(&m_tInfo, sizeof(LINE));
}


//CLine_lee::CLine_lee(LINEPOINT& tLPoint, LINEPOINT& tRPoint, LINE_TYPE _LINETYPE)
//	:  m_tInfo(tLPoint, tRPoint)
//	, m_e_LineType(LINE_TYPE::_LINETYPE) 
//{
//	ZeroMemory(&m_tInfo, sizeof(LINE));
//}
CLine_lee::CLine_lee(LINEPOINT& tLPoint, LINEPOINT& tRPoint, LINE_TYPE _LINETYPE) : m_tInfo(tLPoint, tRPoint), m_e_LineType(_LINETYPE)
{
}


CLine_lee::~CLine_lee()
{
}

void CLine_lee::Render(HDC hDC)
{

	MoveToEx(hDC, int(m_tInfo.tLPoint.fX), (int)m_tInfo.tLPoint.fY, nullptr);
	LineTo(hDC, int(m_tInfo.tRPoint.fX), (int)m_tInfo.tRPoint.fY);
}
