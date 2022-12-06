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
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CGravity.h"
#include "CSound.h"

CPlayer::CPlayer()
	: m_pTex(nullptr)
	, m_pSound(nullptr)
	, m_eCurState(PLAYER_STATE::IDLE)
	, m_ePrevState(PLAYER_STATE::WALK)
	, m_iDir(1)
	, m_iPrevDir(1)
{
	//_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link_0.bmp");
	
	CResMgr::GetInst()->LoadSound(L"Jump", L"sound\\Player_Jump.wav");

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 5.f));
	GetCollider()->SetScale(Vec2(20.f, 55.f));

	CreateRigidBody();

	// Texture 로딩하기
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link_0.bmp");
	CreateAnimator();
	
	GetAnimator()->LoadAnimation(L"animation\\player_idle_left.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_idle_right.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_walk_left.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_walk_right.anim");


	//GetAnimator()->CreateAnimation(L"IDLE_DOWN", pTex, Vec2(0.f, 0.f), Vec2(60, 65), Vec2(60.f, 0.f), 0.1f, 3);
	//GetAnimator()->CreateAnimation(L"IDLE_LEFT", pTex, Vec2(0.f, 65.f), Vec2(60, 65), Vec2(60.f, 0.f), 0.1f, 3);
	//GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pTex, Vec2(0.f, 195.f), Vec2(60, 65), Vec2(60.f, 0.f), 0.1f, 3);
	//GetAnimator()->CreateAnimation(L"IDLE_UP", pTex, Vec2(0.f, 130.f), Vec2(60, 65), Vec2(60.f, 0.f), 0.1f, 1);

	//GetAnimator()->CreateAnimation(L"WALK_LEFT", pTex, Vec2(0.f, 325.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);
	//GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f, 455.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);
	//GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 260.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f),0.1f, 10);
	//GetAnimator()->CreateAnimation(L"WALK_UP", pTex, Vec2(0.f, 390.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);

	//GetAnimator()->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\player_idle_left.anim");
	//GetAnimator()->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\player_idle_right.anim");
	//GetAnimator()->FindAnimation(L"WALK_LEFT")->Save(L"animation\\player_walk_left.anim");
	//GetAnimator()->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\player_walk_right.anim");

	GetAnimator()->Play(L"WALK_RIGHT", true);


	CreateGravity();
	
}

CPlayer::~CPlayer()
{

}


void CPlayer::update()
{

	update_move();

	update_state();
	
	update_animation();





	if (KEY_TAP(KEY::ENTER))
	{
		SetPos(Vec2(640.f, 584.f));
	}


	GetAnimator()->update();
	
	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;
	
}

void CPlayer::render(HDC _dc)
{
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

void CPlayer::update_state()
{
	//if (KEY_TAP(KEY::W))
	//{
	//	
	//}
	//if (KEY_TAP(KEY::S))
	//{
	//	
	//}


	//if (KEY_HOLD(KEY::A))
	//{
	//	//m_vDir = Vec2(0.f, 0.f);
	//	//m_vDir.x = -1;
	//	m_iDir = -1;
	//	if(PLAYER_STATE::JUMP != m_eCurState)
	//		m_eCurState = PLAYER_STATE::WALK;
	//}
	//if (KEY_HOLD(KEY::D))
	//{
	//	//m_vDir = Vec2(0.f, 0.f);
	//	//m_vDir.x = 1;
	//	m_iDir = 1;
	//	if (PLAYER_STATE::JUMP != m_eCurState)
	//		m_eCurState = PLAYER_STATE::WALK;
	//}

	if (0.f == GetRigidBody()->GetSpeed() && PLAYER_STATE::JUMP != m_eCurState)
	{
		m_eCurState = PLAYER_STATE::WALK;
	}

	if (KEY_TAP(KEY::SPACE))
	{

		m_eCurState = PLAYER_STATE::JUMP;

		if(GetRigidBody())
		{
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -300.f));
		}
		m_pSound = CResMgr::GetInst()->FindSound(L"Jump");
		m_pSound->Play(false);
		m_pSound->SetVolume(10.f);
	}


}

