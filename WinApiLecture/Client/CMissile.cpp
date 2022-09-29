#include "pch.h"
#include "CMissile.h"
#include "CScene.h"

#include "CTimeMgr.h"
#include "CSeneMgr.h"
#include "CKeyMgr.h"

CMissile::CMissile()
	: m_fDir(1.f)
{
}

CMissile::~CMissile()
{
}





void CMissile::update()
{
	Vec2 vPos_Center = GetPos();
	Vec2 vPos_Right = GetPos();
	Vec2 vPos_Left = GetPos();

	vPos_Center.y += 600.f * fDT * m_fDir;
	vPos_Right.y += 600.f * fDT * m_fDir;
	vPos_Right.x += 300.f * fDT * m_fDir;
	vPos_Left.y += 600.f * fDT * m_fDir;
	vPos_Left.y -= 300.f * fDT * m_fDir;

	SetPos(vPos_Center);
	SetPos(vPos_Right);
	SetPos(vPos_Left);
}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 VScale = GetScale();
	Ellipse(_dc, (int)(vPos.x - VScale.x / 2.f), (int)(vPos.y - VScale.y / 2.f)
		, (int)(vPos.x + VScale.x / 2.f), (int)(vPos.y + VScale.y / 2.f));
}

