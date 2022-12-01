#pragma once
#include "CScene.h"
class CUI;

class CScene_Start:
	public CScene
{
private:
	CUI* m_pUI;

public:
	virtual void Enter();
	virtual void Exit();
	virtual void update();


public:
	CScene_Start();
	~CScene_Start();
};

