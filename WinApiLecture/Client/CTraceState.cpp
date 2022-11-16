#include "pch.h"
#include "CTraceState.h"

#include "CSceneMgr.h"
#include "CTimeMgr.h"

#include "CScene.h"
#include "CPlayer.h"
#include "CMonster.h"

CTraceState::CTraceState()
	:	CState(MON_STATE::TRACE)
{
}

CTraceState::~CTraceState()
{
}


void CTraceState::update()
{
	// Ÿ���� �� �÷��̾ �i�ư���.
	CPlayer* pPlayer= (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();
	Vec2 vMonPos = GetMonster()->GetPos();

	Vec2 vMonDir = vPlayerPos - vMonPos;
	vMonDir.Normalize();

	vMonPos += vMonDir * GetMonster()->GetInfo().fSpeed * fDT;

	GetMonster()->SetPos(vMonPos);
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}
