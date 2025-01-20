#pragma once

#define		WINCX		800
#define		WINCY		600
#define		VK_MAX		0xff
#define		MOVING_RADIAN 5.1f

#define			OBJ_NOEVENT		0
#define			OBJ_DEAD		1

#define MINIGAME_TOTAL 5
//윤동주
#define fDT CTimeMgr::CreateSingleTonInst()->GetfDT()

extern HWND		g_hWnd;

typedef struct tagInfo
{
	D3DXVECTOR3	vPos;		// 위치 벡터

	D3DXVECTOR3	 vDir;		// 방향 벡터
	D3DXVECTOR3  vLook;

	D3DXVECTOR3  vNormal;

	D3DXMATRIX	matWorld;	

}INFO;


enum CHANNELID
{
	SOUND_EFFECT,
	SOUND_BGM,
	SOUND_EFFECT_2,
	SOUND_EFFECT_3,
	MAXCHANNEL
};

enum ANIME_RESULT
{
	GS_IDLE,
	GS_NEXT,
	GS_WIN,
	GS_LOSE,
	GS_END
};
enum OBJID {
	OBJ_PLAYER,
	OBJ_PINGPONGBALL, //윤동주
	OBJ_MONSTER, 
	OBJ_BULLET,
	OBJ_MOUSE,
	OBJ_SHIELD, 
	OBJ_BOSS, 
	OBJ_UI,
	OBJ_LINE,

	OBJ_END
};

enum COLORID
{

	COLOR_008080, // 0 ,128,128
	COLOR_000000,
	COLOR_4D6DF3,
	COLOR_FFFFFF,  // white
	COLOR_C1DCFF, //  193, 220, 255 하늘색
	COLOR_108C29, //  16 140 41 이상한초록
	COLOR_8D9CB4,  //회색
	COLOR_F8F8A0,  //누런색
	COLOR_7E87A5,  //회색2
	COLOR_END
};

enum NUMBER_STATE
{
	NS_0,
	NS_1,
	NS_2,
	NS_3,
	NS_4,
	NS_5,
	NS_6,
	NS_7,
	NS_8,
	NS_9,
	NS_END
};

typedef struct tagFrame
{
	int		iFrameStart;	// 몇 번 인덱스부터 시작할 것인가
	int		iFrameEnd;
	int		iMotion;
	DWORD	dwSpeed;
	DWORD	dwTime;

}FRAME;

typedef struct tagPoint
{
	float	fX;
	float	fY;

	tagPoint() { ZeroMemory(this, sizeof(tagPoint)); }
	tagPoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

}LINEPOINT;

typedef struct tagLine
{
	LINEPOINT		tLPoint;
	LINEPOINT		tRPoint;

	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT& _tLPoint, LINEPOINT& _tRPoint)
		: tLPoint(_tLPoint), tRPoint(_tRPoint) {}

}LINE;


enum SCENEID {
	//SC_LOGO,
	//SC_MENU,
	//SC_EDIT,
	//SC_STAGE,
	//SC_MINIGAME_00,
	//SC_MINIGAME_01,
	//SC_MINIGAME_02,
	SC_TEST,
	SC_MINIGAME_00,
	SC_HOCKEY,
	SC_PINGPONG,

	SC_END
};

enum ROTATION_STATE //큐브 회전하는 
{
	RS_12, 
	RS_09,
	RS_06,
	RS_03,
	RS_END
};




static D3DXVECTOR3	Get_Mouse()
{
	POINT		pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	return D3DXVECTOR3((float)pt.x, (float)pt.y, 0.f);
}


enum DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	LU, // left up
	RU, // right up
	LD,
	RD,
	DIR_END
};

enum PIPE_STATE
{
	PS_00, // 1자
	PS_01, // ㄴ자
	PS_02, // 10자
	PS_03, // ㅗ자
	
	PS_END
};

enum PIPEBALL_STATE
{
	PB_00,
	PB_END
};

enum LINE_TYPE
{
	LT_PASS,
	LT_NONPASS,
	LT_END
};

#define SINGLE(type)\
private:\
	type();\
	~type();\
public:\
	static type* CreateSingleTonInst()\
	{\
		static type mgr;\
		return &mgr;\
	}\


class CStringCmp
{

public:
	CStringCmp(const TCHAR* pString) : m_pString(pString) {}

public:
	template<typename T>
	bool operator()(T& MyPair)
	{
		return !lstrcmp(m_pString, MyPair.first);
	}

private:
	const	TCHAR* m_pString;
};

struct Vec2
{
	float fX;
	float fY;

	Vec2(const Vec2& _v)
	{
		fX = _v.fX;
		fY = _v.fY;
	}

	Vec2(float _x, float _y)
	{
		fX = _x;
		fY = _y;
	}

	Vec2() {}


	Vec2 operator * (int _i)
	{
		return Vec2(fX * (float)_i, fY * (float)_i);
	}

	Vec2 operator + (Vec2 _v)
	{
		return Vec2(fX + _v.fX, fY + _v.fY);
	}

	Vec2 operator - (Vec2 _v)
	{
		return Vec2(fX - _v.fX, fY - _v.fY);
	}

};


template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}



template<typename T>
void Safe_Delete_Array(T& Temp)
{
	if (Temp)
	{
		delete[] Temp;
		Temp = nullptr;
	}
}


struct DeleteObj
{
	template<typename T>
	void		operator()(T& Obj)
	{
		if (Obj)
		{
			delete Obj;
			Obj = nullptr;
		}
	}
};

struct DeleteMap
{
	template<typename T>
	void		operator()(T& MyPair)
	{
		if (MyPair.second)
		{
			delete MyPair.second;
			MyPair.second = nullptr;
		}
	}
};
