#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CUIMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "SelectGDI.h"
#include "resource.h"
#include "CSoundMgr.h"
#include "CSound.h"

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{

}
CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	DestroyMenu(m_hMenu);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;
	
	//해상도에 맞게 윈도우 크기 조정
	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y), false);

	// 메뉴바 생성

	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));

	m_hDC = GetDC(m_hWnd);


	// 이중 버퍼링 용도의 텍스쳐 한장을 만든다..

	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);


	//자주 사용 할 펜 및 브러쉬 생성
	CreateBrushPen();

	//Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CCamera::GetInst()->init();
	CSoundMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();
	
	// Sound 로드 테스트
	//CResMgr::GetInst()->LoadSound(L"StartSceneBGM", L"sound\\TimeTemple.wav");
	//CSound* pNewSound = CResMgr::GetInst()->FindSound(L"BGM_01");

	//pNewSound->Play();

	//pNewSound->SetPosition(50.f);
	//pNewSound->PlayAsBGM(true);
	//pNewSound->SetVolume(10.f);

	return S_OK;
}



void CCore::Progress()
{
	// ==============
	// Manager Update
	// ==============

	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CCamera::GetInst()->update();
	// ============
	// Scene Update
	// ============
	CSceneMgr::GetInst()->update();

	// 충돌체크
	CCollisionMgr::GetInst()->update();

	// UI 이벤트 체크
	CUIMgr::GetInst()->update();



	//=========
	//Rendering
	//=========
	//화면 Clear
	Clear();
	
	CSceneMgr::GetInst()->render(m_pMemTex->GetDC());
	CCamera::GetInst()->render(m_pMemTex->GetDC());


	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();

	// ==============
	// 이벤트 지연처리
	// ==============

	CEventMgr::GetInst()->update();
}

void CCore::Clear()
{
	SelectGDI gdi(m_pMemTex->GetDC(), BRUSH_TYPE::BLACK);
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
}

void CCore::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
	// red blue green pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0,0,255));

}

void CCore::DockMenu()
{
	SetMenu(m_hWnd, m_hMenu);
	ChangeWindowSize(GetResolution(), true);
}

void CCore::DivideMenu()
{
	SetMenu(m_hWnd, nullptr);
	ChangeWindowSize(GetResolution(), false);
}

void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	RECT rt = { 0,0,(long)_vResolution.x,(long)_vResolution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
}

