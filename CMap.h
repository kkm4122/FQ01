#pragma once
#include "CUnit.h"
#include "CImageFile.h"
#include"CSprite.h"
#include"CScreen.h"
class CImageFile; 

struct TILE
{
	class CUnit* unit = nullptr;
	class CUnit* Path = nullptr;
};

class CMap
{
public:
	CMap();
	~CMap();
	TILE mTiles[100][100];

	
	void Update()
	{

		for (int i = 0; i < SizeY; i++) 
		{
			for (int j = 0; j < SizeX; j++) 
			{
				mTiles[i][j].unit = nullptr;
				mTiles[i][j].Path = nullptr;
			}
		}
		for (auto ic : mCharacters) 
		{
			if (ic)
			{
				if (ic->TilePos.x >= 0 && ic->TilePos.x + ic->size - 1 < SizeX && ic->TilePos.y >= 0 && ic->TilePos.y + ic->size - 1 < SizeY)
				{					
					for (int i = 0; i < ic->size; i++)
					{
						for (int j = 0; j < ic->size; j++)
						{
							//if(mTiles[ic->TilePos.y + i][ic->TilePos.x + j].unit!=nullptr)
							mTiles[ic->TilePos.y + i][ic->TilePos.x + j].unit = ic;
						}
					}
				}
			}
		}

		for (CUnit* ic : mCharacters) {
			if (ic)  ic->Update(20);
		}
		//Soldier1* a = (Soldier1*)mTiles[1][1].unit;


	}
	void SetUnit(class CUnit* unit)
	{
		mTiles[unit->TilePos.y][unit->TilePos.x].unit = nullptr;	//유닛포인터 공백
		int x = unit->mPosition.x / 16;
		int y = unit->mPosition.y / 16;
		for (int uy = 0; uy < unit->size; uy++)
		{
			for (int ux = 0; ux < unit->size; ux++)
			{
				mTiles[y + uy][x + ux].unit = unit;
			}
		}
		mTiles[y][x].unit = unit;
		mTiles[y][x].Path = unit;
		unit->TilePos.x = x;
		unit->TilePos.y = y;
	}

	void AddChar(int x,int y,int size,int id,  CUnit* a, const WCHAR* Anino)
	{
		CUnit* AddUnit = a;
		AddUnit->TileSet(x, y, Anino);
		AddUnit->TilePos.x = x;
		AddUnit->TilePos.y = y;
		AddUnit->Umap = this;
		for (int uy = 0; uy < a->size; uy++)
		{
			for (int ux = 0; ux < a->size; ux++)
			{
				mTiles[y + uy][x + ux].unit = a;
			}
		}
		//mTiles[y][x].Path = a;
		AddUnit->size = size;
		AddUnit->UnitNo = id;
		mCharacters.push_back(AddUnit);
		//SetUnit(a);
	}
	void DelChar(CUnit* a)
	{
		CUnit* DelUnit = a;
		for (auto& i : mCharacters)
		{
			if (i == a)
				mCharacters.erase(remove(mCharacters.begin(),mCharacters.end(),i));	
		}
		
	}
	void AddObject(int x, int y, int size, int id, CUnit* a, const WCHAR* Anino)
	{
		CUnit* AddUnit = a;
		AddUnit->TileSet(x, y, Anino);
		AddUnit->TilePos.x = x;
		AddUnit->TilePos.y = y;
		for (int uy = 0; uy < a->size; uy++)
		{
			for (int ux = 0; ux < a->size; ux++)
			{
				mTiles[y + uy][x + ux].Path = a;
			}
		}
		mTiles[y][x].Path = a;
		AddUnit->size = size;
		AddUnit->UnitNo = id;
		mObject.push_back(AddUnit);
	}
	void Draw(HDC hdc);
	
	void SetMap(const WCHAR* fileName, const WCHAR* name);
	
	std::vector<CUnit*>mCharacters;
	std::vector<CUnit*>mObject;
	CUnit Obstacle;
	CImageFile* MapImg;
	CImageFile* CIMB;
	//CScreen* CS;
	CSprite CSB;
	CSprite Mapobj;
	int PosX = 0;
	int PosY = 0;
	int CamPosX = 16;//UI창내부 화면 좌표
	int CamPosY = 48;//UI창내부 화면 좌표
	int SizeX = 0;
	int SizeY = 0;
	//CScreen Mapscreen(610,863);
};

