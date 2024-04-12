#pragma once
#include "CUnit.h"
#include "CImageFile.h"
#include"CSprite.h"
class CImageFile; 

struct TILE
{
	class CUnit* unit = nullptr;
};

class CMap
{
public:
	CMap();
	~CMap();
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
	void SetMap(const WCHAR* fileName, const WCHAR* name)
	{
		MapImg = CImageFile::New(fileName, name);
		Mapobj.Set(posX, posY, 0, 0, MapImg, 0, CSprite::DrawType_Draw);
	}
	std::vector<CUnit*>mCharactors;

	CImageFile* MapImg;
	int posX=16;
	int posY=48;
	CSprite Mapobj;
};

