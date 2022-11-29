#include "pch.h"
#include "CSoundMgr.h"

#include "CCore.h"
#include "CSound.h"

CSoundMgr::CSoundMgr()
    : m_pSound(nullptr)
    , m_pBGM(nullptr)
{
}

CSoundMgr::~CSoundMgr()
{
}


int CSoundMgr::init(void)
{
    if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL)))
    {
        MessageBox(NULL, L"���� ����̽� ���� ����", L"SYSTEM ERROR", MB_OK);
        return false;
    }

    // ���� ����̽� �������� ����
    HWND hWnd = CCore::GetInst()->GetMainHwnd();
    if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag�� ����
    {
        MessageBox(NULL, L"���� ����̽� �������� ����", L"SYSTEM ERROR", MB_OK);
        return false;
    }

    return true;
}

void CSoundMgr::RegisterToBGM(CSound* _pSound)
{
    if (m_pBGM != nullptr)
        m_pBGM->Stop(true);

    m_pBGM = _pSound;
}
