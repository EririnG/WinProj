#pragma once
#include "CUI.h"

class CScene;
class CObject;

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

typedef void(CScene::*SCENE_MEMFUNC)(void);
typedef void(CObject::* OBJECT_MEMFUNC)(void);

class CBtnUI :
    public CUI
{
private:
    BTN_FUNC        m_pFunc;
    DWORD_PTR       m_param1;
    DWORD_PTR       m_param2;

    CScene*         m_pSceneInst; // ȣ�� ��ų ��ü
    SCENE_MEMFUNC   m_pSceneFunc; // ȣ�� �� �Լ�
public:

    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();


    void SetClickedCallBack(BTN_FUNC _pFunc,DWORD_PTR _param1,DWORD_PTR _param2) 
    {
        m_pFunc = _pFunc; 
        m_param1 = _param1;
        m_param2 = _param2;
    }

    void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc)
    {
        m_pSceneInst = _pScene;
        m_pSceneFunc = _pSceneFunc;
    }

    CLONE(CBtnUI);
public:
    CBtnUI();
    ~CBtnUI();

};

