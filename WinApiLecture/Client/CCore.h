//#pragma once
//// 싱글톤 패턴
//// 객체의 생성을 1개로 제한
//// 어디서든 쉽게 접근 가능

#include "Define.h"

class CCore
{
private:
	HWND	m_hWnd;			// 메인 윈도우 핸들
	POINT	m_ptResolution; // 메인 윈도우 해상도
	HDC		m_hDC;			// 메인 윈도우에 Draw 할 DC

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