#pragma once

#include "Obj.h"


class CTexture;

class CUi  : public CObj
{
public:
	enum UI_STATE { UI_IDLE , UI_NEXT ,UI_WIN ,UI_LOSE ,UI_END};
	CUi();
	virtual ~CUi();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update()override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

protected:
	UI_STATE				m_ePreState;
	UI_STATE				m_eCurState;
	//¿Í¸®¿À
	vector<CTexture*>	m_vecTexture;
};

