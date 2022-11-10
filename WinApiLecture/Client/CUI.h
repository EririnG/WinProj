#pragma once
#include "CObject.h"
class CUI :
    public CObject
{

private:
    vector<CUI*> m_vecChildUI;
    CUI*        m_pParentUI;
    Vec2        m_vFinalPos;

    bool        m_bCamAffected; // UI�� ī�޶� ������ �޴� ����
    bool        m_bMouseOn;     // UI ���� ���콺�� �ִ���
    bool        m_bLbtnDown;    // UI �� ���ʹ�ư�� �������� �ִ���

public:

    Vec2 GetFinalPos() { return m_vFinalPos; }
    CUI* GetParent() { return m_pParentUI; }
    bool IsMouseOn() { return m_bMouseOn; }
    bool IsLbtnDown() { return m_bLbtnDown; }

    void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }
    const vector<CUI*>& GetChildUI() {return m_vecChildUI;}

public:

    virtual void update();
    virtual void finalupdate();
    virtual void render(HDC _dc);

  
private:
    void update_child();
    void finalupdate_child();
    void render_child(HDC _dc);

    void MouseOnCheck();

public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();

    virtual CUI* Clone() = 0;

public:
    CUI(bool _bCamAff);
    CUI(const CUI& _origin);
    virtual ~CUI();

    friend class CUIMgr;
};

