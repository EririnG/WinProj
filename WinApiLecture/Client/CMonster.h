#pragma once
#include "CObject.h"

class AI;
class CTexture;

struct tMonInfo
{	
	float		fSpeed;			// 속도
	float		fHP;			// 체력
	float		fRecogRange;	// 인지 범위
	float		fAttRange;		// 공격 범위
	float		fAtt;			// 공격력
	CTexture*	pTex;			// 텍스쳐
};





class CMonster:
	public CObject
{
private:
	tMonInfo	m_tInfo;
	AI*			m_pAI;

	CTexture* m_pTex;


public:
	float GetSpeed() { return m_tInfo.fSpeed; }
	void SetSpeed(float _f) { m_tInfo.fSpeed = _f; }
	void SetAI(AI* _AI);
	const tMonInfo& GetInfo() { return m_tInfo; }

private:
	void SetMonInfo(const tMonInfo& _info) { m_tInfo = _info; }


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

	friend class CMonFactory;
};

