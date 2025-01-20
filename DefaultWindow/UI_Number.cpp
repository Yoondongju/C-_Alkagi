#include "stdafx.h"
#include "UI_Number.h"

#include "AbstractFactory.h"

#include "BmpMgr.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "ObjMgr.h"
#include "SceneMgr.h"


UI_Number::UI_Number() : m_eNumberState(NS_END)  
{

}

UI_Number::~UI_Number()
{
	Release();
}

void UI_Number::Release()
{
	for (auto& iter : m_vecTexture)
	{
		Safe_Delete<CTexture*>(iter);
	}
	m_vecTexture.clear();

}

void UI_Number::Initialize()
{

	//m_tInfo = { 400.f, 750.f, 800.f, 100.f }; //임시주석

	//m_eCurState = UI_IDLE;
	m_pFrameKey = L"UI_NUMBER";


	m_eObjType = OBJID::OBJ_UI;
	m_eColorid = COLORID::COLOR_END;
	CreateAnimator();	

	m_vecTexture.push_back(new CTexture);
	m_vecTexture.back()->Load(L"../Image/Api/Text_Number/Number_new_2.bmp");
	GetAnimator()->CreateAnimation(L"UI_Number_State_00",  // 00
		m_vecTexture.back(),   //사이즈 129.34
		Vec2(0.f, 0.f),
		Vec2(8.f, 11.f),  //slicesize
		Vec2(0.f, 0.f), //step 
		1.f,	//only 1
		1);  //framecount

	m_vecTexture.push_back(new CTexture);
	m_vecTexture.back()->Load(L"../Image/Api/Text_Number/Number_new_2.bmp");
	GetAnimator()->CreateAnimation(L"UI_Number_State_01",  // 01
		m_vecTexture.back(),   //사이즈 129.34
		Vec2(8.f * 1, 0.f),
		Vec2(8.f, 11.f),  //slicesize
		Vec2(0.f, 0.f), //step 
		1.f,	//only 1
		1);  //framecount

	m_vecTexture.push_back(new CTexture);
	m_vecTexture.back()->Load(L"../Image/Api/Text_Number/Number_new_2.bmp");
	GetAnimator()->CreateAnimation(L"UI_Number_State_02",  // 02
		m_vecTexture.back(),   //사이즈 129.34
		Vec2(8.f * 2, 0.f),
		Vec2(8.f, 11.f),  //slicesize
		Vec2(0.f, 0.f), //step 
		1.f,	//only 1
		1);  //framecount


	m_vecTexture.push_back(new CTexture);
	m_vecTexture.back()->Load(L"../Image/Api/Text_Number/Number_new_2.bmp");
	GetAnimator()->CreateAnimation(L"UI_Number_State_03",  // 03
		m_vecTexture.back(),   //사이즈 129.34
		Vec2(8.f * 3, 0.f),
		Vec2(8.f, 11.f),  //slicesize
		Vec2(0.f, 0.f), //step 
		1.f,	//only 1
		1);  //framecount


	m_vecTexture.push_back(new CTexture);
	m_vecTexture.back()->Load(L"../Image/Api/Text_Number/Number_new_2.bmp");
	GetAnimator()->CreateAnimation(L"UI_Number_State_04",  // 04
		m_vecTexture.back(),   //사이즈 129.34
		Vec2(8.f * 4, 0.f),
		Vec2(8.f, 11.f),  //slicesize
		Vec2(0.f, 0.f), //step 
		1.f,	//only 1
		1);  //framecount

	m_vecTexture.push_back(new CTexture);
	m_vecTexture.back()->Load(L"../Image/Api/Text_Number/Number_new_2.bmp");
	GetAnimator()->CreateAnimation(L"UI_Number_State_05",  // 05
		m_vecTexture.back(),   //사이즈 129.34
		Vec2(8.f * 5, 0.f),
		Vec2(8.f, 11.f),  //slicesize
		Vec2(0.f, 0.f), //step 
		1.f,	//only 1
		1);  //framecount

	m_vecTexture.push_back(new CTexture);
	m_vecTexture.back()->Load(L"../Image/Api/Text_Number/Number_new_2.bmp");
	GetAnimator()->CreateAnimation(L"UI_Number_State_06",  // 06
		m_vecTexture.back(),   //사이즈 129.34
		Vec2(8.f * 6, 0.f),
		Vec2(8.f, 11.f),  //slicesize
		Vec2(0.f, 0.f), //step 
		1.f,	//only 1
		1);  //framecount

	m_vecTexture.push_back(new CTexture);
	m_vecTexture.back()->Load(L"../Image/Api/Text_Number/Number_new_2.bmp");
	GetAnimator()->CreateAnimation(L"UI_Number_State_07",  // 07
		m_vecTexture.back(),   //사이즈 129.34
		Vec2(8.f * 7, 0.f),
		Vec2(8.f, 11.f),  //slicesize
		Vec2(0.f, 0.f), //step 
		1.f,	//only 1
		1);  //framecount

	m_vecTexture.push_back(new CTexture);
	m_vecTexture.back()->Load(L"../Image/Api/Text_Number/Number_new_2.bmp");
	GetAnimator()->CreateAnimation(L"UI_Number_State_08",  // 08
		m_vecTexture.back(),   //사이즈 129.34
		Vec2(8.f * 8, 0.f),
		Vec2(8.f, 11.f),  //slicesize
		Vec2(0.f, 0.f), //step 
		1.f,	//only 1
		1);  //framecount

	m_vecTexture.push_back(new CTexture);
	m_vecTexture.back()->Load(L"../Image/Api/Text_Number/Number_new_2.bmp");
	GetAnimator()->CreateAnimation(L"UI_Number_State_09",  // 09
		m_vecTexture.back(),   //사이즈 129.34
		Vec2(8.f * 9, 0.f),     
		Vec2(8.f, 11.f),  //slicesize
		Vec2(0.f, 0.f), //step 
		1.f,	//only 1
		1);  //framecount





	m_eNumberState = NS_0;
	GetAnimator()->Play(L"UI_Number_State_00");

}



void UI_Number::Render(HDC hDC)
{

	GetAnimator()->GetCurAnimation()->Render(hDC);


}

int  UI_Number::Update()
{

	//__super::Update_Rect();
	GetAnimator()->Update();
	//m_eNumberState = CObjMgr::Get_Instance()->Get_Score();
	return OBJ_NOEVENT;
}


void UI_Number::Late_Update()
{
	switch (m_eNumberState)
	{

	case NS_0:

		GetAnimator()->Play(L"UI_Number_State_00");
		break;

	case NS_1:

		GetAnimator()->Play(L"UI_Number_State_01");
		break;

	case NS_2:

		GetAnimator()->Play(L"UI_Number_State_02");
		break;


	case NS_3:

		GetAnimator()->Play(L"UI_Number_State_03");
		break;

	case NS_4:

		GetAnimator()->Play(L"UI_Number_State_04");
		break;

	case NS_5:

		GetAnimator()->Play(L"UI_Number_State_05");
		break;

	case NS_6:

		GetAnimator()->Play(L"UI_Number_State_06");
		break;

	case NS_7:

		GetAnimator()->Play(L"UI_Number_State_07");
		break;

	case NS_8:

		GetAnimator()->Play(L"UI_Number_State_08");
		break;

	case NS_9:

		GetAnimator()->Play(L"UI_Number_State_09");
		break;


	}






	//Motion_Change();
	__super::Move_Frame();







}