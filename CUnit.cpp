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
	mUnitSprite.Update(dt);
}

void CUnit::Draw(HDC hdc)
{
	mUnitSprite.Draw(hdc);
}

bool CUnit::CANMoveOneTile(CMap* Map)
{
	return false;
}

void CUnit::TargetAstar(CMap* Map, CUnit* a)
{
	mTarget = { a->TilePos.x, a->TilePos.y };
	path = A.PathFind(a, Map, TilePos, mTarget);
}

bool CUnit::Searchthis(CMap* Map, CUnit* Target, POS NextP)
{
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			if (Map->mTiles[NextP.y + y][NextP.x + x].unit == Target)
			{
				return true;
			}
		}
	}
	return false;
}

void CUnit::MovePath(CMap* Map, CUnit* a)
{
	TargetAstar(Map, a);
}

bool CUnit::CanMove(CMap* Map, CUnit* Target, POS NextP)
{
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			if (Map->mTiles[NextP.y + y][NextP.x + x].unit != nullptr&& Map->mTiles[NextP.y + y][NextP.x + x].unit!=this)
			{
				return false;
			}
		}
	}
	return true;
}

void CUnit::UpdateCamPos(int cx, int cy)
{
	mUnitSprite.mDestX =  cx + (16 * TilePos.x);
	mUnitSprite.mDestY =  cy + (16 * TilePos.y);
}