void CPlayer::update_move()
{
	CRigidBody* pRigid = GetRigidBody();

	//if (KEY_HOLD(KEY::W))
	//{
	//	pRigid->AddForce(Vec2(0.f, -200.f));

	//}
	//if (KEY_HOLD(KEY::S))
	//{
	//	pRigid->AddForce(Vec2(0.f, 200.f));
	//}
	//if (KEY_HOLD(KEY::A))
	//{
	//	pRigid->AddForce(Vec2(-200.f, 0.f));
	//}

	//if (KEY_HOLD(KEY::D))
	//{
	//	pRigid->AddForce(Vec2(200.f, 0.f));
	//}

	if (KEY_TAP(KEY::W))
	{
		if (m_eCurState != PLAYER_STATE::JUMP)
		{
			SetPos(Vec2(280.f, 300.f));
		}
		//pRigid->AddVelocity(Vec2(0.f, -100.f));
	}
	if (KEY_TAP(KEY::S))
	{
		if (m_eCurState != PLAYER_STATE::JUMP)
		{
			SetPos(Vec2(280.f, 584.f));
		}
		//pRigid->AddVelocity(Vec2(0.f, 100.f));ws
	}
	//if (KEY_TAP(KEY::A))
	//{
	//	pRigid->SetVelocity(Vec2(-100.f, pRigid->GetVelocity().y));
	//}
	//if (KEY_TAP(KEY::D))
	//{
	//	pRigid->SetVelocity(Vec2(100.f, pRigid->GetVelocity().y));
	//}

}

void CPlayer::update_animation()
{
	if (m_eCurState == m_ePrevState && m_iPrevDir == m_iDir)
		return;

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		//if (1 == m_vDir.y)
		//	GetAnimator()->Play(L"IDLE_DOWN", true);
		//else if(-1 == m_vDir.x)
		//	GetAnimator()->Play(L"IDLE_LEFT", true);
		//else if (1 == m_vDir.x )
		//	GetAnimator()->Play(L"IDLE_RIGHT", true);
		//else if(-1 == m_vDir.y)
		//	GetAnimator()->Play(L"IDLE_UP", true);
		if (1 == m_iDir)
			GetAnimator()->Play(L"WALK_RIGHT", true);
		else if (-1 == m_iDir)
			GetAnimator()->Play(L"IDLE_LEFT", true);

	}

		break;
	case PLAYER_STATE::WALK:
	{
		//if (1 == m_vDir.y)
		//	GetAnimator()->Play(L"WALK_DOWN", true);
		//else if (-1 == m_vDir.x)
		//	GetAnimator()->Play(L"WALK_LEFT", true);
		//else if (1 == m_vDir.x)
		//	GetAnimator()->Play(L"WALK_RIGHT", true);
		//else if (-1 == m_vDir.y)
		//	GetAnimator()->Play(L"WALK_UP", true);
		if (1 == m_iDir)
			GetAnimator()->Play(L"WALK_RIGHT", true);
		else if (-1 == m_iDir)
			GetAnimator()->Play(L"WALK_LEFT", true);

	}
		break;
	case PLAYER_STATE::JUMP:
	{
		if (1 == m_iDir)
			GetAnimator()->Play(L"WALK_RIGHT", true);
		else if (-1 == m_iDir)
			GetAnimator()->Play(L"WALK_LEFT", true);
	}

		break;
	case PLAYER_STATE::ATTACK:

		break;
	case PLAYER_STATE::DEAD:

		break;
	default:
		break;
	}
}

void CPlayer::update_gravity()
{
	GetRigidBody()->AddForce(Vec2(0.f,500.f));
}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Ground1" == _pOther->GetObj()->GetName()|| L"Ground2" == _pOther->GetObj()->GetName())
	{
		Vec2 vPos = GetPos();
		if (vPos.y < pOtherObj->GetPos().y)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}
}
