#include "pch.h"
#include "CImageFile.h"
#include "resource.h"
#include "CMap.h"










CMap::CMap()
{
	
	
	MapImg = CImageFile::New(MAKEINTRESOURCE(BG_FEILD),L"BG_FEILD");
	Mapobj.Set(PosX, PosY, 0, 0, MapImg, 0, CSprite::DrawType_Draw);
	SizeX = MapImg->Width() / 16;
	SizeY = MapImg->Height() / 16;
	for (int y = 0; y <= SizeY; y++)
	{
		for(int x = 0; x <= SizeX; x++)
		{
			mTiles[y][x].unit = nullptr;
			if (y == SizeY)
			{
				mTiles[y][x].unit = &Obstacle;
			}
			else if (x == SizeX)
			{
				mTiles[y][x].unit = &Obstacle;
			}
		}
	}
	
}

CMap::~CMap()
{
}

void CMap::SetMap(const WCHAR* fileName, const WCHAR* name)
{
	MapImg = CImageFile::New(fileName, name);
	Mapobj.Set(PosX, PosY, 0, 0, MapImg, 0, CSprite::DrawType_Draw);
	SizeX = MapImg->Width() / 16;
	SizeY = MapImg->Height() / 16;

}