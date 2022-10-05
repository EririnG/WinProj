#include "pch.h"
#include "CPlayer.h"
#include "CScene.h"

#include "CSeneMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"

#include "CMissile.h"
#include "CTexture.h"

CPlayer::CPlayer()
	: m_pTex(nullptr)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\player.bmp");
	CreateCollider();
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

	int(vPos.x - (float)(iWidth / 2));
	int(vPos.y - (float)(iHeight / 2));

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

	/*Vec2 vPos = GetPos();
	Vec2 VScale = GetScale();

	Rectangle(_dc, (int)(vPos.x - VScale.x / 2.f), (int)(vPos.y - VScale.y / 2.f)
		, (int)(vPos.x + VScale.x / 2.f), (int)(vPos.y + VScale.y / 2.f));*/

}


void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;

	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(10.f, 10.f));
	pMissile->SetDir(Vec2(-1.f, -7.f));

	CScene* pCurScene = CSeneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}
