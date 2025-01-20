#pragma once

#include "Obj.h"
class CLine;
class PipeBall;
class PipeBlock : public CObj
{
public:
	PipeBlock();
	virtual ~PipeBlock();



public:
	PIPE_STATE		Get_PipeState() { return m_e_PipeState; }
	void			Set_PipeState(PIPE_STATE _ps) { m_e_PipeState = _ps; }
	ROTATION_STATE	Get_RotationState() { return m_e_RotationState; }
	void			Set_RotationState(ROTATION_STATE _ps) { m_e_RotationState = _ps; }
	//bool			Get_ClickFlag() { return m_b_ClickFlag; }
	//void			Set_PipeState(bool _ps) { m_b_ClickFlag= _ps; }

	void			Init_vPoint();
	void			Set_player(CObj* _p) { m_p_Player = _p; }
		
public:
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void Late_Update()override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void		Key_Input();
	void		RotationState_update(); // RS enum update
	void		Rotate_block();  //enum 에 따라 회전 시키는 함수
	void		Update_lineList();
	void		Collision_Player_x();
	void		Collision_Player_y();
	void		Collision_Player();
protected:
	PIPE_STATE			m_e_PipeState; //블록의 모양 
	ROTATION_STATE		m_e_RotationState; // 회전상태 기본 RS_12
	bool				m_b_ClickFlag; //눌러지면 true되고 update

	D3DXVECTOR3			m_v_Rect_Point[4];
	D3DXVECTOR3			m_v_Rect_Point_Origin[4];

	D3DXVECTOR3			m_vPoint[12];
	D3DXVECTOR3			m_vPoint_Origin[12];

	float				m_f_delta_angle;
	list<CLine*>		m_LineList;
	CObj* m_p_Player;
};

