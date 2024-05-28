#include "pch.h"
#include "CMap.h"
#include "CUnitMange.h"
#include "CImageFile.h"
#include "CApplication.h"
#include "InGameIntro3.h"
#include "CScreen.h"
#define VK_W 87
#define VK_S 83
#define VK_A 65
#define VK_D 68
int dt2 = 0;
InGameIntro3::InGameIntro3()
{
	SetScene();
}

InGameIntro3::~InGameIntro3()
{
	//delete subscreen;
	
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
	switch (tsno)
	{
	case (0):
		dt++;
		if (dt % 5 == 0)
		{
			dt = 0;
			if(FieldMap->CamPosY >48-304)FieldMap->CamPosY -= 16;
			else
			{
				if(CUnitMange::a->Ares->TilePos.y>34)
				CUnitMange::a->Ares->WalkOneTile(FieldMap, MOVE_UP);
				else
				{
					CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s3);
					tsno++;
					
				}
			}
		}
		break;
	case 1:
		Tbox = true;
		ClickEvent = true;
		if (Tboxnum == 3) {
			tsno++;
			Tbox = false;
			ClickEvent = false;
		}
		break;
	case 2:

		dt++;
		if (dt % 5 == 0)
		{
			dt = 0;
			if (CUnitMange::a->Ares->TilePos.y > 30)
				CUnitMange::a->Ares->WalkOneTile(FieldMap, MOVE_UP);
			else
			{
				if (CUnitMange::a->GarshiaSoldier[14]->TilePos.x > 20)
				{
					CUnitMange::a->GarshiaSoldier[14]->
						WalkOneTile(FieldMap, MOVE_LEFT);
				}
				if (CUnitMange::a->GarshiaSoldier[15]->TilePos.x > 20)
				{
					CUnitMange::a->GarshiaSoldier[15]->
						WalkOneTile(FieldMap, MOVE_LEFT);
				}
				//20
				if (CUnitMange::a->GarshiaSoldier[16]->TilePos.x < 16)
				{
					CUnitMange::a->GarshiaSoldier[16]->
						WalkOneTile(FieldMap, MOVE_RIGHT);
				}
				if (CUnitMange::a->GarshiaSoldier[17]->TilePos.x < 16)
				{
					CUnitMange::a->GarshiaSoldier[17]->
						WalkOneTile(FieldMap, MOVE_RIGHT);
				}
				else
				{
					dt2++;
				}
				if (dt2 == 8) 
				{
					dt2 = 0;
					tsno++;
				}
			}
		}
		
		break;
	case 3:
		dt++;
		switch (dt)
		{
		case 10:
			CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s9);
			break;
		case 20:
			CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s8);
			break;
		case 30:
			CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s10);
			break;
		case 40:
			CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s11);
			break;
		case 50:
			CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s9);
			break;
		case 60:
			CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s8);
			break;
		case 80:
			CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s4);
			break;
		case 100:
			CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s12);
			break;
		case 110:
			for(int i=0;i<4; i++)
			{ 
				CUnitMange::a->GarshiaSoldier[14 + i]->mUnitSprite.ChangeAnimation(s11);
			}
			CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s9);
			break;
		case 120:
			for (int i = 0; i < 4; i++)
			{
				CUnitMange::a->GarshiaSoldier[14 + i]->mUnitSprite.ChangeAnimation(s5);
			}
			break;
		case 130:
			for (int i = 0; i < 4; i++)
			{
				CUnitMange::a->GarshiaSoldier[14 + i]->mUnitSprite.ChangeAnimation(s10);
			}
			break;
		case 140:
			for (int i = 0; i < 4; i++)
			{
				CUnitMange::a->GarshiaSoldier[14 + i]->mUnitSprite.ChangeAnimation(s4);
			}
			break;
		case 150:
			for (int i = 0; i < 4; i++)
			{
				CUnitMange::a->GarshiaSoldier[14 + i]->DrawUnit = false;
			}
			break;
		case 160:
			CUnitMange::a->Ares->WalkOneTile(FieldMap, MOVE_UP);
			CUnitMange::a->Ares->WalkOneTile(FieldMap, MOVE_UP);
			break;
		case 170:
			tsno++;
			CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s0);
			break;
		default:
			break;
		}
		break;
	case 4:
		break;
	default:
		break;
	}
}

