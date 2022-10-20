#include "pch.h"
#include "CMonster.h"
#include "CMissile.h"
#include "CScene.h"
#include "CCollider.h"
#include "CRes.h"

#include "CTimeMgr.h"
#include "CSeneMgr.h"
#include "CResMgr.h"


CMonster::CMonster()
	: m_vCenterpos(Vec2(0.f, 0.f))
	, m_fMaxDistance(50.f)
	, m_fSpeed(100.f)
	, m_iDir(1)
	, m_pTex(nullptr)
	, m_iHP(5)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"MonsterTex", L"texture\\monster.bmp");
	
	
	CreateCollider();
	GetCollider()->SetScale(Vec2(55.f, 55.f));
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
	pMissile->SetDir(3.f * PI / 2.f);

	CScene* pCurScene = CSeneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj =_pOther->GetObj();
	
	if (pOtherObj->GetName() == L"Missile_Player")
	{
		m_iHP -= 1;
		if (0 >= m_iHP)
		{
			DeleteObject(this);
		}
	}

	
}

void CMonster::update()
{
	Vec2 vCurPos = GetPos();
	// 진행 방향으로 시간당 m_fSpeed 만큼 이동
	vCurPos.x += fDT * m_fSpeed * m_iDir;

	// 배회 거리 기준량을 넘어섰는지 확인
	float fDist = abs(m_vCenterpos.x-vCurPos.x) - m_fMaxDistance;

	if (0.f < fDist)
	{
		// 방향 변경
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

	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();


	/*Rectangle(_dc, (int)(vPos.x - VScale.x / 2.f), (int)(vPos.y - VScale.y / 2.f)
		, (int)(vPos.x + VScale.x / 2.f), (int)(vPos.y + VScale.y / 2.f));*/

	TransparentBlt(_dc,
		int(vPos.x - (float)(iWidth / 2)),
		int(vPos.y - (float)(iHeight / 2)),
		iWidth,
		iHeight,
		m_pTex->GetDC(),
		0, 0, iWidth, iHeight, RGB(255, 0, 255));

	// 컴포넌트가 있는경우 렌더
	component_render(_dc);
}
