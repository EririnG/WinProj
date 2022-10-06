#include "pch.h"
#include "CSLIME.h"
#include "CCollider.h"

#include "CResMgr.h"


CSLIME::CSLIME()
	: m_pTex(nullptr)
	
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"MonsterTex", L"texture\\monster.bmp");
	CreateCollider();

	GetCollider()->SetScale(Vec2(55.f, 55.f));
}

CSLIME::~CSLIME()
{
}
