#pragma once

#include "Obj.h"
#include "CTexture.h"

class UI_Number : public CObj
{
public:
	UI_Number();
	virtual ~UI_Number();

public:
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void Late_Update()override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;


	void		Set_NumberState(NUMBER_STATE _NS) { m_eNumberState = _NS; }
protected:
	vector<CTexture*>	m_vecTexture;
	NUMBER_STATE		m_eNumberState;

	int					m_i_UD_Count; 
};

