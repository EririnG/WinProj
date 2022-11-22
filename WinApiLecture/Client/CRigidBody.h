#pragma once

class CObject;

class CRigidBody
{
private:
	CObject*	m_pOwner;

	Vec2		m_vForce;		// 크기, 방향
	Vec2		m_vAccel;		// 가속도
	Vec2		m_vVelocity;	// 속도 ( 크기 : 속력, 방향 )
	
	float		m_fMaxSpeed; // 최대 속력
	float		m_fMass;		// 질량


	float		m_fFricCoeff;	// 마찰 계수

	// F = M * A;
	// V += A * DT;



public:
	void finalupdate();

public:
	void AddForce(Vec2 _vF) { m_vForce += _vF; }
	void SetMass(float _fMass) { m_fMass = _fMass; }
	float GetMass() { return m_fMass; }

	void SetVelocity(Vec2 _v) { m_vVelocity = _v; }
	void AddVelocity(Vec2 _v) { m_vVelocity += _v; }
	void SetMaxVelocity(float _Speed) { m_fMaxSpeed = _Speed; }

public:
	void Move();


public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

