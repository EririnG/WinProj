#pragma once

class CObject;
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};


class CCamera
{
	SINGLE(CCamera);
private:
	Vec2		m_vLookAt;			// 카메라가 보는 위치
	Vec2		m_vCurLookAt;		// 이전위치와 현재위치 보정 위치
	Vec2		m_vPrevLookAt;		// 카메라가 보는 이전 프레임 위치
	
	CObject*	m_pTarjetObj;		// 카메라 타겟 오브젝트
	Vec2		m_vDiff;			// 해상도 중심위치와, 카메라 LookAt간의 차이 값

	float		m_fTime;			// 타겟을 따라가는데 걸리는 시간
	float		m_fSpeed;			// 타겟을 따라가는 속도
	float		m_fAccTime;			// 누적 시간

	CAM_EFFECT	m_eEffect;			// 카메라 효과
	CTexture*	m_pVeilTex;			// 카메라 가림막 텍스쳐(검은색으로)
	float		m_fEffectDuration;	// 효과 진행 시간
	float		m_fCurTime;			// 카메라 효과 현재 진행된 시간

public:
	void SetLookAt(Vec2 _vLook) 
	{ 
		m_vLookAt = _vLook;
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.f;
	}

	void SetTarget(CObject* _pTarget) { m_pTarjetObj = _pTarget; }
	Vec2 GetLookAt() { return m_vCurLookAt; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff;  }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }

	void FadeIn();
	void FadeOut(float _fDuration) 
	{ 
		m_eEffect = CAM_EFFECT::FADE_OUT; 
		m_fEffectDuration = _fDuration;
		
		if (0.f == m_fEffectDuration)
			assert(nullptr);
	}

public:
	void init();
	void update();
	void render(HDC _dc);

private:
	void CalDiff();

};

