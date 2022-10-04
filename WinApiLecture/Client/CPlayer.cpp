#include "pch.h"
#include "CPlayer.h"
#include "CScene.h"

#include "CSeneMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"

#include "CMissile.h"
#include "CTexture.h"

CPlayer::CPlayer()
	: m_pTex(nullptr)
{
	//texture ·Îµù
	/*CTexture* m_pTex = new CTexture;

	wstring strFilepath = CPathMgr::GetInst()->GetContentPath();
	strFilepath += L"texture\\player.bmp";
	m_pTex->Load(strFilepath);*/

}

CPlayer::~CPlayer()
{
	if (nullptr != m_pTex)
		delete m_pTex;
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

	BitBlt(_dc,
		int(vPos.x - (float)(iWidth / 2)),
		int(vPos.y - (float)(iHeight / 2)),
		iHeight,
		iWidth,
		m_pTex->GetDC(),
		0, 0, SRCCOPY);

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

void CPlayer::CreateMissile2()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	CMissile* pCEN_Missile = new CMissile;
	CMissile* pRIGHT_Missile = new CMissile;
	CMissile* pLEFT_Missile = new CMissile;

	pCEN_Missile->SetPos(vMissilePos);
	pCEN_Missile->SetScale(Vec2(10.f, 10.f));
	pCEN_Missile->SetDir(true);
	pRIGHT_Missile->SetPos(vMissilePos);
	pRIGHT_Missile->SetScale(Vec2(10.f, 10.f));
	pRIGHT_Missile->SetDir(true);
	pLEFT_Missile->SetPos(vMissilePos);
	pLEFT_Missile->SetScale(Vec2(10.f, 10.f));
	pLEFT_Missile->SetDir(true);

	CScene* pCurScene = CSeneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pCEN_Missile, GROUP_TYPE::DEFAULT);
	pCurScene->AddObject(pRIGHT_Missile, GROUP_TYPE::DEFAULT);
	pCurScene->AddObject(pLEFT_Missile, GROUP_TYPE::DEFAULT);

}


