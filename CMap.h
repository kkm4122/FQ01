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
		for (CUnit* ic : mCharacters) {
			if (ic)  ic->mUnitSprite.Update(20);
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
		asdf->size = size;
		asdf->UnitNo = id;
		mCharacters.push_back(asdf);
	}
	void Draw(HDC hdc)
	{
		
		Mapobj.mDestX = CamPosX+PosX;
		Mapobj.mDestY = CamPosY+PosY;
		//¸ÊÀÇ Ãâ·ÂÁÂÇ¥(Ä«¸Þ¶ó ÁÂÇ¥)°¡ ¹Ù²ð¶§ ÃÖ½ÅÈ­
		CScreen Mapscreen(626, 863);
		for (CUnit* ic : mCharacters) {
			if (ic)  ic->UpdateCamPos(CamPosX, CamPosY);
		}//¸ÊÀÇ ÀÖ´Â À¯´ÖÁÂÇ¥ ÃÖ½ÅÈ­

		Mapobj.Draw(Mapscreen.m_HDC);

		for (CUnit* ic : mCharacters) {
			if (ic) ic->Draw(Mapscreen.m_HDC);
		}
		Mapscreen.Draw(hdc,CamPosX,CamPosY,626,863 );

	}
	void SetMap(const WCHAR* fileName, const WCHAR* name)
	{
		MapImg = CImageFile::New(fileName, name);
		Mapobj.Set(PosX, PosY, 0, 0, MapImg, 0, CSprite::DrawType_Draw);
		mx = MapImg->Width() / 16;
		my = MapImg->Height() / 16;
		
	}
	std::vector<CUnit*>mCharacters;

	CImageFile* MapImg;
	int PosX=16;
	int PosY=48;
	CSprite Mapobj;
	int CamPosX=0;
	int CamPosY=0;
	int mx;
	int my;
	//CScreen Mapscreen(610,863);
};

