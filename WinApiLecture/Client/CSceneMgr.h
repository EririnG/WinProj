#pragma once


class CScene;
class CTexture;

class CSceneMgr
{
	SINGLE(CSceneMgr);

private:
	CScene*		m_arrScene[(UINT)SCENE_TYPE::END]; // ¸ðµç ¾À ¸ñ·Ï
	CScene*		m_pCurScene; // ÇöÀç ¾À

	CTexture*	m_pTex;// ÇöÀç¸Ê È­¸é
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

