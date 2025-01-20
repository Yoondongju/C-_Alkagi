#pragma once

#include "Obj.h"

class LINE_lee;
class PipeBall : public CObj
{
public:
	PipeBall();
	virtual ~PipeBall();



public:

public:
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void Late_Update()override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:


	void		Key_Input();


protected:


	D3DXVECTOR3					m_vPoint[4];
	D3DXVECTOR3					m_vPoint_Origin[4];


	bool m_b_W_flag;
	bool m_b_S_flag;

	float m_start_x;
	float m_start_y;
	list<LINE_lee*>			m_LineList;

};

