#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2		m_vLookAt;		// 카메라가 보는 위치
	CObject*	m_pTarjetObj;	// 카메라 타겟 오브젝트

	Vec2		m_vDiff;		// 해상도 중심위치와, 카메라 LookAt간의 차이 값


public:
	void SetLookAt(Vec2 _vLook) { m_vLookAt = _vLook; }
	void SetTarget(CObject* _pTarget) { m_pTarjetObj = _pTarget; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; ; }


public:
	void update();

private:
	void CalDiff();

};

