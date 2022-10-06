#include "pch.h"
#include "CSeneMgr.h"
#include "CScene_Start.h"
#include "CResMgr.h"
#include "CCore.h"

CSeneMgr::CSeneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
	, m_pTex(nullptr)
	, m_DC(0)
{

}

CSeneMgr::~CSeneMgr()
{
	// 씬 전부 삭제
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}

}

void CSeneMgr::init()
{
	// Scene 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	/*m_arrscene[(uint)scene_type::tool] = new cscene_tool;
	m_arrscene[(uint)scene_type::stage_01] = new cscene_stage01;
	m_arrscene[(uint)scene_type::stage_02] = new cscene_stage02;*/

	// 현재 씬 지정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	//m_pTex = m_pCurScene->GetScene();
	//
	//int iWidth = (int)m_pTex->Width();
	//int iHeight = (int)m_pTex->Height();
	//
	//m_DC = CCore::GetInst()->GetMainDC();

	//TransparentBlt(m_DC,0,0,
	//	iWidth,
	//	iHeight,
	//	m_pTex->GetDC(),
	//	0, 0, iWidth, iHeight, RGB(255, 0, 255));

	m_pCurScene->Enter();
}

void CSeneMgr::update()
{
	m_pCurScene->update();
	m_pCurScene->finalupdate();
}

void CSeneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}
