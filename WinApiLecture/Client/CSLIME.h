#pragma once
#include "CMonster.h"

class CTexture;

class CSLIME :
    public CMonster
{
public:
    CTexture* m_pTex;


public:
    CSLIME();
    ~CSLIME();

};

