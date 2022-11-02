#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2		m_vLookAt;		// ī�޶� ���� ��ġ
	CObject*	m_pTarjetObj;	// ī�޶� Ÿ�� ������Ʈ

	Vec2		m_vDiff;		// �ػ� �߽���ġ��, ī�޶� LookAt���� ���� ��


public:
	void SetLookAt(Vec2 _vLook) { m_vLookAt = _vLook; }
	void SetTarget(CObject* _pTarget) { m_pTarjetObj = _pTarget; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; ; }


public:
	void update();

private:
	void CalDiff();

};

