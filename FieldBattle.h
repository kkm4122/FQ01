#pragma once
#include "CSprite.h"
#include "CTextout.h"
#include"resource.h"
#include "IScene.h"
class FieldBattle :
    public IScene
{
public:
	FieldBattle();
	~FieldBattle();
	virtual bool Sample() override;
	virtual bool isChanged() override;
	virtual void onFrameMove() override;
	virtual void onDraw(HDC hdc) override;
	virtual void onKeyDown(UINT virtual_key)override;
	virtual void SetScene()override;
	virtual void onMouseDown(UINT x, UINT y, UINT left_right) override;
	CMap* FieldMap;
	CImageFile* UI;
	CSprite UIs;
	int framecount = 0;
};

