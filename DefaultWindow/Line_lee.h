#pragma once

#include "Define.h"

class CLine_lee
{
public:
	CLine_lee();
//	CLine_lee(LINEPOINT& tLPoint, LINEPOINT& tRPoint);
	CLine_lee(LINEPOINT& tLPoint, LINEPOINT& tRPoint, LINE_TYPE _LINETYPE);
	//CLine_lee(LINE& tLine);
	~CLine_lee();

public:
	const LINE& Get_Info() const { return m_tInfo; }
	//	LINETYPE		Get_LineType() { return m_eLineType; }
public:
	void		Render(HDC hDC);

private:
	LINE		m_tInfo;
	LINE_TYPE	m_e_LineType;  //라인별 타입체크
};

