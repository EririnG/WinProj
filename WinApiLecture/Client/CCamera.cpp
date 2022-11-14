#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CTexture.h"
#include "CResMgr.h"


CCamera::CCamera()
	:	m_pTarjetObj(nullptr)
	,	m_fTime(1.5f)
	,	m_fSpeed(0.f)
	,	m_fAccTime(0.5f)
	,	m_eEffect(CAM_EFFECT::NONE)
	,	m_pVeilTex(nullptr)
	,	m_fEffectDuration(0.f)
	,	m_fCurTime(0.f)
{
	
}

CCamera::~CCamera()
{
}


void CCamera::init()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"CameraVeil",(UINT)vResolution.x,(UINT)vResolution.y);
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

void CCamera::render(HDC _dc)
{
	if (CAM_EFFECT::NONE == m_eEffect)
		return;

	float fRatio = 0.f; // ����Ʈ ���� ����

	if (CAM_EFFECT::FADE_OUT == m_eEffect)
	{
		// �ð� �������� üũ
		m_fCurTime += fDT;
		
		// ���� �ð��� ����Ʈ �ִ� ���� �ð��� �Ѿ ���
		if (m_fEffectDuration < m_fCurTime)
		{
			//ȿ�� ����
			m_eEffect = CAM_EFFECT::NONE;
			return;
		}
		
		fRatio = m_fCurTime / m_fEffectDuration;
	}

	int iAlpha = int(255.f * fRatio);

	
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha;

	AlphaBlend(_dc, 0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		, m_pVeilTex->GetDC()
		, 0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height(), bf);
}

void CCamera::CalDiff()
{
	// ���� LookAt�� ���� Look�� ���̰��� �����ؼ� ������ LookAt�� ���Ѵ�.
	
	m_fAccTime += fDT;

	if (m_fTime <= m_fAccTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;

		if (!vLookDir.IsZero())
		{
			m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
		}

	}


	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;
}
