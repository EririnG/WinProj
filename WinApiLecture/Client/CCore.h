//#pragma once
//// �̱��� ����
//// ��ü�� ������ 1���� ����
//// ��𼭵� ���� ���� ����

#include "Define.h"

class CCore
{
private:
	HWND	m_hWnd;			// ���� ������ �ڵ�
	POINT	m_ptResolution; // ���� ������ �ػ�
	HDC		m_hDC;			// ���� �����쿡 Draw �� DC

	HBITMAP m_hBit;
	HDC		m_memDC;
public:
	SINGLE(CCore);

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void Progress();

private:
	void update();
	void render();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	POINT GetResolution() { return m_ptResolution; }
};