#include "pch.h"
#include "CSeneMgr.h"

#include "CScene_Start.h"
#include "CScene_Tool.h"

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
	// ?? ???? ????
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
	// Scene ????
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	
	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");


	// ???? ?? ????
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

void CSeneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	m_pCurScene->Exit();
	m_pCurScene = m_arrScene[(UINT)_eNext];
	m_pCurScene->Enter();
}
