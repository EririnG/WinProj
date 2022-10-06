#include "pch.h"
#include "CMissile.h"
#include "CScene.h"
#include "CCollider.h"


#include "CTimeMgr.h"
#include "CSeneMgr.h"
#include "CKeyMgr.h"
#include "CResMgr.h"


CMissile::CMissile()
	: m_fTheta(PI/2.f)
	, m_vDir(Vec2(1.f,1.f))
	, m_pTex(nullptr)
{
	m_vDir.Normalize();
	m_pTex = CResMgr::GetInst()->LoadTexture(L"MissileTex", L"texture\\missile.bmp");
	CreateCollider();
	GetCollider()->SetScale(Vec2(10.f, 10.f));
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
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();
	Vec2 VScale = GetScale();

	TransparentBlt(_dc,
		int(vPos.x - (float)(iWidth / 2)),
		int(vPos.y - (float)(iHeight / 2)),
		iWidth,
		iHeight,
		m_pTex->GetDC(),
		0, 0, iWidth, iHeight, RGB(255, 0, 255));

	// 컴포넌트가 있는경우 렌더
	component_render(_dc);
	/*
	Ellipse(_dc, (int)(vPos.x - VScale.x / 2.f), (int)(vPos.y - VScale.y / 2.f)
		, (int)(vPos.x + VScale.x / 2.f), (int)(vPos.y + VScale.y / 2.f));*/
}

