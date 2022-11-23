#pragma once

class CObject;

class CCollider
{
private:
	static UINT g_iNextID;

	CObject* m_pOwner; // collider�� �����ϰ� �ִ� ������Ʈ
	Vec2 m_vOffsetPos; // ������Ʈ�� ���� ������� ��ġ
	Vec2 m_vFinalPos; // finalupdate���� �� ������ ���� ���
	Vec2 m_vScale;		// �浹ü�� ũ��

	UINT m_iID; // �浹ü�� ������ ID��
	int  m_iCol; 

	bool m_bActive;	// �浹ü Ȱ��ȭ ����
	


public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

	Vec2 GetFinalPos() { return m_vFinalPos; }

	CObject* GetObj() { return m_pOwner; }

	UINT GetID() { return m_iID; }

public:
	void finalupdate();
	void render(HDC _dc);

public:
	void OnCollision(CCollider* _pOther);//�浹�� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(CCollider* _pOther);//�浹 ����
	void OnCollisionExit(CCollider* _pOther);

	CCollider& operator = (CCollider& _origin) = delete;


public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

	friend class CObject;
};

