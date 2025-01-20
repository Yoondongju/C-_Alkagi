#include "stdafx.h"
#include "CTimeMgr.h"


CTimeMgr::CTimeMgr()
	: m_llPrevCount{}
	, m_llCurCount{}
	, m_llFrequency{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount()
	, m_iFPS()
{

}


CTimeMgr::~CTimeMgr()
{


}

void CTimeMgr::init()
{
	// 초기화 할때 현재 카운트 (update 시점에서는 이전 카운트임)
	QueryPerformanceCounter(&m_llPrevCount);

	// 초당 카운트 횟수
	QueryPerformanceFrequency(&m_llFrequency);


}

void CTimeMgr::update()
{
	// 1 FPS ? ( update 시점에서는 현재 카운트 )
	QueryPerformanceCounter(&m_llCurCount);

	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;


	// 현재 카운트를 이전카운트에 넣음 (다음번 갱신을 위해)
	m_llPrevCount = m_llCurCount;


	

	if (m_dDT > (1. / 60.))
	{
		m_dDT = (1. / 60.);
	}



}