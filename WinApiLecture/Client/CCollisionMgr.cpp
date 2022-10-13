#include "pch.h"

#include "CCollisionMgr.h"
#include "CSeneMgr.h"

#include "CScene.h"
#include "CObject.h"

CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{}


void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}

	}
}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSeneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// �浹ü�� �������� ���� ���
		if (nullptr == vecLeft[i]->GetCollider())
			continue;




		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// �浹ü�� ���ų�, �ڱ� �ڽŰ��� �浹�� ���
			if (nullptr == vecRight[j]->GetCollider() || vecLeft[i]==vecRight[j])
				continue;

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRighttCol = vecLeft[j]->GetCollider();

			// �� �浹ü ���� ���̵� ����
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRighttCol->GetID();

			map < ULONGLONG, bool>::iterator iter = m_mapColInfo.find(ID.ID);

			//�浹 ������ �� ��� ������ ��� ���( �浹���� �ʾҴٷ� ��� )
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}


			if (IsCollision(pLeftCol, pRighttCol))
			{
				//���� �浹 ���̴�.
				if (iter->second)
				{
					// �������� �浹 �ϰ� �־���.
					pLeftCol->OnCollision(pRighttCol);
					pRighttCol->OnCollision(pLeftCol);
				}
				else
				{
					// �������� �浹���� �ʾҴ�.
					// �浹�� ���� �M!!
					pLeftCol->OnCollisionEnter(pRighttCol);
					pRighttCol->OnCollisionEnter(pLeftCol);
					iter->second = true;
				}
				
			}
			else
			{
				// ���� �浹�ϰ� ���� �ʴ�.
				if (iter->second)
				{
					// �浹���� �� ��� ����
					pLeftCol->OnCollisionExit(pRighttCol);
					pRighttCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}

		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	return false;
}


void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// �� ���� ���� �׷� Ÿ���� ������,
	// ū ���� ��(��Ʈ) �� ���

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		UINT iRow = (UINT)_eRight;
		UINT iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
	
}




