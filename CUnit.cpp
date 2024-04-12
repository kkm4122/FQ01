#include "pch.h"
#include "CUnit.h"



CUnit::~CUnit()
{
}

void CUnit::Draw(HDC hdc)
{
	mUnitSprite.Draw(hdc);
}

void CUnit::UpdateCamPos(int cx, int cy)
{
	mUnitSprite.mDestX = -1 * cx + (16 * TilePos.x);
	mUnitSprite.mDestY = -1 * cy + (16 * TilePos.y);
	
}


