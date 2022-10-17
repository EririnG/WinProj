#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"

#include "SelectGDI.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
{
}

CCollider::CCollider(const CCollider& _origin)
	: m_pOwner(nullptr)
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++)
{
}

CCollider::~CCollider()
{
}


void CCollider::finalupdate()
{
	Vec2 vObJectPos = m_pOwner->GetPos();
	m_vFinalPos = vObJectPos + m_vOffsetPos;
}

void CCollider::render(HDC _dc)
{
	SelectGDI g(_dc, PEN_TYPE::GREEN);
	SelectGDI h(_dc, BRUSH_TYPE::HOLLOW);

	Rectangle(_dc
		, (int)(m_vFinalPos.x - m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y - m_vScale.y / 2.f)
		, (int)(m_vFinalPos.x + m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y + m_vScale.y / 2.f));

}

void CCollider::OnCollision(CCollider* _pOther)
{
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
}
