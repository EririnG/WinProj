#include "pch.h"
#include "CObject.h"
#include "CCollider.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"


CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
{
}

CObject::~CObject()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;
}

void CObject::CreateCollider()
{
}

void CObject::update()
{
}

void CObject::finalupdate()
{
	if (m_pCollider)
		m_pCollider->finalupdate();
}


void CObject::render(HDC _dc)
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}