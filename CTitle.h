#pragma once
#include "CSprite.h"
#include "IScene.h"
#include"resource.h"

class CImageFile;
class CTitle :
    public IScene
{
public:
	CTitle();
	~CTitle();
	virtual bool Sample() override;
	virtual bool isChanged() override;
	virtual void onFrameMove() override;
	virtual void onDraw(HDC hdc) override;
	virtual void onKeyDown(UINT virtual_key)override;
	virtual void SetScene() override;
public:
	CImageFile* TitleImage;
	CImageFile* Fadeout;
	CSprite		mBG;
	CSprite		Fout;

	bool Fadein = true;
	bool NextScene = false;
	bool samplechange = false;
};

