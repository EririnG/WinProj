#include "pch.h"
#include "CIdleState.h"


CIdleState::CIdleState()
	: CState(MON_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::update()
{
	// Player 의 위치 체크


	// 몬스터의 범위 안에 들어오면 추적 상태로 전환
	
}

void CIdleState::Enter()
{
	

}

void CIdleState::Exit()
{
}