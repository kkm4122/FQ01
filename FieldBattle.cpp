#include "pch.h"
#include "CMap.h"
#include "CImageFile.h"
#include "FieldBattle.h"
#define VK_W 87
#define VK_S 83
#define VK_A 65
#define VK_D 68
FieldBattle::FieldBattle()
{
    SetScene();
}

FieldBattle::~FieldBattle()
{
}

bool FieldBattle::Sample()
{
    return false;
}

bool FieldBattle::isChanged()
{
    return false;
}

void FieldBattle::onFrameMove()
{
    FieldMap->Update();
}

void FieldBattle::onDraw(HDC hdc)
{
    FieldMap->Draw(hdc);
    UIs.Draw(hdc);
}

void FieldBattle::onKeyDown(UINT virtual_key)
{
    switch (virtual_key)
    {
    case(VK_S):
        FieldMap->CamPosY += 16;
        break;
    default:
        break;
    }

}

void FieldBattle::SetScene()
{
    FieldMap = new CMap;
    FieldMap->SetMap(MAKEINTRESOURCE(BG_FEILD), L"BG_FEILD");
    //FieldMap->CamPosY -= 8*16;
    UI = CImageFile::New(MAKEINTRESOURCE(IDB_UI), L"IDB_UI");
    UIs.Set(0, 0, 0, 0, UI, RGB(255, 0, 255), CSprite::DrawType_Transparent);
    {//¿ÞÂÊ º´»ç
        FieldMap->AddChar(5, 6, 2, 2, CUnitMange::a->GarshiaSoldier[0], L"a.SnoSTOP:2");
        FieldMap->AddChar(5, 10, 2, 2, CUnitMange::a->GarshiaSoldier[1], L"a.SnoSTOP:2");
        FieldMap->AddChar(5, 13, 2, 2, CUnitMange::a->GarshiaSoldier[2], L"a.SnoSTOP:2");
        FieldMap->AddChar(2, 9, 2, 2, CUnitMange::a->GarshiaSoldier[3], L"a.SnoSTOP:2");
        FieldMap->AddChar(8, 9, 2, 2, CUnitMange::a->GarshiaSoldier[4], L"a.SnoSTOP:2");
        FieldMap->AddChar(2, 12, 2, 2, CUnitMange::a->GarshiaSoldier[5], L"a.SnoSTOP:2");
        FieldMap->AddChar(2, 15, 2, 2, CUnitMange::a->GarshiaSoldier[6], L"a.SnoSTOP:2");
    }
}

void FieldBattle::onMouseDown(UINT x, UINT y, UINT left_right)
{
}
