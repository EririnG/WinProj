#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2		m_vLookAt;		// ī�޶� ���� ��ġ
	Vec2		m_vCurLookAt;	// ������ġ�� ������ġ ���� ��ġ
	Vec2		m_vPrevLookAt;	// ī�޶� ���� ���� ������ ��ġ
	CObject*	m_pTarjetObj;	// ī�޶� Ÿ�� ������Ʈ

	Vec2		m_vDiff;		// �ػ� �߽���ġ��, ī�޶� LookAt���� ���� ��


public:
	void SetLookAt(Vec2 _vLook) { m_vLookAt = _vLook; }
	void SetTarget(CObject* _pTarget) { m_pTarjetObj = _pTarget; }
	Vec2 GetLookAt() { return m_vCurLookAt; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff;  }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }

public:
	void update();

private:
	void CalDiff();

};

