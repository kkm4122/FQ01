#pragma once
#include "CSprite.h"
#include "IScene.h"
#include"resource.h"



class CImageFile;
class CIntroScene :
    public IScene
{
public:
	CIntroScene();
	~CIntroScene();
	virtual bool Sample() override;
	virtual bool isChanged() override;
	virtual void onFrameMove() override;
	virtual void onDraw(HDC hdc) override;
	virtual void onKeyDown(UINT virtual_key)override;
	
public:
	CImageFile* IntroImage[9];
	CImageFile* TitleImage;
	CImageFile* Fadeout;
	CSprite		mBG;
	CSprite		Fout;
	int Image_num = IDB_INTRO1;
	int Intro_num = 0;
	int Text_num = 0;
	int Textframe = 0;
	bool Fadein = true;
	bool NextScene = false;
	bool samplechange = false;
};

