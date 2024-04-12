#include "pch.h"
#include "CImageFile.h"
#include "resource.h"
#include "CMap.h"










CMap::CMap()
{
	MapImg = CImageFile::New(MAKEINTRESOURCE(BG_FEILD),L"BG_FEILD");
	Mapobj.Set(PosX, PosY, 0, 0, MapImg, 0, CSprite::DrawType_Draw);
}

CMap::~CMap()
{
}
