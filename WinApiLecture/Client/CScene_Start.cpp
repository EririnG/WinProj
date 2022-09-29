#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{

}

void CScene_Start::Enter()
{
	// Object 추가
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f,384.f));
	pObj->SetScale(Vec2(100.f,100.f));
	AddObject(pObj, GROUP_TYPE::DEFAULT);


	 //몬스터 배치
	int iMonCount = 16;
	float fMoveDist = 25.f;
	float fObjScale = 50.f;
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CMonster* pMonsterObj = nullptr;

	float fTerm = (vResolution.x - ((fMoveDist+ fObjScale/2) * 2)) / (float)(iMonCount-1);

	for (int i = 0; i < iMonCount; ++i)
	{
		// Monster Object 추가
		pMonsterObj = new CMonster;
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i*fTerm , 50.f));
		pMonsterObj->SetScale(Vec2(50.f, 50.f));
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		AddObject(pMonsterObj, GROUP_TYPE::DEFAULT);
	}

}

void CScene_Start::Exit()
{
}
