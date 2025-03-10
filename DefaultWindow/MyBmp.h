#pragma once

#include "Define.h"

class CMyBmp
{
public:
	CMyBmp();
	~CMyBmp();

public:
	HDC			Get_MemDC() { return m_hMemDC; }

	void		Load_Bmp(const TCHAR* pFilePath,int _iX,int _iY);
	void		Release();

private:
	HDC			m_hMemDC;

	HBITMAP		m_hBitmap;
	HBITMAP		m_hOldBmp;
};

