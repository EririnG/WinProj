#include "pch.h"
#include "CPlayer.h"
#include "CScene.h"

#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"

#include "CMissile.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"


CPlayer::CPlayer()
	: m_pTex(nullptr)
{
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link_0.bmp");
	
	
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(1.f, 0.f));
	GetCollider()->SetScale(Vec2(10.f, 40.f));

	// Texture 로딩하기
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link_0.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_DOWN", m_pTex, Vec2(0.f, 260.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f),1.f, 10);
}

CPlayer::~CPlayer()
{

}


void CPlayer::update()
{
	Vec2 vPos = GetPos();
	

	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * fDT;
	}

	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT;
	}

	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDT;
	}

	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDT;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos);
}

void CPlayer::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();

	//int(vPos.x - (float)(iWidth / 2));
	//int(vPos.y - (float)(iHeight / 2));

	/*BitBlt(_dc,
		int(vPos.x - (float)(iWidth / 2)),
		int(vPos.y - (float)(iHeight / 2)),
		iWidth,
		iHeight,
		m_pTex->GetDC(),
		0, 0, SRCCOPY);*/

	TransparentBlt(_dc,
		int(vPos.x - (float)(iWidth / 2)),
		int(vPos.y - (float)(iHeight / 2)),
		iWidth,
		iHeight,
		m_pTex->GetDC(),
		0, 0, iWidth, iHeight,RGB(255,0,255) );

	// 컴포넌트가 있는경우 렌더
	component_render(_dc);

}


void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(10.f, 10.f));
	pMissile->SetDir(Vec2(0.f, -7.f));

	CreateObject(pMissile,GROUP_TYPE::PROJ_PLAYER);
}