void InGameIntro3::onDraw(HDC hdc)
{//subcamPosy = 0;
	//subHeight = 0;
	CScreen SubScr(hdc, 640, 366);

	//18 Á¦³Ú·ç
	FieldMap->Draw(hdc);
	UIs.Draw(hdc);
	submap.mDestY = subcamPosy;
	submap.Draw(SubScr.m_HDC);
	for (CUnit* ic : FieldMap->mCharacters)
	{
		if (ic) ic->UpdateCamPos(FieldMap->CamPosX, subcamPosy);
	}
	for (CUnit* ic : FieldMap->mCharacters)
	{
		if (ic) ic->Draw(SubScr.m_HDC);
	}
	//Subsp.mDestY = 
	Subsp.Draw(SubScr.m_HDC);
	SubScr.Draw(hdc, 0, 48, Subsp.mSrcWidth, Subsp.mSrcHeight - 16, 0, subHeight);

	{//ÆùÆ® ¼³Á¤
		LoadString(CApplication::theApp->mhInst, IDS_CUT3_1 + Tboxnum, str, 512);
		SetBkMode(hdc, TRANSPARENT);
		HFONT hFont, oldFont;
		hFont = CreateFontW(16, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("¹ÙÅÁÃ¼"));
		oldFont = (HFONT)SelectObject(hdc, hFont);
	}
	if (Tbox)
	{
		TS.Draw(hdc, str, 1);
		switch (Tboxnum)
		{
		case 0:
			CUnitMange::a->Ares->UnitState.Update(10);
			CUnitMange::a->Ares->UnitState.Draw(hdc);
			break;
		case 1:
			CUnitMange::a->Genelu->UnitState.Update(10);
			CUnitMange::a->Genelu->UnitState.Draw(hdc);
			break;
		case 2:
			CUnitMange::a->Ares->UnitState.Update(10);
			CUnitMange::a->Ares->UnitState.Draw(hdc);
			break;
		case 3:
			CUnitMange::a->Ares->UnitState.Update(10);
			CUnitMange::a->Ares->UnitState.Draw(hdc);
			break;
		case 4:
			CUnitMange::a->Genelu->UnitState.Update(10);
			CUnitMange::a->Genelu->UnitState.Draw(hdc);
			break;
		case 5:
			CUnitMange::a->Genelu->UnitState.Update(10);
			CUnitMange::a->Genelu->UnitState.Draw(hdc);
			break;
		case 6:
			CUnitMange::a->Genelu->UnitState.Update(10);
			CUnitMange::a->Genelu->UnitState.Draw(hdc);
			break;
		case 7:
			break;
		default:
			break;
		}
	}
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
		FieldMap->CSB.mAlpha+=5;
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
	switch (left_right)
	{
	case(MK_LBUTTON):
		if (ClickEvent)
		{
			if (Tbox)
			{
				Tboxnum++;
			}
			else
			{
				tsno++;
				ClickEvent = false;
			}
		}
		break;
	default:
		break;
	}
}

void InGameIntro3::SetScene()
{
	
	str = new WCHAR[512];
	FieldMap = new CMap;
	FieldMap->SetMap(MAKEINTRESOURCE(IDB_GARSIACASTLE), L"IDB_GARSIACASTLE");
	FieldMap->CamPosY = 16 * 4;
	Subim = CImageFile::New(MAKEINTRESOURCE(IDB_SCREENFRAME), L"IDB_SCREENFRAME");
	Subsp.Set(0, 0, 0, 0, Subim, RGB(255, 0, 255), CSprite::DrawType_Transparent);
	submap.Set(FieldMap->PosX + 16, subcamPosy, 0, 0, FieldMap->MapImg, 0, CSprite::DrawType_Transparent);
	//FieldMap->CamPosY = -16*16;
	UI = CImageFile::New(MAKEINTRESOURCE(IDB_UI), L"IDB_UI");
	UIs.Set(0, 0, 0, 0, UI, RGB(255, 0, 255), CSprite::DrawType_Transparent);
	TS.Set(160, 191, 488, 256, 16);
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
	FieldMap->AddChar(18, 35, 2, 2, CUnitMange::a->Ares, L"a.SnoSTOP:3");
	FieldMap->AddChar(22, 25, 2, 2, CUnitMange::a->RockMan[0], L"a.SnoSTOP:0");
	FieldMap->AddChar(22, 23, 2, 2, CUnitMange::a->RockMan[1], L"a.SnoSTOP:0");
	FieldMap->AddChar(22, 21, 2, 2, CUnitMange::a->RockMan[2], L"a.SnoSTOP:0");
	FieldMap->AddChar(14, 25, 2, 2, CUnitMange::a->RockMan[3], L"a.SnoSTOP:0");
	FieldMap->AddChar(14, 23, 2, 2, CUnitMange::a->RockMan[4], L"a.SnoSTOP:0");
	FieldMap->AddChar(14, 21, 2, 2, CUnitMange::a->RockMan[5], L"a.SnoSTOP:0");
	for (int i = 0; i < 6; i++)
		CUnitMange::a->RockMan[i]->DrawUnit = false;
	//FieldMap->mCharacters[0]->DrawUnit = false;
}
