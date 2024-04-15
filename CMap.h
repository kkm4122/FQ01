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
			if (ic)  ic->mUnitSprite.Update(10);
		}
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
	void AddChar(int x,int y,  CUnit* a)
	{
		CUnit* asdf = a;
		asdf->TileSet(x, y, L"a.Sno:0");
		asdf->TilePos.x = x;
		asdf->TilePos.y = y;
		mCharacters.push_back(asdf);
	}
	void Draw(HDC hdc)
	{
		
		Mapobj.mDestX = CamPosX+PosX;
		Mapobj.mDestY = CamPosY+PosY;
		CScreen Mapscreen(626, 863);
		for (CUnit* ic : mCharacters) {
			if (ic)  ic->UpdateCamPos(CamPosX, CamPosY);
		}

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
	}
	std::vector<CUnit*>mCharacters;

	CImageFile* MapImg;
	int PosX=16;
	int PosY=48;
	CSprite Mapobj;
	int CamPosX=0;
	int CamPosY=0;
	//CScreen Mapscreen(610,863);
};

