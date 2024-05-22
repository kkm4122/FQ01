#include "pch.h"
#include "CImageFile.h"
#include "resource.h"
#include "CMap.h"










CMap::CMap()
{
	MapImg = CImageFile::New(MAKEINTRESOURCE(BG_FEILD),L"BG_FEILD");
	CIMB = CImageFile::New(MAKEINTRESOURCE(IDB_BITMAP1), L"IDB_BITMAP1");
	CSB.Set(PosX, PosY, 0, 0, CIMB, 0, CSprite::DrawType_AlphaBlend);
	CSB.mAlpha = 0;
	Mapobj.Set(PosX, PosY, 0, 0, MapImg, 0, CSprite::DrawType_Draw);
	SizeX = MapImg->Width() / 16;
	SizeY = MapImg->Height() / 16;
	for (int y = 0; y <= SizeY; y++)
	{
		for(int x = 0; x <= SizeX; x++)
		{
			mTiles[y][x].unit = nullptr;
			mTiles[y][x].Path = nullptr;
			if (y == SizeY)
			{
				mTiles[y][x].unit = &Obstacle;
				mTiles[y][x].Path = &Obstacle;
			}
			else if (x == SizeX)
			{
				mTiles[y][x].unit = &Obstacle;
				mTiles[y][x].Path = &Obstacle;
			}
		}
	}
	
}

CMap::~CMap()
{
}

void CMap::Draw(HDC hdc)
{
	Mapobj.mDestX = CamPosX + PosX;
	Mapobj.mDestY = CamPosY + PosY;
	//¸ÊÀÇ Ãâ·ÂÁÂÇ¥(Ä«¸Þ¶ó ÁÂÇ¥)°¡ ¹Ù²ð¶§ ÃÖ½ÅÈ­
	CScreen Mapscreen(SizeX * 16 + 16, SizeY * 16);
	for (CUnit* ic : mCharacters) {
		if (ic)  ic->UpdateCamPos(CamPosX, CamPosY);
	}//¸ÊÀÇ ÀÖ´Â À¯´ÖÁÂÇ¥ ÃÖ½ÅÈ­

	Mapobj.Draw(Mapscreen.m_HDC);
	CSB.Draw(Mapscreen.m_HDC);
	for (CUnit* ic : mCharacters) {
		if (ic&&ic->DrawUnit) ic->Draw(Mapscreen.m_HDC);
	}
	Mapscreen.Draw(hdc, Mapobj.mDestX, Mapobj.mDestY, SizeX * 16, SizeY * 16);

}

void CMap::SetMap(const WCHAR* fileName, const WCHAR* name)
{
	MapImg = CImageFile::New(fileName, name);
	Mapobj.Set(PosX, PosY, 0, 0, MapImg, 0, CSprite::DrawType_Draw);
	SizeX = MapImg->Width() / 16;
	SizeY = MapImg->Height() / 16;

}