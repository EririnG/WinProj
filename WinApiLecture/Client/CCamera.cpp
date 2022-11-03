#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

CCamera::CCamera()
	:	m_pTarjetObj(nullptr)
{}

CCamera::~CCamera()
{
}


void CCamera::update()
{
	if (m_pTarjetObj)
	{
		if (m_pTarjetObj->IsDead())
		{
			m_pTarjetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTarjetObj->GetPos();
		}
	}
	// ȭ�� �߾���ǥ�� ī�޶� LookAt ��ǥ���� ���̰� ���
	
	if (KEY_HOLD(KEY::UP))
		m_vLookAt.y -= 500.f * fDT;
	if (KEY_HOLD(KEY::DOWN))
		m_vLookAt.y += 500.f * fDT;
	if (KEY_HOLD(KEY::LEFT))
		m_vLookAt.x -= 500.f * fDT;
	if (KEY_HOLD(KEY::RIGHT))
		m_vLookAt.x += 500.f * fDT;

	CalDiff();
}

void CCamera::CalDiff()
{
	// ���� LookAt�� ���� Look�� ���̰��� �����ؼ� ������ LookAt�� ���Ѵ�.
	Vec2 vLookDir = m_vLookAt - m_vPrevLookAt; // ����
	
	m_vCurLookAt = m_vPrevLookAt+ vLookDir.Normalize() * 500.f * fDT;

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;
}
