#include "pch.h"
#include "CMap.h"
#include "CUnitMange.h"
#include "CImageFile.h"
#include "InGameIntro3.h"

InGameIntro3::InGameIntro3()
{
	FieldMap = new CMap;
	FieldMap->SetMap(MAKEINTRESOURCE(IDB_GARSIACASTLE), L"IDB_GARSIACASTLE");
	FieldMap->CamPosY += 16;
	UI = CImageFile::New(MAKEINTRESOURCE(IDB_UI), L"IDB_UI");
	UIs.Set(0, 0, 0, 0, UI, RGB(255, 0, 255), CSprite::DrawType_Transparent);
}

InGameIntro3::~InGameIntro3()
{
}

bool InGameIntro3::Sample()
{
	return false;
}

bool InGameIntro3::isChanged()
{
	return false;
}

void InGameIntro3::onFrameMove()
{
}

void InGameIntro3::onDraw(HDC hdc)
{
	FieldMap->Draw(hdc);
	UIs.Draw(hdc);
}

void InGameIntro3::onKeyDown(UINT virtual_key)
{
}

void InGameIntro3::onMouseDown(UINT x, UINT y, UINT left_right)
{
}
