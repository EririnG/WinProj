//#pragma once
//// �̱��� ����
//// ��ü�� ������ 1���� ����
//// ��𼭵� ���� ���� ����
//
//class ccore
//{
//private:
//	static ccore* g_pinst;
//
//public:
//	
//	// ���� �ɹ��Լ�, ��ü���� ȣ�� ����, this �� ����( �ɹ� ���� �Ұ�), ���� �ɹ��� ���� ����
//	// ���� �ɹ��Լ�
//	static ccore* getinstance()
//	{
//		//���� ȣ�� �� ���
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
	HWND	m_hWnd;			// ���� ������ �ڵ�
	POINT	m_ptResolution; // ���� ������ �ػ�
	HDC		m_hDC;			// ���� �����쿡 Draw �� DC

public:
	SINGLE(CCore);

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void Progress();

private:
	void update();
	void render();


};