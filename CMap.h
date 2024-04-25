#pragma once
#include "CUnit.h"
#include "CImageFile.h"
#include"CSprite.h"
#include"CScreen.h"
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

		for (int i = 0; i < 100; i++) 
		{
			for (int j = 0; j < 100; j++) 
			{
				mTiles[i][j].unit = nullptr;
			}
		}
		for (auto ic : mCharacters) 
		{
			if (ic) 
			{
				for (int i = 0; i < ic->size; i++) 
				{
					for (int j = 0; j < ic->size; j++) 
					{
						if (ic->TilePos.x >= 0 && ic->TilePos.x + ic->size < SizeX && ic->TilePos.y >= 0 && ic->TilePos.y + ic->size < SizeY)
						{
							mTiles[ic->TilePos.x + i][ic->TilePos.y + j].unit = ic;
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
		mTiles[unit->TilePos.y][unit->TilePos.x].unit = nullptr;	//À¯´ÖÆ÷ÀÎÅÍ °ø¹é
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
		unit->TilePos.x = x;
		unit->TilePos.y = y;
	}

	void AddChar(int x,int y,int size,int id,  CUnit* a, const WCHAR* Anino)
	{
		CUnit* asdf = a;
		asdf->TileSet(x, y, Anino);
		asdf->TilePos.x = x;
		asdf->TilePos.y = y;
		for (int uy = 0; uy < a->size; uy++)
		{
			for (int ux = 0; ux < a->size; ux++)
			{
				mTiles[y + uy][x + ux].unit = a;
			}
		}
		asdf->size = size;
		asdf->UnitNo = id;
		mCharacters.push_back(asdf);
		//SetUnit(a);
	}
	void Draw(HDC hdc)
	{
		
		Mapobj.mDestX = CamPosX+PosX;
		Mapobj.mDestY = CamPosY+PosY;
		//¸ÊÀÇ Ãâ·ÂÁÂÇ¥(Ä«¸Þ¶ó ÁÂÇ¥)°¡ ¹Ù²ð¶§ ÃÖ½ÅÈ­
		CScreen Mapscreen(SizeX*16+16, SizeY*16);
		for (CUnit* ic : mCharacters) {
			if (ic)  ic->UpdateCamPos(CamPosX, CamPosY);
		}//¸ÊÀÇ ÀÖ´Â À¯´ÖÁÂÇ¥ ÃÖ½ÅÈ­

		Mapobj.Draw(Mapscreen.m_HDC);

		for (CUnit* ic : mCharacters) {
			if (ic) ic->Draw(Mapscreen.m_HDC);
		}
		Mapscreen.Draw(hdc, Mapobj.mDestX, Mapobj.mDestY, SizeX * 16 , SizeY * 16);

	}
	void SetMap(const WCHAR* fileName, const WCHAR* name);
	
	std::vector<CUnit*>mCharacters;

	CImageFile* MapImg;
	CSprite Mapobj;
	int PosX = 16;
	int PosY = 48;
	int CamPosX = 0;
	int CamPosY = 0;
	int SizeX = 0;
	int SizeY = 0;
	//CScreen Mapscreen(610,863);
};

