#include "stdafx.h"
#include "Line.h"



CLine::CLine() //:m_eLineType(LINETYPE::LINEEND)
{
	ZeroMemory(&m_tInfo, sizeof(LINE));
}

CLine::CLine(LINEPOINT& tLPoint, LINEPOINT& tRPoint, LINE_TYPE _LINETYPE) : m_tInfo(tLPoint, tRPoint), m_eLineType(_LINETYPE)
{
}



CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	
	MoveToEx(hDC, int(m_tInfo.tLPoint.fX ), (int)m_tInfo.tLPoint.fY, nullptr);
	LineTo(hDC, int(m_tInfo.tRPoint.fX ), (int)m_tInfo.tRPoint.fY);
}
