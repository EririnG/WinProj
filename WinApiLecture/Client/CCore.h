//#pragma once
//// 싱글톤 패턴
//// 객체의 생성을 1개로 제한
//// 어디서든 쉽게 접근 가능
//
//class ccore
//{
//private:
//	static ccore* g_pinst;
//
//public:
//	
//	// 정적 맴버함수, 객체없이 호출 가능, this 가 없다( 맴버 접근 불가), 정적 맴버는 접근 가능
//	// 정적 맴버함수
//	static ccore* getinstance()
//	{
//		//최초 호출 된 경우
//		if (nullptr == g_pinst)
//		{
//			g_pinst = new ccore;
//		}
//
//		return g_pinst;
//	}
//
//	static void release()
//	{
//		if (nullptr != g_pinst)
//		{
//			delete g_pinst;
//			g_pinst = nullptr;
//		}
//	}
//
//
//private:
//	ccore();
//	~ccore();
//};
//
#include "Define.h"

class CCore
{
private:
	HWND	m_hWnd;			// 메인 윈도우 핸들
	POINT	m_ptResolution; // 메인 윈도우 해상도
	HDC		m_hDC;			// 메인 윈도우에 Draw 할 DC

public:
	SINGLE(CCore);

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void Progress();

private:
	void update();
	void render();


};