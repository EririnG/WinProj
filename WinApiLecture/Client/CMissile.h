#pragma once
#include "CObject.h"

class CTexture;

class CMissile :
    public CObject
{
private:
    float     m_fTheta; // 미사일 방향
    Vec2      m_vDir;
    CTexture* m_pTex;

public:
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetDir(Vec2 _vDir) 
    { 
        m_vDir = _vDir; 
        m_vDir = m_vDir.Normalize();

    }


public:
    virtual void update();
    virtual void render(HDC _dc);
    CLONE(CMissile);

public:
    void ChangeMissile();

public:
    CMissile();
    ~CMissile();

};

