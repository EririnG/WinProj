#pragma once
#include "CUI.h"

class CPanelUI :
    public CUI
{
private:
    Vec2    m_vDragStart;
    bool    m_bMove;

public:
    void SetMove(bool _Move) { m_bMove = _Move; }

public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();

    CLONE(CPanelUI);

public:
    virtual void update();
    virtual void render(HDC _dc);
    
public:
    CPanelUI();
    ~CPanelUI();
};

