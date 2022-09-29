#include "pch.h"
#include "CMissile.h"


#include "CTimeMgr.h"

CMissile::CMissile()
	: m_fDir(1.f)
{
}

CMissile::~CMissile()
{
}


void CMissile::update()
{
	Vec2 vPos = GetPos();

	vPos.y += 600.f * fDT * m_fDir;

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 VScale = GetScale();
	Ellipse(_dc, (int)(vPos.x - VScale.x / 2.f), (int)(vPos.y - VScale.y / 2.f)
		, (int)(vPos.x + VScale.x / 2.f), (int)(vPos.y + VScale.y / 2.f));
}
