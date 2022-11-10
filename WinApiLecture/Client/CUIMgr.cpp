#include "pch.h"

#include "CUIMgr.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"

#include "CScene.h"
#include "CUI.h"

CUIMgr::CUIMgr()
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);


	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		CUI* pUI= (CUI*)vecUI[i];

		// �θ�
		pUI = GetTargetedUI(pUI);

		if (nullptr != pUI)
		{
			pUI->MouseOn();

			if (bLbtnTap)
			{
				pUI->MouseLbtnDown();
				pUI->m_bLbtnDown = true;
			}
			else if (bLbtnAway)
			{
				pUI->MouseLbtnUp();
				if (pUI->m_bLbtnDown)
				{
					pUI->MouseLbtnClicked();
				}

				// ���ʹ�ư ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
				pUI->m_bLbtnDown = false;
			}
		}
	}
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	CUI* pTargetUI = nullptr;

	// 1. �θ� UI ����, ��� �ڽĵ��� �˻� �Ѵ�.
	static list<CUI*> queue;
	static vector<CUI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// ť���� ������ �ϳ� ������
		CUI* pUI = queue.front();
		queue.pop_front();

		// ť���� ������ UI�� TargetUI ���� Ȯ��
		// 2. Ÿ�� UI �� ��, �� �켱������ ���� ������ �� ���� ������ �ڽ� UI
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
