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



public:
	void CreateAnimation(const wstring& _strName,CTexture* _pTex,Vec2 _vLT,Vec2 _vSliceSize,Vec2 _vStep, float _fDuration, UINT _iFrameCount);
	CAnimation* FindAnimation(const wstring& _strName);
	void Play();

	void render(HDC _dc);
	void update();

public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};

