#pragma once

#include "Define.h"

class CScene abstract
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual		void		Initialize()	PURE;
	virtual		int			Update()		;
	virtual		void		Late_Update()	PURE;
	virtual		void		Render(HDC hDC)	PURE;
	virtual		void		Release()		PURE;


	virtual void		Enter() PURE;
	virtual void		Exit();



protected:
	bool	m_bSuccess;

};

