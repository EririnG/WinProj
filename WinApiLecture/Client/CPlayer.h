#pragma once
#include "CObject.h"

class CTexture;

class CPlayer:
	public CObject
{
private:
	CTexture* m_pTex;

public:
	virtual void update();
	virtual void render(HDC _dc);

private:
	void CreateMissile();

	CLONE(CPlayer);
public:
	CPlayer();
	~CPlayer();
};

