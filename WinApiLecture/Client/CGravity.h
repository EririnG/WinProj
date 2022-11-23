#pragma once

class CObject;

class CGravity
{
private:
	CObject*	m_pOwner;

	bool		m_bGround;

public:
	void SetGround(bool _b) { m_bGround = _b; }

public:
	void finalupdate();


public:
	CGravity();
	~CGravity();

	friend class CObject;
};

