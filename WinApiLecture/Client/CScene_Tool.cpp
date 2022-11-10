#include "pch.h"
#include "CScene_Tool.h"
#include "CTile.h"
#include "CCore.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CSceneMgr.h"

#include "resource.h"
#include "CUI.h"

CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}



void CScene_Tool::Enter()
{
	

	// 타일 생성
	CreateTile(5, 5);

	Vec2 vResolution = CCore::GetInst()->GetResolution();

	CUI* pUI = new CUI(false);
	pUI->SetName(L"ParentUI");
	pUI->SetScale(Vec2(500.f, 300.f));
	pUI->SetPos(Vec2(vResolution.x-pUI->GetScale().x,0.f));
	
	
	CUI* pchildui = new CUI(false);
	pchildui->SetName(L"ChildUI");
	pchildui->SetScale(Vec2(100.f, 40.f));
	pchildui->SetPos(Vec2(0.f, 0.f));
	
	pUI->AddChild(pchildui);

	AddObject(pUI, GROUP_TYPE::UI);



	// Camera Look 지정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

}

void CScene_Tool::Exit()
{
}

void CScene_Tool::update()
{
	CScene::update();

	SetTileIdx();

}

void CScene_Tool::SetTileIdx()
{
	if(KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (0.f > vMousePos.x || iTileX <= iCol
			|| 0.f > vMousePos.y || iTileY <= iRow)
		{
			return;
		}

		UINT iIdx = iRow * iTileX + iCol;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx();

	}

	
}








// ======================
// Tile Count Window Proc
// ======================
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK )
		{
			//IDC_EDIT1
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1,nullptr,false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
