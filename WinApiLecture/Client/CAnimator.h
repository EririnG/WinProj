#pragma once

class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	map<wstring, CAnimation*> m_mapAnim;	// ��� Anim
	CAnimation*				  m_pCurAnim;	// ���� ������� Anim
	CObject*				  m_pOwner;		// Animator ���� ������Ʈ
	bool					  m_bRepeat;	// �ݺ���� ����

public:
	CObject* GetObj() { return m_pOwner; }

public:
	void CreateAnimation(const wstring& _strName,CTexture* _pTex,Vec2 _vLT,Vec2 _vSliceSize,Vec2 _vStep, float _fDuration, UINT _iFrameCount);
	void LoadAnimation(const wstring& _strRealativePath);
	CAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName,bool _bRepeat);

	void render(HDC _dc);
	void update();
	void finalupdate();

public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};

