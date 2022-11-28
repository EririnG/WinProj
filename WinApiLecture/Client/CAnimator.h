#pragma once

class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	map<wstring, CAnimation*> m_mapAnim;	// 모든 Anim
	CAnimation*				  m_pCurAnim;	// 현재 재생중인 Anim
	CObject*				  m_pOwner;		// Animator 소유 오브젝트
	bool					  m_bRepeat;	// 반복재생 여부

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

