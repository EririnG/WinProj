#pragma once

class CObject;

class CRigidBody
{
private:
	CObject*	m_pOwner;

	Vec2		m_vForce;		// ũ��, ����
	Vec2		m_vAccel;		// ���ӵ�
	Vec2		m_vVelocity;	// �ӵ� ( ũ�� : �ӷ�, ���� )
	float		m_fMass;		// ����

	// F = M * A;
	// V += A * DT;



public:
	void finalupdate();

public:
	void AddForce(Vec2 _vF) { m_vForce += _vF; }
	void SetMass(float _fMass) { m_fMass = _fMass; }

	float GetMass() { return m_fMass; }
public:
	void Move();


public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

