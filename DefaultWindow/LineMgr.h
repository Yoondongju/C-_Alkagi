#pragma once

#include "Line.h"

class CObj;

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	bool		Collision_Line(float& fX, float* pY);
	bool		Collision_Line_Vertical_up(CObj* pObj, float* pY);
	bool		Collision_Line_Vertical_down(CObj* pObj, float* pY);

	bool		Collision_Line_WALL(CObj* pObj, float* pX, float* pY);// 이준식 
	bool		Collision_Line_PipeBall(CObj* pObj, float* pX, float* pY);// 이준식 

public:
	void		Render(HDC hDC);
	void		Release();
	void		Load_Line();
	void		Initialize(SCENEID _type);
	void		Load_Line_type(SCENEID _type);





public:
	static CLineMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CLineMgr;

		return m_pInstance;
	}
	static void		Destroy()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CLineMgr*		m_pInstance;
	list<CLine*>			m_LineList;
};

