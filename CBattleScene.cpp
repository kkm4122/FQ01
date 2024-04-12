#include "pch.h"
#include "CMap.h"
#include "CUnitMange.h"
#include "CImageFile.h"
#include "CBattleScene.h"

CBattleScene::CBattleScene()
{

    FieldMap = new CMap;
    FieldMap->SetMap(MAKEINTRESOURCE(BG_FEILD), L"BG_FEILD");
    /*FieldMap->posX = 16;
    FieldMap->posY = 48;
    FieldMap->MapImg = CImageFile::New(MAKEINTRESOURCE(BG_FEILD), L"BG_Field");
    FieldMap->Mapobj.Set(0, 0, 0, 0, FieldMap->MapImg, 0, CSprite::DrawType_Draw);*/
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
    FieldMap->Mapobj.Draw(hdc);
}

void CBattleScene::onKeyDown(UINT virtual_key)
{
    switch (virtual_key)
    {
    case(VK_UP):
        FieldMap->Mapobj.mDestY-=16;
        break;
    case(VK_DOWN):
        FieldMap->Mapobj.mDestY += 16;
        break;
    default:
        break;
    }
}

void CBattleScene::onMouseDown(UINT x, UINT y, UINT left_right)
{
}
