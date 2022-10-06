#pragma once
#include "CScene.h"

class CTexture;

class CScene_Start:
	public CScene
{
private:
	CTexture* m_pTex;

public:
	virtual void Enter();
	virtual void Exit();


public:
	CScene_Start();
	~CScene_Start();

};

