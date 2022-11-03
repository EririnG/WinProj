#include "pch.h"
#include "CKeyMgr.h"

#include "CCore.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',

	VK_MENU, // ALT
	VK_CONTROL, // CTRL
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN, // ENTER
	VK_ESCAPE, // ESC

	VK_LBUTTON,
	VK_RBUTTON,

	
};



CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE,false });
	}

}

void CKeyMgr::update()
{
	//������ ��Ŀ�� �˾Ƴ���
	//HWND hMainWnd = CCore::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus();

	// ������ ��Ŀ�� ���� �� Ű �̺�Ʈ ����
	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			//Ű�� �����ִ�.
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrev)
				{
					//�������� �����־���.
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					// ������ �������� �ʾҴ�.
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrev = true;
			}
			// ������ Ű�� �ȴ����ִ�.
			else
			{
				if (m_vecKey[i].bPrev)
				{
					//�������� �����־���.
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					//�������� �ȴ����־���.
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrev = false;
			}
		}

		// Mouse ��ġ ���
		POINT ptPos = {};
		GetCursorPos(&ptPos);

		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);

		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);

	}
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrev = false;
			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}

	}
	
}


