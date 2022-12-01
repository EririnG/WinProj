#include "CPanelUI.h"

#include "CKeyMgr.h"

CPanelUI::CPanelUI()
	: CUI(false)
	, m_bMove(false)
{
}

CPanelUI::~CPanelUI()
{
}


void CPanelUI::MouseOn()
{
	if(m_bMove)
	{
		if (IsLbtnDown())
		{
			Vec2 vDiff = MOUSE_POS - m_vDragStart;

			Vec2 vCurPos = GetPos();
			vCurPos += vDiff;
			SetPos(vCurPos);

			m_vDragStart = MOUSE_POS;
		}
	}
}

void CPanelUI::MouseLbtnDown()
{
	if(m_bMove)
	{
		m_vDragStart = MOUSE_POS;
	}
}

void CPanelUI::MouseLbtnUp()
{
}

void CPanelUI::update()
{
}

void CPanelUI::render(HDC _dc)
{
	CUI::render(_dc);
}


