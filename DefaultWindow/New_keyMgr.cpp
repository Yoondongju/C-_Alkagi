#include "stdafx.h"
#include "New_KeyMgr.h"

int g_arrVK[(UINT)KEY::END] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	'Q','W','E','R','T',
	'Y','U','I','O','P',
	'A','S','D','F','G',
	'Z','X','C','V','B',

	VK_LBUTTON,
	VK_RBUTTON,
	'1',

	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE
};



New_KeyMgr::New_KeyMgr()
{

}

New_KeyMgr::~New_KeyMgr()
{

}


void New_KeyMgr::init()
{
	m_vecKey.reserve((UINT)KEY::END);

	for (int i = 0; i < (int)KEY::END; ++i)
	{
		m_vecKey.push_back({ KEY_STATE::NONE,false });
	}

}

void New_KeyMgr::Update()
{
	HWND hWnd = GetFocus();

	// 윈도우 포커싱 중일때
	if (hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY::END; i++)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)   // 해당 키가 눌렸다면?
			{
				if (m_vecKey[i].bPrePush) // 이전에도 눌림
				{
					m_vecKey[i].eKeyState = KEY_STATE::HOLD;
				}
				else // 이전엔 안눌렸다
				{
					m_vecKey[i].eKeyState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrePush = true;
			}

			else // 해당키가 안눌림
			{
				if (m_vecKey[i].bPrePush) // 이전엔 눌림
				{
					m_vecKey[i].eKeyState = KEY_STATE::AWAY;
				}
				else // 이전에도 안눌렸다
				{
					m_vecKey[i].eKeyState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrePush = false;
			}
		}

		// Mouse 위치 계산
		POINT ptPos = { };
		GetCursorPos(&ptPos); // 전체 윈도우의 좌표
		ScreenToClient(g_hWnd, &ptPos); // 내 클라이언트의 좌표

		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y); // 내가 누른곳의 x,y 좌표가담김

	}

	else // 포커싱 중 아닐때
	{
		for (int i = 0; i < (int)KEY::END; i++)
		{
			m_vecKey[i].bPrePush = false;


			if (m_vecKey[i].eKeyState == KEY_STATE::TAP || m_vecKey[i].eKeyState == KEY_STATE::HOLD)
			{
				m_vecKey[i].eKeyState = KEY_STATE::AWAY;
			}

			else if (m_vecKey[i].eKeyState == KEY_STATE::AWAY)
			{
				m_vecKey[i].eKeyState = KEY_STATE::NONE;
			}

		}
	}


}
