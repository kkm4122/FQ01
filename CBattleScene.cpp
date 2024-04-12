#include "pch.h"
#include "CMap.h"
#include "CUnitMange.h"
#include "CImageFile.h"
#include "CBattleScene.h"
#define VK_W 87
CBattleScene::CBattleScene()
{

    FieldMap = new CMap;
    FieldMap->SetMap(MAKEINTRESOURCE(BG_FEILD), L"BG_FEILD");
    /*FieldMap->posX = 16;
    FieldMap->posY = 48;
    FieldMap->MapImg = CImageFile::New(MAKEINTRESOURCE(BG_FEILD), L"BG_Field");
    FieldMap->Mapobj.Set(0, 0, 0, 0, FieldMap->MapImg, 0, CSprite::DrawType_Draw);*/
    UI = CImageFile::New(MAKEINTRESOURCE(IDB_UI), L"IDB_UI");
    UIs.Set(0, 0, 0, 0, UI, RGB(255, 0, 255), CSprite::DrawType_Transparent);
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
        FieldMap->Mapobj.mDestY -= 16;
        break;
    case(VK_DOWN):
        FieldMap->Mapobj.mDestY += 16;
        break;
    case(VK_LEFT):
        FieldMap->Mapobj.mDestX -= 16;
        break;
    case(VK_RIGHT):
        FieldMap->Mapobj.mDestX += 16;
        break;
    case(VK_W):
        FieldMap->Mapobj.mDestY -= 16;
        break;
    default:
        break;
    }
    //case()
}

void CBattleScene::onMouseDown(UINT x, UINT y, UINT left_right)
{
}
