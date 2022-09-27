#pragma once

class CScene;

class CSeneMgr
{
	SINGLE(CSeneMgr);

private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END]; // ��� �� ���
	CScene* m_pCurScene; // ���� ��
public:
	void init();
	void update();
	void render(HDC _dc);
};

