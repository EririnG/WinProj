#include "pch.h"
#include "CMissile.h"
#include "CScene.h"

#include "CTimeMgr.h"
#include "CSeneMgr.h"
#include "CKeyMgr.h"

CMissile::CMissile()
	: m_fTheta(PI/2.f)
	, m_vDir(Vec2(1.f,1.f))
{
	m_vDir.Normalize();
	CreateCollider();
}


CMissile::~CMissile()
{
}





void CMissile::update()
{
	Vec2 vPos = GetPos();

	vPos.x += 600.f * fDT * m_vDir.x;
	vPos.y += 600.f * fDT * m_vDir.y;


	SetPos(vPos);

}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 VScale = GetScale();
	Ellipse(_dc, (int)(vPos.x - VScale.x / 2.f), (int)(vPos.y - VScale.y / 2.f)
		, (int)(vPos.x + VScale.x / 2.f), (int)(vPos.y + VScale.y / 2.f));
}

