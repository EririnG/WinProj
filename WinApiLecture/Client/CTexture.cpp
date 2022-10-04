#include "pch.h"
#include "CTexture.h"

#include "CCore.h"

CTexture::CTexture()
	: m_hBit(0)
	, m_dc(0)
	, m_bitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}



void CTexture::Load(const wstring& _strfilepath)
{
	m_hBit = (HBITMAP)LoadImage(nullptr, _strfilepath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);
	// 비트맵과 연결할 DC
	
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	// 비트맵과 DC 연결
	HBITMAP hprevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hprevBit);


	// 비트맵정보
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);



}