#include "pch.h"
#include "CScene_01.h"


#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCamera.h"
#include "AI.h"
#include "CState.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CRigidBody.h"
#include "SelectGDI.h"
#include "CGround.h"
#include "CSound.h"

#include "CCore.h"

#include "CPathMgr.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CTimeMgr.h"

CScene_01::CScene_01()
	: m_pTex(nullptr)
	, m_bUseForce(false)
	, m_fForceRadius(500.f)
	, m_fCurRadius(0.f)
	, m_fForce(500.f)
{
}

CScene_01::~CScene_01()
{
}

void CScene_01::update()
{
	if (KEY_HOLD(KEY::LBTN))
	{
		m_bUseForce = true;
		CreateForce();
	}
	else
	{
		m_bUseForce = false;
	}

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		const vector<CObject*>& vecObj = GetGroupObject((GROUP_TYPE)i);

		for (size_t j = 0; j < vecObj.size(); ++j)
		{
			if (!vecObj[j]->IsDead())
			{
				if (m_bUseForce && vecObj[j]->GetRigidBody())
				{
					Vec2 vDiff = vecObj[j]->GetPos() - m_vForcePos;
					float fLen = vDiff.Length();
					if (fLen < m_fForceRadius)
					{
						float fRatio = 1.f - (fLen / m_fForceRadius);
						float fForce = m_fForce * fRatio;


						vecObj[j]->GetRigidBody()->AddForce(vDiff.Normalize() * fForce);
					}
				}
				vecObj[j]->update();
			}
		}
	}
}

void CScene_01::render(HDC _dc)
{
	CScene::render(_dc);
	if (!m_bUseForce)
		return;
	SelectGDI gdi1(_dc, BRUSH_TYPE::HOLLOW);
	SelectGDI gdi2(_dc, PEN_TYPE::GREEN);

	m_fCurRadius += m_fForceRadius * 3.f * fDT;
	if (m_fCurRadius > m_fForceRadius)
	{
		m_fCurRadius = 0.f;
	}

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vForcePos);

	Ellipse(_dc
		, (int)(vRenderPos.x - m_fCurRadius)
		, (int)(vRenderPos.y - m_fCurRadius)
		, (int)(vRenderPos.x + m_fCurRadius)
		, (int)(vRenderPos.y + m_fCurRadius));
}

void CScene_01::Enter()
{
	// Object 추가
	CObject* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(280.f, 450.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	//CObject* pOtherPlayer = pObj->Clone();
	//pOtherPlayer->SetPos(Vec2(740.f, 640.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	//CCamera::GetInst()->SetTarget(pObj);

	 //몬스터 배치
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	//CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f, 300.f));
	//AddObject(pMon, GROUP_TYPE::MONSTER);


	// 땅 물체 배치
	CObject* pGround = new CGround;
	pGround->SetName(L"Ground1");
	pGround->SetPos(Vec2(640.f, 584.f));
	pGround->SetScale(Vec2(1500.f, 60.f));
	AddObject(pGround, GROUP_TYPE::GROUND);

	CObject* pUpGround = new CGround;
	pUpGround->SetName(L"Ground2");
	pUpGround->SetPos(Vec2(640.f, 300.f));
	pUpGround->SetScale(Vec2(1500.f, 60.f));
	AddObject(pUpGround, GROUP_TYPE::GROUND);

	// 충돌 지정
	// Player 그룹과 Monster 그룹 간의 충돌체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);

	// Camera Look 지정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	// Camera 효과 지정
	CCamera::GetInst()->FadeOut(1.0f);
	CCamera::GetInst()->FadeIn(1.0f);


	CResMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\FloralLife.wav");
	CSound* pScene01_Sound = CResMgr::GetInst()->FindSound(L"BGM_01");
	pScene01_Sound->Play();
	pScene01_Sound->SetVolume(10.f);


	start();
}

void CScene_01::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}


void CScene_01::CreateForce()
{
	m_vForcePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
}


