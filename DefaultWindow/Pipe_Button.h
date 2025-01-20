#pragma once

#include "Obj.h"

class LINE_lee;
class Pipe_Button : public CObj
{
public:
	Pipe_Button();
	virtual ~Pipe_Button();



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


};

