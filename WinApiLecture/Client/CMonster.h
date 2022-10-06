#pragma once
#include "CObject.h"

class CTexture;

class CMonster:
	public CObject
{
private:
	Vec2	m_vCenterpos;
	float	m_fSpeed;
	float	m_fMaxDistance;
	int     m_iDir;
	CTexture* m_pTex;


public:
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float _f) { m_fSpeed = _f; }
	void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
	void SetCenterPos(Vec2 _vPos) { m_vCenterpos = _vPos; }

public:
	void CreateMissile();

public:
	virtual void update();
	virtual void render(HDC _dc);
public:
	CMonster();
	~CMonster();

};

