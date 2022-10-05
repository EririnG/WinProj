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

	// ���� ����ϴ� GDI Object
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];

public:
	SINGLE(CCore);

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void Progress();



private:
	void CreateBrushPen();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }

};