#pragma once

#include "Obj.h"

class UI_Number;
class PipeBlock;
class PipeBall;


template<typename T>
class CAbstractFactory
{
public:
	static CObj*		Create()
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		//pObj->Set_Pos(_fX, _fY);

		return pObj;
	}




	static CObj* Create(float _fX, float _fY, float _fCX, float _fCY)
	{
		CObj* pObj = new T;
		pObj->Initialize();

		//pObj->Set_Pos(_fX, _fY);
		//pObj->Set_PosCXY(_fCX, _fCY);

		return pObj;
	}



	// UI_Number Only
	static CObj* Create(float _fX, float _fY, float _fCX, float _fCY, NUMBER_STATE _NS)
	{
		CObj* pObj = new T;
		pObj->Initialize();

		//pObj->Set_Pos(_fX, _fY);
		//pObj->Set_PosCXY(_fCX, _fCY);
	
		dynamic_cast<UI_Number*>(pObj)->Set_NumberState(_NS);
		return pObj;
	}

	// PIPEBLOCK Only
	static CObj* Create(float _fX, float _fY, float _fWidth, PIPE_STATE _PS, CObj* _player)
	{
		CObj* pObj = new T;
		dynamic_cast<PipeBlock*>(pObj)->Set_player(_player);
		dynamic_cast<PipeBlock*>(pObj)->Set_PipeState(_PS);

		//pObj->Initialize();

		pObj->Set_Pos(_fX, _fY);
		pObj->Set_width(_fWidth);
		dynamic_cast<PipeBlock*>(pObj)->Init_vPoint();
		return pObj;
	}

	static CObj* Create(float _fX, float _fY, float _fWidth, PIPEBALL_STATE _PB)
	{
		PipeBall* pObj = new T;
		pObj->Initialize();
		
		//dynamic_cast<PipeBall*>(pObj)->Setting_ball(_fX, _fY, _fWidth);


		return pObj;
	}




public:
	CAbstractFactory(){}
	~CAbstractFactory(){}
};

