#include "pch.h"
#include "CScene_Start.h"

#include "CCore.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CUIMgr.h"

#include "resource.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"

void ChangeScene(DWORD_PTR, DWORD_PTR);

CScene_Start::CScene_Start()
	: m_pUI(nullptr)
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
}

void CScene_Start::ChangeScene(DWORD_PTR, DWORD_PTR)
{
	
}



void CScene_Start::Enter()
{
	// 툴 Scene 에서 사용할 메뉴를 붙인다.
	CCore::GetInst()->DockMenu();

	// 타일 생성

	Vec2 vResolution = CCore::GetInst()->GetResolution();

	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(500.f, 600.f));
	pPanelUI->SetPos(Vec2(0.f, vResolution.y - pPanelUI->GetScale().y));


	CBtnUI* pStartBtnUI = new CBtnUI;
	pStartBtnUI->SetName(L"StartBtnChildUI");
	pStartBtnUI->SetScale(Vec2(400.f, 120.f));
	pStartBtnUI->SetPos(Vec2(50.f, 50.f));
	((CBtnUI*)pPanelUI->GetChildUI()[0])->SetClickedCallBack(ChangeScene, 0, 0);

	pPanelUI->AddChild(pStartBtnUI);
	AddObject(pPanelUI, GROUP_TYPE::UI);

	CBtnUI* pSetBtnUI = new CBtnUI;
	pSetBtnUI->SetName(L"SetBtnChildUI");
	pSetBtnUI->SetScale(Vec2(400.f, 120.f));
	pSetBtnUI->SetPos(Vec2(50.f, 175.f));
	((CBtnUI*)pSetBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Start::CreateTile);
	pPanelUI->AddChild(pSetBtnUI);
	AddObject(pPanelUI, GROUP_TYPE::UI);

	CBtnUI* pHelpBtnUI = new CBtnUI;
	pHelpBtnUI->SetName(L"pHelpBtnChildUI");
	pHelpBtnUI->SetScale(Vec2(400.f, 120.f));
	pHelpBtnUI->SetPos(Vec2(50.f, 300.f));
	((CBtnUI*)pHelpBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Start::CreateTile);
	pPanelUI->AddChild(pHelpBtnUI);
	AddObject(pPanelUI, GROUP_TYPE::UI);

	CBtnUI* pExitBtnUI = new CBtnUI;
	pExitBtnUI->SetName(L"ExitBtnChildUI");
	pExitBtnUI->SetScale(Vec2(400.f, 120.f));
	pExitBtnUI->SetPos(Vec2(50.f, 425.f));
	((CBtnUI*)pExitBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Start::CreateTile);
	pPanelUI->AddChild(pExitBtnUI);
	AddObject(pPanelUI, GROUP_TYPE::UI);



	/*
	CUI* pClonePanel = pPanelUI->Clone();
	pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f, 0.f));
	((CBtnUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(ChangeScene, 0, 0);
	AddObject(pClonePanel, GROUP_TYPE::UI);

	m_pUI = pClonePanel;
*/
// Camera Look 지정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);
}

void CScene_Start::Exit()
{
	CCore::GetInst()->DivideMenu();

	DeleteAll();
}

void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}
