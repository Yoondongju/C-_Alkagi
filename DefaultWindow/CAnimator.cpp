#include "stdafx.h"
#include "CAnimator.h"

#include "CAnimation.h"
#include "CTexture.h"


CAnimator::CAnimator()
	: m_pOwner(nullptr)
	, m_pCurAnimation(nullptr)
{

}

CAnimator::~CAnimator()
{
	for (auto& iter : m_mapAnimation)
	{
		Safe_Delete<CAnimation*>(iter.second);
	}

	m_mapAnimation.clear();
}


void CAnimator::CreateAnimation(const TCHAR* _strKey,
	CTexture* _pTex, //넣을려는 텍스쳐
	Vec2 _vLT,  //시작위치
	Vec2 _vSliceSize,  //슬라이스사이즈
	Vec2 _vStep,  // 스탭
	float fDuration,  //무조건 1 
	UINT _iFrameCount) // FrameCount
{
	CAnimation* pAni;

	if (!FindAnimation(_strKey))
	{
		pAni = new CAnimation;
		pAni->SetKey(_strKey);
		pAni->m_Animator = this;
		pAni->Create(_pTex, _vLT, _vSliceSize, _vStep, fDuration, _iFrameCount);
		m_mapAnimation.insert(make_pair(_strKey, pAni));
	}

}


CAnimation* CAnimator::FindAnimation(const TCHAR* _strKey)
{
	auto iter = find_if(m_mapAnimation.begin(), m_mapAnimation.end(), CStringCmp(_strKey));

	if (iter == m_mapAnimation.end())
		return nullptr;

	return iter->second;

}

void CAnimator::Play(const TCHAR* _strKey)
{
	CAnimation* pAni = FindAnimation(_strKey);

	if (pAni)
		m_pCurAnimation = pAni;
}

void CAnimator::Update()
{
	if (m_pCurAnimation)
		m_pCurAnimation->Update();
}

void CAnimator::Render(HDC hDC)
{
	if (m_pCurAnimation)
		m_pCurAnimation->Render(hDC);
}
