#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"

CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llFrequency{}
	, m_llPrevCount{}
	, m_dDT(0.)
	, m_iCallCount(0)
	, m_dACC(0.)
{
}

CTimeMgr::~CTimeMgr()
{}

void CTimeMgr::init()
{
	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_llPrevCount);
	// �ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);
	// ���� �������� ī���ð� , ���� ������ ī���� ���� ���̸� ���Ѵ�.
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart)/(double)m_llFrequency.QuadPart;
	// ���� ī��Ʈ ���� ���簪���� ����(������ ����� ���ؼ�)
	m_llPrevCount = m_llCurCount;
}

void CTimeMgr::render()
{
	++m_iCallCount;
	m_dACC += m_dDT;

	if (m_dACC >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dACC = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
