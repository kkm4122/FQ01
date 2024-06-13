#include "pch.h"
#include "CMap.h"
#include "CImageFile.h"
#include "CApplication.h"
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
    switch (tsno)
    {
    case 0:
        dt++;
        if (dt % 5 == 0)
        {
            if (FieldMap->CamPosY != 48)
            {
                FieldMap->CamPosY += 16;
            }
            else
            {
                tsno++;
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
            tsno++;
        }
        case 3:
            dt++;
            if (dt % 10 == 0)
            {
                for (CUnit* ic : FieldMap->mCharacters)
                {
                    ic->WalkToAstar(FieldMap,ic->Target);
                }
                //WalkToAstar(FieldMap,)
            }
            break;
    default:
        break;
    }
}

void FieldBattle::onDraw(HDC hdc)
{
    FieldMap->Draw(hdc);
    UIs.Draw(hdc);
    {//폰트 설정
        LoadString(CApplication::theApp->mhInst, IDS_CUT4_1 + Tboxnum, str, 512);//stringTable에서 대사스크립트 가져옴
        SetBkMode(hdc, TRANSPARENT);
        HFONT hFont, oldFont;
        hFont = CreateFontW(16, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("바탕체"));
        oldFont = (HFONT)SelectObject(hdc, hFont);
    }
    if (Tbox)
    {
        
        switch (Tboxnum)
        {
        case 0:
            TS.Draw(hdc, str, 2);
            CUnitMange::a->GarshiaCom[0]->UnitState.Update(10);
            CUnitMange::a->GarshiaCom[0]->UnitState.Draw(hdc);
            break;
        case 1:
            TS.Draw(hdc, str, 2);
            CUnitMange::a->HActum->UnitState.Update(10);
            CUnitMange::a->HActum->UnitState.Draw(hdc);
            break;
        case 2:
            TS.Draw(hdc, str, 1);
            CUnitMange::a->KarionPawn[0]->UnitState.Update(10);
            CUnitMange::a->KarionPawn[0]->UnitState.Draw(hdc);
            break;
        default:
            break;
        }
    }
}

void FieldBattle::onKeyDown(UINT virtual_key)
{
    switch (virtual_key)
    {
    case(VK_S):
        FieldMap->CamPosY += 16;
        break;
    case(VK_W):
        FieldMap->CamPosY -= 16;
        break;
    default:
        break;
    }

}

