#pragma once
#include "CUnit.h"


class Map
{

public:
	TILE mTiles[100][100];


	void Update()
	{
		//Soldier1* a = (Soldier1*)mTiles[1][1].unit;
	}

	void SetUnit(class CUnit* unit)
	{

		mTiles[unit->mTile.y][unit->mTile.x].unit = nullptr;	//유닛포인터 공백
		int x = unit->mPosition.x / 16;
		int y = unit->mPosition.y / 16;
		mTiles[y][x].unit = unit;
		unit->mTile.x = x;
		unit->mTile.y = y;

	}


};
