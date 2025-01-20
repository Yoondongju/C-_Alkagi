#pragma once

#include "Obj.h"

#define PLAYER_SIZE 20.f
const float fMaxpull = sqrt((WINCX / 2.f * WINCX / 2.f) + (WINCY / 2.f * WINCY / 2.f));


class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();



public:
	virtual void Initialize() override;
	virtual void Initialize(D3DXVECTOR3 _v, D3DXVECTOR3 _Dir = { 0.f,0.f,0.f });

	virtual int  Update() override;
	virtual void Late_Update()override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	void RenderChargingUI(HDC hDC);

private:
	void		Key_Input();
	void		Move();
	void		CollisionMove();



public:
	void	SetPlayerTurn(bool _b) { m_bPlayerTurn = _b; }
	bool	IsPlayerTurn() { return m_bPlayerTurn; }


	float       GetGauge() { return m_fPullGauge; }
	static BYTE	GetCount() { return m_iCount; }

private:
	D3DXVECTOR3 m_vSize;

	D3DXVECTOR3 m_vPoint[4];
	D3DXVECTOR3 m_vOriginPoint[4];

	D3DXVECTOR3	m_vPosinPoint;
	D3DXVECTOR3	m_vOriginPosinPoint;

	D3DXVECTOR3	m_vPosinLeftPoint;
	D3DXVECTOR3	m_vOriginPosinLeftPoint;

	D3DXVECTOR3	m_vPosinRightPoint;
	D3DXVECTOR3	m_vOriginPosinRightPoint;


	float			m_fAngle;
	float			m_fPullGauge;
	float			m_fFrictionforce;

	bool			m_bReadyPull;
	bool			m_bStartMove;

	bool			m_bCopying;
	static bool		m_bPlayerTurn;
	static BYTE		m_iCount;


	bool			m_bCopyInstance;
};

// 행렬을 사용하는 이유 : 객체의 여러 상태를 표현하기 위함

// 1. 크기 변환 
// 2. 회전 변환
// 3. 위치 변환

// 4 x 4 -> 4행 4열
// 행과 열의 숫자가 일치하는 행렬 -> 정방 행렬

// Local Vtx * World Matrix	-> World Vtx

// 행렬의 곱셈 법칙

//1. 앞의 행렬의 열과 뒤의 행렬의 행의 값이 일치해야 곱셈이 성립
//
//(1 * 3) * (4 * 4)		(x)
//(1 * 4) * (4 * 4)		(o)
//
//2. 앞의 행렬의 행의 값과 뒤의 행렬의 열의 값으로 결과 값이 생성됨
//
//(1 * 4) * (4 * 4)	-> (1 * 4)
//
//3. 행렬의 곱셈은 교환 법칙이 항상 성립하지는 않는다.
//
//// A * B == B * A
//
//1 2		+  5 6    ->  6  8
//3 4		   7 8		  10 12	
//
//1 2		*  5 6    ->  1 * 5 + 2 * 7		1 * 6 + 2 * 8	->  19	22
//3 4		   7 8		  3 * 5 + 4 * 7		3 * 6 + 4 * 8 		43	50
//
//5 6		*  1 2	  ->  5 * 1 + 6 * 3		5 * 2 + 6 * 4	->	23	34 
//7 8	       3 4		  7 * 1 + 8 * 3		7 * 2 + 8 * 4		31	46		
//
//⁂ 월드 행렬 = 크(기 행렬) * 자(전 행렬) * 이(동 행렬) * 공(전 행렬) * 부(모 행렬)
//
//4. 어떤 행렬과 그 행렬의 역행렬을 곱하면 항등 행렬이 된다.
//
//항등 행렬(I) : 어떤 행렬과 연산을 해도 반드시 원본 값 그대로가 되는 행렬, 행렬의 초기화 상태라고도 말함
//
//1	0	0	0
//0	1	0	0
//0	0	1	0
//0	0	0	1	
//
//A * A^-1 = I -> A / A = 1

// dx는 왜 4 * 4 행렬을 제공하는가?
// 
// 							_11,	_12,	_13,	_14
// 	X, Y, Z, W			*	_21,	_22,	_23,	_24		-> X`, Y`, Z`, W`
// 							_31,	_32,	_33,	_34
// 							_41,	_42,	_43,	_44
// 
// W값이 0인 경우 -> 방향 벡터
// W값이 1인 경우 -> 위치 벡터
// 
// 크기(배율) : _11(X), _22(Y), _33(Z)
// 위치(좌표) : _41(X), _42(Y), _43(Z)
// X축 회전   : _22(cos), _23(sin), _32(-sin), _33(cos)
// Y축 회전   : _11(cos), _13(-sin), _31(sin), _33(cos)
// Z축 회전   : _11(cos), _12(sin), _21(-sin), _22(cos)