#pragma once
#include "CObject.h"
class CUI :
    public CObject
{

private:
    vector<CUI*> m_vecChildUI;
    CUI*        m_pParentUI;

public:
    CUI* GetParent() { return m_pParentUI; }
    void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }


public:

    virtual void update();
    virtual void finalupdate();
    virtual void render(HDC _dc);

    CLONE(CUI);
private:
    void update_child();
    void render_child(HDC _dc);

public:
    CUI();
    ~CUI();

};

