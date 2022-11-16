#pragma once
#include "CObject.h"

class AI;
class CTexture;

struct tMonInfo
{	
	float		fSpeed;			// �ӵ�
	float		fHP;			// ü��
	float		fRecogRange;	// ���� ����
	float		fAttRange;		// ���� ����
	float		fAtt;			// ���ݷ�
	CTexture*	pTex;			// �ؽ���
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

