// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// DefaultWindow.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"

// TODO: �ʿ��� �߰� �����
// �� ������ �ƴ� STDAFX.H���� �����մϴ�.
#include "CEventMgr.h"


void ChangeScene(SCENEID _Next)
{
	tEvent eve = {};
	eve.eEven = EVENT_TYPE::SCENE_CHANGE;
	eve.lParam = (DWORD_PTR)_Next;

	CEventMgr::CreateSingleTonInst()->AddEvent(eve);
}