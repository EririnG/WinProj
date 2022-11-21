#pragma once
class CMonster;

enum class MON_TYPE
{
	NORMAL,
	RANGE,
	MAGE,
};

class CMonFactory
{
public:
	static CMonster* CreateMonster(MON_TYPE _eType, Vec2 _vPos);





private:
	CMonFactory() {}
	~CMonFactory() {}
};

