#include "pch.h"
#include "CMonster.h"
#include "CMissile.h"
#include "CScene.h"

#include "CTimeMgr.h"
#include "CSeneMgr.h"

CMonster::CMonster()
	: m_vCenterpos(Vec2(0.f, 0.f))
	, m_fMaxDistance(50.f)
	, m_fSpeed(100.f)
	, m_iDir(1)
{
}


CMonster::~CMonster()
{
}

void CMonster::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y += GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;

	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(10.f, 10.f));
	pMissile->SetDir(false);

	CScene* pCurScene = CSeneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}

void CMonster::update()
{
	Vec2 vCurPos = GetPos();
	// ���� �������� �ð��� m_fSpeed ��ŭ �̵�
	vCurPos.x += fDT * m_fSpeed * m_iDir;

	// ��ȸ �Ÿ� ���ط��� �Ѿ���� Ȯ��
	float fDist = abs(m_vCenterpos.x-vCurPos.x) - m_fMaxDistance;

	if (0.f < fDist)
	{
		// ���� ����
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}

	SetPos(vCurPos);

	int call = CTimeMgr::GetInst()->GetCallCount();
	if (call == 2)
	{
		CreateMissile();
	}




}

void CMonster::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 VScale = GetScale();

	Rectangle(_dc, (int)(vPos.x - VScale.x / 2.f), (int)(vPos.y - VScale.y / 2.f)
		, (int)(vPos.x + VScale.x / 2.f), (int)(vPos.y + VScale.y / 2.f));
}