void FieldBattle::SetScene()
{
    str = new WCHAR[512];
    TS.Set(160, 191, 488, 256, 16);
    FieldMap = new CMap;
    FieldMap->SetMap(MAKEINTRESOURCE(BG_FEILD), L"BG_FEILD");
    FieldMap->CamPosY -= 8*16;
    UI = CImageFile::New(MAKEINTRESOURCE(IDB_UI), L"IDB_UI");
    UIs.Set(0, 0, 0, 0, UI, RGB(255, 0, 255), CSprite::DrawType_Transparent);
    {//왼쪽 병사 오른쪽 주시 0~6
        FieldMap->AddChar(5, 6, 2, 1, CUnitMange::a->GarshiaSoldier[0], L"a.SnoSTOP:2");
        FieldMap->AddChar(5, 10, 2, 1, CUnitMange::a->GarshiaSoldier[1], L"a.SnoSTOP:2");
        FieldMap->AddChar(5, 13, 2, 1, CUnitMange::a->GarshiaSoldier[2], L"a.SnoSTOP:2");
        FieldMap->AddChar(2, 9, 2, 1, CUnitMange::a->GarshiaSoldier[3], L"a.SnoSTOP:2");
        FieldMap->AddChar(8, 9, 2, 1, CUnitMange::a->GarshiaSoldier[4], L"a.SnoSTOP:2");
        FieldMap->AddChar(2, 12, 2, 1, CUnitMange::a->GarshiaSoldier[5], L"a.SnoSTOP:2");
        FieldMap->AddChar(2, 15, 2, 1, CUnitMange::a->GarshiaSoldier[6], L"a.SnoSTOP:2");
        
    }
    {//왼쪽병사 아래쪽 주시 7~11
        FieldMap->AddChar(8, 6, 2, 1, CUnitMange::a->GarshiaSoldier[7], L"a.SnoSTOP:0");
        FieldMap->AddChar(11, 6, 2, 1, CUnitMange::a->GarshiaSoldier[8], L"a.SnoSTOP:0");
        FieldMap->AddChar(14, 6, 2, 1, CUnitMange::a->GarshiaSoldier[9], L"a.SnoSTOP:0");
        FieldMap->AddChar(12, 9, 2, 1, CUnitMange::a->GarshiaSoldier[10], L"a.SnoSTOP:0");
        FieldMap->AddChar(16, 8, 2, 1, CUnitMange::a->GarshiaSoldier[11], L"a.SnoSTOP:0");
    }
    {//오른쪽 병사 아래쪽 주시    
        FieldMap->AddChar(19, 8, 2, 1, CUnitMange::a->GarshiaSoldier[12], L"a.SnoSTOP:0");
        FieldMap->AddChar(21, 6, 2, 1, CUnitMange::a->GarshiaSoldier[13], L"a.SnoSTOP:0");
        FieldMap->AddChar(24, 6, 2, 1, CUnitMange::a->GarshiaSoldier[14], L"a.SnoSTOP:0");
        FieldMap->AddChar(27, 6, 2, 1, CUnitMange::a->GarshiaSoldier[15], L"a.SnoSTOP:0");
        FieldMap->AddChar(23, 9, 2, 1, CUnitMange::a->GarshiaSoldier[16], L"a.SnoSTOP:0");
    }
    {//오른쪽 병사 오른쪽 주시
        FieldMap->AddChar(27, 9, 2, 1, CUnitMange::a->GarshiaSoldier[17], L"a.SnoSTOP:1");
        FieldMap->AddChar(30, 6, 2, 1, CUnitMange::a->GarshiaSoldier[18], L"a.SnoSTOP:1");
        FieldMap->AddChar(30, 10, 2, 1, CUnitMange::a->GarshiaSoldier[19], L"a.SnoSTOP:1");
        FieldMap->AddChar(30, 13, 2, 1, CUnitMange::a->GarshiaSoldier[20], L"a.SnoSTOP:1");
        FieldMap->AddChar(33, 9, 2, 1, CUnitMange::a->GarshiaSoldier[21], L"a.SnoSTOP:1");
        FieldMap->AddChar(33, 12, 2, 1, CUnitMange::a->GarshiaSoldier[22], L"a.SnoSTOP:1");
        FieldMap->AddChar(33, 15, 2, 1, CUnitMange::a->GarshiaSoldier[23], L"a.SnoSTOP:1");

    }
    {//궁병 24~29
        FieldMap->AddChar(8, 3, 2, 1, CUnitMange::a->Garshiaarcher[0], L"a.SnoSTOP:0");
        FieldMap->AddChar(11, 3, 2, 1, CUnitMange::a->Garshiaarcher[1], L"a.SnoSTOP:0");
        FieldMap->AddChar(14, 3, 2, 1, CUnitMange::a->Garshiaarcher[2], L"a.SnoSTOP:0");
        FieldMap->AddChar(21, 3, 2, 1, CUnitMange::a->Garshiaarcher[3], L"a.SnoSTOP:0");
        FieldMap->AddChar(24, 3, 2, 1, CUnitMange::a->Garshiaarcher[4], L"a.SnoSTOP:0");
        FieldMap->AddChar(27, 3, 2, 1, CUnitMange::a->Garshiaarcher[5], L"a.SnoSTOP:0");
    }
    {//가르시아 기마병30~31
        FieldMap->AddChar(21, 12, 3, 1, CUnitMange::a->GarshiaH[0], L"a.SnoSTOP:0");
        FieldMap->AddChar(13, 12, 3, 1, CUnitMange::a->GarshiaH[1], L"a.SnoSTOP:0");
    }
    {//카리온 폰32~37
        FieldMap->AddChar(13, 17, 2, 2, CUnitMange::a->KarionPawn[0], L"a.SnoSTOP:2");
        FieldMap->AddChar(9, 17, 2, 2, CUnitMange::a->KarionPawn[1], L"a.SnoSTOP:2");
        FieldMap->AddChar(11, 20, 2, 2, CUnitMange::a->KarionPawn[2], L"a.SnoSTOP:2");
        FieldMap->AddChar(22, 17, 2, 2, CUnitMange::a->KarionPawn[3], L"a.SnoSTOP:1");
        FieldMap->AddChar(26, 17, 2, 2, CUnitMange::a->KarionPawn[4], L"a.SnoSTOP:1");
        FieldMap->AddChar(24, 20, 2, 2, CUnitMange::a->KarionPawn[5], L"a.SnoSTOP:1");
    }
    FieldMap->AddChar(17, 4, 3, 1, CUnitMange::a->GarshiaCom[0], L"a.SnoSTOP:0");//38
    FieldMap->AddChar(17, 16, 3, 2, CUnitMange::a->HActum,L"a.SnoSTOP:3");//39
    for (CUnit* ic : FieldMap->mCharacters)
    {
        ic->searchUnit(FieldMap);
    }
}

void FieldBattle::onMouseDown(UINT x, UINT y, UINT left_right)
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
