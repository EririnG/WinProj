#pragma once

class CAnimator;
class CTexture;

struct tAnimFrm
{
	Vec2	vLT;
	Vec2	vSlice;
	float	fDuration;
};

class CAnimation
{
private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;
	vector<tAnimFrm>	m_vecFrm; // 모든 프레임 정보

public:
	const wstring& GetName() { return m_strName; }

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	void update();
	void render(HDC _dc);
	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep,float _fDuration, UINT _iFrameCount);

public:
	CAnimation();
	~CAnimation();
	
	friend class CAnimator;
};

