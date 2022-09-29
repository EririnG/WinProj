#pragma once
#include "CObject.h"
class CMissile :
    public CObject
{
private:
    float     m_fDir; // 미사일 방향

public:
    void SetDir(bool _bUp)
    {
        if (_bUp)
            m_fDir = -1.f;
        else
            m_fDir = 1.f;
    }


public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    void ChangeMissile();

public:
    CMissile();
    ~CMissile();

};

