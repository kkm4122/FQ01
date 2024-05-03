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

void CUnit::WalkToAstar(CMap* Map, CUnit* a)
{
	if (!path.empty())
	{
		POS* pathasdf = path.back();
		
		if (pathasdf->x != a->TilePos.x || pathasdf->y != a->TilePos.y)
		{
			path.clear();
			TargetAstar(Map, a);
		}
		else
		{
			pathasdf = path.front();

		}
	}
}

void CUnit::StackToAstar(CMap* Map, CUnit* target)
{
	if (!path_stack.empty())
	{
		POS* nextP = path_stack.top();
		/*
		다음 갈 위치에 장애물 있으면 해결동작,
		astar bool함수 만들기
		move bool 
		*/
		Move(nextP->x-TilePos.x, nextP->y-TilePos.y);
		path_stack.pop();
		
	}
}

void CUnit::Move(int x, int y)
{
	if (x == 1 && y == 0)
	{
		TilePos.x++;
		mUnitSprite.ChangeAnimation(mRight);
	}
	else if (x == -1 && y == 0)
	{
		TilePos.x--;
		mUnitSprite.ChangeAnimation(mLeft);
	}
	else if (x == 0 && y == 1)
	{
		TilePos.y++;
		mUnitSprite.ChangeAnimation(mDown);
	}
	else if (x == 0 && y == -1)
	{
		TilePos.y--;
		mUnitSprite.ChangeAnimation(mUp);
	}
}

bool CUnit::CANMoveOneTile(CMap* Map)
{
	return false;
}

void CUnit::TargetAstar(CMap* Map, CUnit* a)
{
	
		mTarget = { a->TilePos.x, a->TilePos.y };
		path = A.PathFind(a, Map, TilePos, a->TilePos);
	
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


