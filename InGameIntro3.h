#pragma once
#include "CSprite.h"
#include "CUnit.h"

#include "IScene.h"

#include "CTextout.h"
#include"resource.h"

#include "IScene.h"
class CMap;
class InGameIntro3 :
    public IScene
{
public:
	InGameIntro3();
	~InGameIntro3();
	virtual bool Sample() override;
	virtual bool isChanged() override;
	virtual void onFrameMove() override;
	virtual void onDraw(HDC hdc) override;
	virtual void onKeyDown(UINT virtual_key)override;

	virtual void onMouseDown(UINT x, UINT y, UINT left_right) override;
	CMap* FieldMap;
	CImageFile* UI;
	CSprite UIs;
	int framecount = 0;
};

