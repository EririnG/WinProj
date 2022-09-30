#include "pch.h"
#include "CMissile.h"
#include "CScene.h"

#include "CTimeMgr.h"
#include "CSeneMgr.h"
#include "CKeyMgr.h"

CMissile::CMissile()
	: m_fTheta(PI/2.f)
{
}

CMissile::~CMissile()
{
}





void CMissile::update()
{
	Vec2 vPos = GetPos();

	vPos.x += 600.f * fDT * cosf(m_fTheta);
	vPos.y -= 600.f * fDT * sinf(m_fTheta);


	SetPos(vPos);

}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 VScale = GetScale();
	Ellipse(_dc, (int)(vPos.x - VScale.x / 2.f), (int)(vPos.y - VScale.y / 2.f)
		, (int)(vPos.x + VScale.x / 2.f), (int)(vPos.y + VScale.y / 2.f));
}

