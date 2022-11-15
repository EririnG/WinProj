#include "pch.h"
#include "AI.h"

#include "CState.h"


AI::AI()
	: m_pCurState(nullptr)
	, m_pOwner(nullptr)
{
}

AI::~AI()
{
	Safe_Delete_Map(m_mapState);
}


void AI::update()
{
	m_pCurState->Enter();
}

void AI::AddState(CState* _pState)
{
	CState* pState = GetState(_pState->GetType());
	assert(!pState);
	m_mapState.insert(make_pair(_pState->GetType(), _pState));
	_pState->m_pAI = this;
}

CState* AI::GetState(MON_STATE _eState)
{
	map<MON_STATE, CState*>::iterator iter = m_mapState.find(_eState);
	if (iter == m_mapState.end())
		return nullptr;

	return iter->second;
}


