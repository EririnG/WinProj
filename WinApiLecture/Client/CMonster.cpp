#include "pch.h"
#include "CMonster.h"
#include "CMissile.h"
#include "CScene.h"
#include "CCollider.h"
#include "CRes.h"
#include "AI.h"
#include "CRigidBody.h"
#include "CPlayer.h"

#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CResMgr.h"


CMonster::CMonster()
	: m_pTex(nullptr)
	, m_pAI(nullptr)
	, m_tInfo{}
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"MonsterTex", L"texture\\monster.bmp");
	
	
	CreateCollider();
	GetCollider()->SetScale(Vec2(55.f, 55.f));


}


CMonster::~CMonster()
{
	if (nullptr != m_pAI)
		delete m_pAI;
}


void CMonster::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y += GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;

	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(10.f, 10.f));
	pMissile->SetDir(3.f * PI / 2.f);

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Ground1" == _pOther->GetObj()->GetName() || L"Ground2" == _pOther->GetObj()->GetName())
	{
		Vec2 vPos = GetPos();
		if (vPos.y < pOtherObj->GetPos().y)
		{
			
		}
	}
}

void CMonster::update()
{
	if(nullptr != m_pAI)
		m_pAI->update();

	CRigidBody* pRigid = GetRigidBody();
	pRigid->AddForce(Vec2(-400.f, 0.f));





	// Player 의 위치 체크
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	// 몬스터의 범위 안에 들어오면 추적 상태로 전환
	CMonster* pMonster = this;
	Vec2 vMonPos = pMonster->GetPos();

	Vec2 vDiff = vPlayerPos - vMonPos;
	float fLen = vDiff.Length();

	if (fLen > 1280.f)
	{
 		DeleteObject(this);
	}


}

void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI;
	m_pAI->m_pOwner = this;
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
