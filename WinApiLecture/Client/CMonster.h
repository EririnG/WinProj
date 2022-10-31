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

	int		m_iHP;
	CTexture* m_pTex;


public:
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float _f) { m_fSpeed = _f; }
	void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
	void SetCenterPos(Vec2 _vPos) { m_vCenterpos = _vPos; }
	Vec2 GetCenterPos() { return m_vCenterpos; }

public:
	void CreateMissile();

public:
	virtual void OnCollisionEnter(CCollider* _pOther);

public:
	virtual void update();
	virtual void render(HDC _dc);
	CLONE(CMonster);
public:
	CMonster();
	~CMonster();

};

