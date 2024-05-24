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
public:
	CImageFile* Subim;
	CSprite Subsp;
	CMap* FieldMap;
	CSprite submap;
	CImageFile* UI;
	CSprite UIs;
	CTextOut TS;
	WCHAR* str;
	int framecount = 0;
	int subcamPosy = 9*16;
	int subHeight = 360-120-48+32+(16*9);


	bool NextScene = false;
	bool substart = false;
	int tsno = 0;//이벤트 순서  번호
	bool Tbox = false;
	bool anim = false;
	bool ClickEvent = false;
	int Tboxnum = 0;//대사 스크립트 번호
	int CTboxnum = 0;
	int dt = 0;
};

