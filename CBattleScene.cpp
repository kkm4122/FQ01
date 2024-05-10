#include "pch.h"
#include "CMap.h"
#include "CUnitMange.h"
#include "CImageFile.h"
#include "CBattleScene.h"
#define VK_W 87
#define VK_S 83
#define VK_A 65
#define VK_D 68
CBattleScene::CBattleScene()
{
    //BG_FEILD
    FieldMap = new CMap;
    FieldMap->SetMap(MAKEINTRESOURCE(BG_FEILD), L"BG_FEILD");
    /*FieldMap->posX = 16;
    FieldMap->posY = 48;
    FieldMap->MapImg = CImageFile::New(MAKEINTRESOURCE(BG_FEILD), L"BG_Field");
    FieldMap->Mapobj.Set(0, 0, 0, 0, FieldMap->MapImg, 0, CSprite::DrawType_Draw);*/
    UI = CImageFile::New(MAKEINTRESOURCE(IDB_UI), L"IDB_UI");
    UIs.Set(0, 0, 0, 0, UI, RGB(255, 0, 255), CSprite::DrawType_Transparent);
    FieldMap->AddChar(3, 3, 2, 1, CUnitMange::a->KarionSoldier[10], L"a.Sno:0");
    FieldMap->AddChar(30, 5, 2, 2, CUnitMange::a->GarshiaSoldier[0], L"a.SnoSTOP:0");
    FieldMap->AddChar(20, 10, 2, 2, CUnitMange::a->Aerain, L"a.SnoSTOP:0");
   // FieldMap->mCharacters[0]->TileSet(3, 3, L"a.Sno:0");
    
    for (int i = 0; i < 8; i++)
    {
        FieldMap->AddChar(i+5, 5, 1, 100, CUnitMange::a->BlackObj[i], L"a.SnoSTOP:0");
    }
    for (int i = 0; i < 8; i++)
    {
        FieldMap->AddChar(12, i+5, 1, 100, CUnitMange::a->BlackObj[9+i], L"a.SnoSTOP:0");
    }
    for (int i = 0; i < 8; i++)
    {
        FieldMap->AddChar(15, i, 1, 100, CUnitMange::a->BlackObj[16+i], L"a.SnoSTOP:0");
    }
}

CBattleScene::~CBattleScene()
{
    delete FieldMap;
}

bool CBattleScene::Sample()
{
    return false;
}

bool CBattleScene::isChanged()
{
    return false;
}

void CBattleScene::onFrameMove()
{
    FieldMap->Update();
    framecount++;
    if (framecount % 10 == 0)
    {
        framecount = 0;
       // FieldMap->mCharacters[1]->DirWalk(FieldMap->mCharacters[0]);
        FieldMap->mCharacters[1]->WalkToAstar(FieldMap, FieldMap->mCharacters[2]);
        FieldMap->mCharacters[2]->WalkToAstar(FieldMap, FieldMap->mCharacters[0]);
    }
}

void CBattleScene::onDraw(HDC hdc)
{
    FieldMap->Draw(hdc);
    UIs.Draw(hdc);
}

void CBattleScene::onKeyDown(UINT virtual_key)
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
        FieldMap->CamPosX -= 16;
        break;
    case(VK_RIGHT):
        FieldMap->CamPosX += 16;
        break;
    case(VK_W):
        FieldMap->mCharacters[0]->WalkOneTile(FieldMap,4);
        break;
    case(VK_S):
        FieldMap->mCharacters[0]->WalkOneTile(FieldMap, 5);
        break;
    case(VK_A):
        FieldMap->mCharacters[0]->WalkOneTile(FieldMap, 6);
        break;
    case(VK_D):
        FieldMap->mCharacters[0]->WalkOneTile(FieldMap, 7);
        break;
    case(VK_RETURN):
        FieldMap->mCharacters[0]->MoveTo(2, 3);
        break;
    default:
        break;
    }
    //case()
}

void CBattleScene::onMouseDown(UINT x, UINT y, UINT left_right)
{
}
