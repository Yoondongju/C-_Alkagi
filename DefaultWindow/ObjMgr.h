#pragma once

#include "Obj.h"
#include "Define.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj*		Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }
	list<CObj*>& find_ObjList(OBJID _objid ) { return m_ObjList[_objid]; }

	//&화 안시켜서 그동안 문제

	CObj*		Get_Target(OBJID eID, CObj* pObj);

	CObj*		Get_Target_Mouse(OBJID eID, POINT* px);

	CObj* find_ObjList_framekey(OBJID _objid, TCHAR* pFrameKey)
	{
		CObj* pResult = nullptr;
		for (auto& iter : find_ObjList(_objid))
		{
			if (iter->Get_FrameKey() == pFrameKey)
			{
				pResult = iter;
			}
		}

		return pResult;
	}

public:

	void		Add_Object(OBJID eID, CObj* pObj);
	
	void		Update();		
	void		Late_Update();
	void		Render(HDC hDC);		
	void		Release();

	void		Delete_ID(OBJID eID);






	//EFFECT_STATE    Get_SS() const { return m_eScenestate; }
	//void			Set_SS(EFFECT_STATE _b) { m_eScenestate = _b; }
	ANIME_RESULT    Get_GS() const { return m_eAnime_State; }
	void			Set_GS(ANIME_RESULT _b) { m_eAnime_State = _b; }





	int				Get_Score() { return m_iScore; }
	void			Add_Score(int _iHP) { m_iScore += _iHP; }

	//int				Get_Gold() const { return m_iGold; }
	//void			Set_Gold(int _L) { m_iGold = _L; }



	void	Set_Player_visible(bool _b) { m_b_Player_visible = _b; };
	bool	Get_Player_visible() {return  m_b_Player_visible ; };
	void	Set_nextScene_lee(bool _b) { m_b_nextScene_lee = _b; };
	bool	Get_nextScene_lee() { return m_b_nextScene_lee ; };

private:
	list<CObj*>	m_ObjList[OBJ_END];


public:
	static CObjMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

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

protected:
	static CObjMgr*		m_pInstance;



	ANIME_RESULT m_eAnime_State;  // 애니메이션 상태값
	

	int m_iScore;
	int m_iGold;

	int m_iSceneList[MINIGAME_TOTAL]; //임시로 5


	bool m_b_Player_visible;
	bool m_b_nextScene_lee;


};

