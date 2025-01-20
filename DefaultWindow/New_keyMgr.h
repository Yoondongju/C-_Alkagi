#pragma once

#include "Define.h"

enum class KEY_STATE
{
	NONE, // �������� �ȴ��Ȱ� ���ݵ� �ȴ��� ����
	TAP,  // ������ �ȴ��Ȱ� ���� ��������
	HOLD, // �������� ������ ���ݰ� ��������
	AWAY, // ������ ������ ���� �� ����

	END
};

struct tKeyInfo
{
	KEY_STATE eKeyState;
	bool	bPrePush;
};


enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q, W, E, R, T,
	Y, U, I, O, P,
	A, S, D, F, G,
	Z, X, C, V, B,

	LBUTTON,
	RBUTTON,

	ONE,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	END
};


class New_KeyMgr
{
	SINGLE(New_KeyMgr)


public:
	KEY_STATE GetKeyState(KEY _e) { return m_vecKey[(UINT)_e].eKeyState; }
	Vec2	GetMousePos() { return m_vCurMousePos; }


public:
	void init();
	void Update();


private:
	vector<tKeyInfo> m_vecKey;
	Vec2			 m_vCurMousePos;
};

