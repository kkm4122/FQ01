#include "pch.h"
#include "CMap.h"
#include "CUnitMange.h"
#include "CImageFile.h"
#include "InGameIntro3.h"
#define VK_W 87
#define VK_S 83
#define VK_A 65
#define VK_D 68
InGameIntro3::InGameIntro3()
{
	SetScene();
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
	FieldMap->Update();
}

void InGameIntro3::onDraw(HDC hdc)
{//subcamPosy = 0;
	//subHeight = 0;
	CScreen subscreen(640,368);
	
	//18 Á¦³Ú·ç
	FieldMap->Draw(hdc);
	UIs.Draw(hdc);
	submap.mDestY = subcamPosy;
	submap.Draw(subscreen.m_HDC);
	for (CUnit* ic : FieldMap->mCharacters)
	{
		if (ic) ic->UpdateCamPos(FieldMap->CamPosX, subcamPosy);
	}
	for (CUnit* ic : FieldMap->mCharacters)
	{
		if (ic) ic->Draw(subscreen.m_HDC);
	}
	//Subsp.mDestY = 
	Subsp.Draw(subscreen.m_HDC);
	subscreen.Draw(hdc,0,48,Subsp.mSrcWidth,Subsp.mSrcHeight,0,subHeight);
}

void InGameIntro3::onKeyDown(UINT virtual_key)
{
	switch (virtual_key)
	{
	case(VK_UP):
		FieldMap->CamPosY -= 16;
		break;
	case(VK_DOWN):
		FieldMap->CamPosY += 16;
		break;
	case(VK_LEFT):
		FieldMap->mCharacters[18]->TilePos.x--;
		break;
	case(VK_RIGHT):
		FieldMap->mCharacters[18]->TilePos.x++;
		break;
	case(VK_W):
		subHeight+=16;
		break;
	case(VK_S):
		subHeight -= 16;
		break;
	case(VK_A):
		subcamPosy -= 16;
		//FieldMap->CSB.mAlpha+=5;
		break;
	case(VK_D):
		subcamPosy += 16;
		//FieldMap->CSB.mAlpha -= 5;
		break;
	case(VK_SPACE):
		FieldMap->mCharacters[18]->TilePos.y = 8;
		break;
	}
	
}

void InGameIntro3::onMouseDown(UINT x, UINT y, UINT left_right)
{
}

void InGameIntro3::SetScene()
{
	FieldMap = new CMap;
	FieldMap->SetMap(MAKEINTRESOURCE(IDB_GARSIACASTLE), L"IDB_GARSIACASTLE");
	FieldMap->CamPosY = 16 * 4;
	Subim = CImageFile::New(MAKEINTRESOURCE(IDB_SCREENFRAME), L"IDB_SCREENFRAME");
	Subsp.Set(0, 0, 0, 0, Subim, RGB(255, 0, 255), CSprite::DrawType_Transparent);
	submap.Set(FieldMap->PosX + 16, subcamPosy, 0, 0, FieldMap->MapImg, 0, CSprite::DrawType_Transparent);
	//FieldMap->CamPosY = -16*16;
	UI = CImageFile::New(MAKEINTRESOURCE(IDB_UI), L"IDB_UI");
	UIs.Set(0, 0, 0, 0, UI, RGB(255, 0, 255), CSprite::DrawType_Transparent);
	//À§
	FieldMap->AddChar(12, 8, 2, 2, CUnitMange::a->GarshiaSoldier[0], L"a.SnoSTOP:0");
	FieldMap->AddChar(24, 8, 2, 2, CUnitMange::a->GarshiaSoldier[1], L"a.SnoSTOP:0");
	//¿Þ
	FieldMap->AddChar(2, 29, 2, 2, CUnitMange::a->GarshiaSoldier[2], L"a.SnoSTOP:2");
	FieldMap->AddChar(2, 33, 2, 2, CUnitMange::a->GarshiaSoldier[3], L"a.SnoSTOP:2");
	FieldMap->AddChar(8, 29, 2, 2, CUnitMange::a->GarshiaSoldier[4], L"a.SnoSTOP:2");
	FieldMap->AddChar(8, 33, 2, 2, CUnitMange::a->GarshiaSoldier[5], L"a.SnoSTOP:2");
	FieldMap->AddChar(5, 31, 2, 2, CUnitMange::a->GarshiaSoldier[6], L"a.SnoSTOP:2");
	FieldMap->AddChar(5, 35, 2, 2, CUnitMange::a->GarshiaSoldier[7], L"a.SnoSTOP:2");
	//¿À
	FieldMap->AddChar(28, 29, 2, 2, CUnitMange::a->GarshiaSoldier[8], L"a.SnoSTOP:1");
	FieldMap->AddChar(28, 33, 2, 2, CUnitMange::a->GarshiaSoldier[9], L"a.SnoSTOP:1");
	FieldMap->AddChar(34, 31, 2, 2, CUnitMange::a->GarshiaSoldier[10], L"a.SnoSTOP:1");
	FieldMap->AddChar(34, 33, 2, 2, CUnitMange::a->GarshiaSoldier[11], L"a.SnoSTOP:1");
	FieldMap->AddChar(31, 31, 2, 2, CUnitMange::a->GarshiaSoldier[12], L"a.SnoSTOP:1");
	FieldMap->AddChar(31, 35, 2, 2, CUnitMange::a->GarshiaSoldier[13], L"a.SnoSTOP:1");
	//Áß¾Ó
	FieldMap->AddChar(24, 31, 2, 2, CUnitMange::a->GarshiaSoldier[14], L"a.SnoSTOP:1");
	FieldMap->AddChar(22, 29, 2, 2, CUnitMange::a->GarshiaSoldier[15], L"a.SnoSTOP:0");
	FieldMap->AddChar(12, 31, 2, 2, CUnitMange::a->GarshiaSoldier[16], L"a.SnoSTOP:2");
	FieldMap->AddChar(14, 29, 2, 2, CUnitMange::a->GarshiaSoldier[17], L"a.SnoSTOP:0");
	FieldMap->AddChar(18, 25, 2, 2, CUnitMange::a->Genelu, L"a.SnoSTOP:0");
	FieldMap->AddChar(18, 38, 2, 2, CUnitMange::a->Ares, L"a.SnoSTOP:3");
}
