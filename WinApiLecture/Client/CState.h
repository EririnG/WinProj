#pragma once

class AI;

class CState
{
private:
	AI*			m_pAI;
	MON_STATE	m_eState;


public:
	AI* GetAI() { return m_pAI; }
	MON_STATE GetType() {return m_eState;}

public:
	virtual void update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;


public:
	CState(MON_STATE _eState);
	virtual ~CState();

	friend class AI;
};

