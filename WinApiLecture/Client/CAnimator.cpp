#include "pch.h"
#include "CAnimator.h"

CAnimator::CAnimator()
	: m_pOwner(nullptr)
{
}

CAnimator::~CAnimator()
{
	Safe_Delete_Map(m_mapAnim);
}
