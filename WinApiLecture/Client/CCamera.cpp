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
	// 화면 중앙좌표와 카메라 LookAt 좌표간의 차이값 계산

}

void CCamera::CalDiff()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vLookAt - vCenter;
}
