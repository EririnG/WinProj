#pragma once
#include "CObject.h"
class CMissile :
    public CObject
{
private:
    float     m_fTheta; // 미사일 방향

public:
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }



public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    void ChangeMissile();

public:
    CMissile();
    ~CMissile();

};

