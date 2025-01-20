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

	// ������ ��Ŀ�� ���϶�
	if (hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY::END; i++)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)   // �ش� Ű�� ���ȴٸ�?
			{
				if (m_vecKey[i].bPrePush) // �������� ����
				{
					m_vecKey[i].eKeyState = KEY_STATE::HOLD;
				}
				else // ������ �ȴ��ȴ�
				{
					m_vecKey[i].eKeyState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrePush = true;
			}

			else // �ش�Ű�� �ȴ���
			{
				if (m_vecKey[i].bPrePush) // ������ ����
				{
					m_vecKey[i].eKeyState = KEY_STATE::AWAY;
				}
				else // �������� �ȴ��ȴ�
				{
					m_vecKey[i].eKeyState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrePush = false;
			}
		}

		// Mouse ��ġ ���
		POINT ptPos = { };
		GetCursorPos(&ptPos); // ��ü �������� ��ǥ
		ScreenToClient(g_hWnd, &ptPos); // �� Ŭ���̾�Ʈ�� ��ǥ

		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y); // ���� �������� x,y ��ǥ�����

	}

	else // ��Ŀ�� �� �ƴҶ�
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
