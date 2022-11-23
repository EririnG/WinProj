#pragma once
#include "CObject.h"

class CCollider;

class CGround :
    public CObject
{
private:
    virtual void start();
    virtual void update();
    

public:
    virtual void OnCollisionEnter(CCollider* _pOther);
 
    
    CLONE(CGround);

public:
    CGround();
    ~CGround();
};

