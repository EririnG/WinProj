#pragma once

class CObject;

class CCollider
{
private:
	CObject* m_pOwner;

	Vec2 m_vOffsetPos;

public:
	void finalupdate();

	friend class CObject;
};

