#pragma once

#include "Define.h"

class CLine
{
public:
	CLine();
	//CLine(LINEPOINT& tLPoint, LINEPOINT& tRPoint);
	CLine(LINEPOINT& tLPoint, LINEPOINT& tRPoint, LINE_TYPE _LINETYPE);
	CLine(LINE& tLine);
	~CLine();

public:
	const LINE&		Get_Info() const { return m_tInfo; }
	LINE_TYPE		Get_LineType() { return m_eLineType; }
public:
	void		Render(HDC hDC);

private:
	LINE		m_tInfo;
	LINE_TYPE	m_eLineType;  //라인별 타입체크
};

