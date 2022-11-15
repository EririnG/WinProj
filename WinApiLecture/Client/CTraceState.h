#pragma once
#include "CState.h"
class CTraceState :
    public CState
{


public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();


public:
    CTraceState();
    ~CTraceState();
};

