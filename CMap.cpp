#include "pch.h"
#include "CImageFile.h"
#include "resource.h"
#include "CMap.h"










CMap::CMap()
{
	//CS = new CScreen(640, 800);
	MapImg = CImageFile::New(MAKEINTRESOURCE(BG_FEILD),L"BG_FEILD");
	CIMB = CImageFile::New(MAKEINTRESOURCE(IDB_BITMAP1), L"IDB_BITMAP1");
	CSB.Set(PosX, PosY, 0, 0, CIMB, 0, CSprite::DrawType_AlphaBlend);
	CSB.mAlpha = 0;
	Mapobj.Set(PosX, PosY, 0, 0, MapImg, 0, CSprite::DrawType_Draw);
	SizeX = MapImg->Width() / 16;
	//SizeX++;
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
	CScreen SubScr(hdc, 640, 800);
	Mapobj.mDestX = CamPosX + PosX;
	Mapobj.mDestY = CamPosY + PosY;
	//���� �����ǥ(ī�޶� ��ǥ)�� �ٲ� �ֽ�ȭ
	//CScreen Mapscreen(640, 863);
	for (CUnit* ic : mCharacters) {
		if (ic)  ic->UpdateCamPos(CamPosX, CamPosY);
	}//���� �ִ� ������ǥ �ֽ�ȭ

	Mapobj.Draw(SubScr.m_HDC);
	CSB.Draw(SubScr.m_HDC);
		for (CUnit* ic : mCharacters) {
			if (ic&&ic->DrawUnit) ic->Draw(SubScr.m_HDC);
		}
	SubScr.Draw(hdc, Mapobj.mDestX, Mapobj.mDestY, SizeX * 16, SizeY * 16);
	//delete Mapscreen;
}

void CMap::SetMap(const WCHAR* fileName, const WCHAR* name)
{
	MapImg = CImageFile::New(fileName, name);
	Mapobj.Set(PosX, PosY, 0, 0, MapImg, 0, CSprite::DrawType_Draw);
	SizeX = MapImg->Width() / 16;
	SizeY = MapImg->Height() / 16;

}