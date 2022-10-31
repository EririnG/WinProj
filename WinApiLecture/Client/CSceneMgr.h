#pragma once


class CScene;
class CTexture;

class CSceneMgr
{
	SINGLE(CSceneMgr);

private:
	CScene*		m_arrScene[(UINT)SCENE_TYPE::END]; // ��� �� ���
	CScene*		m_pCurScene; // ���� ��

	CTexture*	m_pTex;// ����� ȭ��
	HDC			m_DC;

public:
	void init();
	void update();
	void render(HDC _dc);
	

	
public:
	CScene* GetCurScene() { return m_pCurScene; }

private:
	void ChangeScene(SCENE_TYPE _eType);

	friend class CEventMgr;
};

