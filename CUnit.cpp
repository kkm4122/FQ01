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
		if(isMoving())
		{
			mDir.x = mTarget.x - mPosition.x;
			mDir.y = mTarget.y - mPosition.y;

			
				mDir.x *= mSpeed;
				mDir.y *= mSpeed;

				mPosition.x += mDir.x;
				mPosition.y += mDir.y;
			
			//대각선 이동도 포함 //단위벡터
			//g_Map->SetUnit(this);
		}
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


