#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"

#include "SelectGDI.h"

CCollider::CCollider()
	: m_pOwner(nullptr)
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
	SelectGDI g(_dc, PEN_TYPE::RED);
	SelectGDI h(_dc, BRUSH_TYPE::HOLLOW);

	Rectangle(_dc
		, (int)(m_vFinalPos.x - m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y - m_vScale.y / 2.f)
		, (int)(m_vFinalPos.x + m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y + m_vScale.y / 2.f));

}
