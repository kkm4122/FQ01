#include "pch.h"
#include "CMap.h"
#include "CUnit.h"



CUnit::~CUnit()
{
}

bool CUnit::isMoving()
{

	return !(mPosition == mTarget);
}

void CUnit::Update(int dt)
{
		
	}

void CUnit::Draw(HDC hdc)
{
	mUnitSprite.Draw(hdc);
}

bool CUnit::CANMoveOneTile(CMap* Map)
{
	return false;
}

void CUnit::UpdateCamPos(int cx, int cy)
{
	mUnitSprite.mDestX =  cx + (16 * TilePos.x);
	mUnitSprite.mDestY =  cy + (16 * TilePos.y);
}


