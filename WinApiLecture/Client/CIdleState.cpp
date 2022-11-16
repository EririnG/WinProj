#include "pch.h"
#include "CIdleState.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CMonFactory.h"
#include "CMonster.h"

#include "CSceneMgr.h"

CIdleState::CIdleState()
	: CState(MON_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::update()
{
	// Player �� ��ġ üũ
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	// ������ ���� �ȿ� ������ ���� ���·� ��ȯ
	CMonster* pMonster = GetMonster();
	Vec2 vMonPos = pMonster->GetPos();
	
	Vec2 vDiff = vPlayerPos - vMonPos;
	float fLen = vDiff.Length();

	// �÷��̾ ������ �νĹ��� ������ ����
	if (fLen < pMonster->GetInfo().fRecogRange)
	{
		ChangeAIState(GetAI(), MON_STATE::TRACE);
	}

}

void CIdleState::Enter()
{
	

}

void CIdleState::Exit()
{
}