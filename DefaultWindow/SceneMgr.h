#pragma once

#include "Define.h"

class CScene;


class CSceneMgr
{
	SINGLE(CSceneMgr)

	
public:
	SCENEID			Get_Scene() { return m_eCurScene; }
	SCENEID			Get_Scene_pre() { return m_ePreScene; }


public:
	void			Scene_Change(SCENEID eID);

	void		    init();
	void			Update();
	void			Late_Update();
	void			Render(HDC hDC);
	void			Release();

    CScene* Get_pScene_pre() { return m_pScene_Pre; }
	CScene* Get_pScene() { return m_pScene; }

private:
	//static CSceneMgr*		m_pInstance;
	vector<CScene*> m_vecGameScene;
	CScene* m_pScene;
	CScene* m_pScene_Pre;

	SCENEID					m_ePreScene;
	SCENEID					m_eCurScene;



};

