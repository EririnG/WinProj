#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"

#include "CPathMgr.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

CScene_Start::CScene_Start()
	: m_pTex(nullptr)
{
	/*m_pTex = CResMgr::GetInst()->LoadTexture(L"StartSceneTex", L"texture\\scene\\start.bmp");
	SetScene(m_pTex);*/

}

CScene_Start::~CScene_Start()
{

}

void CScene_Start::update()
{
	CScene::update();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}
}

void CScene_Start::Enter()
{
	// Object 추가
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f,640.f));
	pObj->SetScale(Vec2(100.f,100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	CObject* pOtherPlayer = pObj->Clone();
	pOtherPlayer->SetPos(Vec2(740.f, 640.f));
	AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	 //몬스터 배치
	int iAMon_Count = 5;
	int iBMon_Count = 8;
	
	float fAMon_MoveDist = 25.f;
	float fBMon_MoveDist = 10.f;

	float fAMon_ObjScale = 50.f;
	float fBMon_ObjScale = 40.f;


	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CMonster* pAMonsterObj = nullptr;
	CMonster* pBMonsterObj = nullptr;

	float fATerm = (vResolution.x - ((fAMon_MoveDist + fAMon_ObjScale /2) * 2)) / (float)(iAMon_Count -1);
	float fBTerm = (vResolution.x - ((fBMon_MoveDist + fBMon_ObjScale / 2) * 2)) / (float)(iBMon_Count - 1);

	for (int i = 0; i < iAMon_Count; ++i)
	{
		// Monster Object 추가
		pAMonsterObj = new CMonster;
		pAMonsterObj->SetName(L"Monster");
		pAMonsterObj->SetPos(Vec2((fAMon_MoveDist + fAMon_ObjScale / 2.f) + (float)i* fATerm, 100.f));
		pAMonsterObj->SetScale(Vec2(fAMon_ObjScale, fAMon_ObjScale));
		pAMonsterObj->SetMoveDistance(fAMon_MoveDist);
		pAMonsterObj->SetCenterPos(pAMonsterObj->GetPos());
		AddObject(pAMonsterObj, GROUP_TYPE::MONSTER);
	}
	for (int i = 0; i < iBMon_Count; ++i)
	{
		pBMonsterObj = new CMonster;
		pBMonsterObj->SetPos(Vec2((fBMon_MoveDist + fBMon_ObjScale / 2.f) + (float)i * fBTerm, 200.f));
		pBMonsterObj->SetScale(Vec2(fBMon_ObjScale, fBMon_ObjScale));
		pBMonsterObj->SetMoveDistance(fBMon_MoveDist);
		pBMonsterObj->SetCenterPos(pBMonsterObj->GetPos());
		AddObject(pBMonsterObj, GROUP_TYPE::MONSTER);
	}

	// 충돌 지정
	// Player 그룹과 Monster 그룹 간의 충돌체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

}

void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}
