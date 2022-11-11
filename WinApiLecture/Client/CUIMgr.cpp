#include "pch.h"

#include "CUIMgr.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"

#include "CScene.h"
#include "CUI.h"

CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	// 1. FocusedUI 확인
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
		return;

	// 2. FocusedUI 내에서, 부모 UI 포함, 자식 UI들 중 실제 타겟팅 된 UI를 가져온다.
	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	bool bLbtnAway = KEY_AWAY(KEY::LBTN);
	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	
	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();

		if (bLbtnTap)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnAway)
		{
			pTargetUI->MouseLbtnUp();
			if (pTargetUI->m_bLbtnDown)
			{
				pTargetUI->MouseLbtnClicked();
			}

			// 왼쪽버튼 떼면, 눌렸던 체크를 다시 해제한다.
			pTargetUI->m_bLbtnDown = false;
		}
	}	
}


void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	if (m_pFocusedUI == _pUI || nullptr == m_pFocusedUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}
	m_pFocusedUI = _pUI;

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}
	if (0 != vecUI.size())
	{
		// 벡터 내에서 맨 뒤로 순번 교체
		vecUI.erase(iter);
		vecUI.push_back(m_pFocusedUI);
	}
	
}


CUI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// 기존 포커싱 UI를 받아두고 변경되었는지 확인한다.
	CUI* pFoCusedUI = m_pFocusedUI;

	if (!bLbtnTap)
	{
		return pFoCusedUI;
	}

	//왼쪽 버튼 tap 이 발생했다는 전제
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
	}
	// 이번에 Focus가 된 UI가 없다
	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFoCusedUI = (CUI*)*targetiter;

	// 벡터 내에서 맨 뒤로 순번 교체
	vecUI.erase(targetiter);

	vecUI.push_back(pFoCusedUI);

	return pFoCusedUI;
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	CUI* pTargetUI = nullptr;

	// 1. 부모 UI 포함, 모든 자식들을 검사 한다.
	static list<CUI*> queue;
	static vector<CUI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// 큐에서 데이터 하나 꺼내기
		CUI* pUI = queue.front();
		queue.pop_front();

		// 큐에서 꺼내온 UI가 TargetUI 인지 확인
		// 2. 타겟 UI 들 중, 더 우선순위가 높은 기준은 더 낮은 계층의 자식 UI
		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);

		}
		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}

	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}
	
	return pTargetUI;
}
