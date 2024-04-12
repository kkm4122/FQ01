#include "pch.h"
#include "CMap.h"
#include "CBattleScene.h"

CBattleScene::CBattleScene()
{
    FieldMap = new CMap;
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
}

void CBattleScene::onKeyDown(UINT virtual_key)
{
}

void CBattleScene::onMouseDown(UINT x, UINT y, UINT left_right)
{
}
