#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"


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

}

void CCamera::CalDiff()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vLookAt - vCenter;
}
