#include "pch.h"
#include "CGround.h"
#include "CCollider.h"
#include "CGravity.h"

CGround::CGround()
{
	CreateCollider();
}

CGround::~CGround()
{
}

void CGround::start()
{
	GetCollider()->SetScale(Vec2(GetScale()));
}

void CGround::update()
{
}

void CGround::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(true);

		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();


		float fLen = abs(vObjPos.y - vPos.y);
		float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;
		
		// 충돌을 접한 상태로 유지하기 위해서 일부로 1픽셀 덜 올려줌
		vObjPos = pOtherObj->GetPos();
		vObjPos.y -= (fValue - 1.f);

		pOtherObj->SetPos(vObjPos);
	}
}

void CGround::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(true);

		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();


		float fLen = abs(vObjPos.y - vPos.y);
		float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;
		
		// 충돌을 접한 상태로 유지하기 위해서 일부로 1픽셀 덜 올려줌
		vObjPos = pOtherObj->GetPos();
		vObjPos.y -= (fValue - 1.f);

		pOtherObj->SetPos(vObjPos);
	}
}

void CGround::OnCollisionExit(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(false);
		Vec2 vPos = pOtherObj->GetPos();

		if(GetPos().y > vPos.y)
		{
			// 충돌중일때 1픽셀 겹치게 해둔 부분을 감안해서 1픽셀을 위로 올려준 채로 충돌을 벗어나게 함
			pOtherObj->SetPos(Vec2(vPos.x, vPos.y - 1.f));
		}
	}
}

