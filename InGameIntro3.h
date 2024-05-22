#pragma once
#include "CSprite.h"
#include "CUnit.h"

#include "IScene.h"

#include "CTextout.h"
#include"resource.h"
#include "CScreen.h"
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
	virtual void SetScene() override;
	CImageFile* Subim;
	CSprite Subsp;
	CMap* FieldMap;
	CSprite submap;
	CImageFile* UI;
	CSprite UIs;
	int framecount = 0;
	int subcamPosy = 8*16;
	int subHeight = 360-120-48;
};

