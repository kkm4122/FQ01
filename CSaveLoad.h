#pragma once
#include "CImageFile.h"
#include "CSprite.h"
#include "IScene.h"
#include "CAnimation.h"
#include "CTextout.h"


class CSaveData;
class CImageFile;
class CSaveLoad :
    public IScene
{
public:
    CSaveLoad();
    ~CSaveLoad();

    virtual bool Sample() override;
    virtual bool isChanged() override;
    void onFrameMove() override;
    void onDraw(HDC hdc) override;
    //virtual void onMouseDown(UINT x, UINT y, UCHAR left_right) override;
    virtual void onMouseMove(UINT x, UINT y) override;
    virtual void onKeyDown(UINT virtual_key) override;
    virtual void onMouseDown(UINT x, UINT y, UINT left_right) override;
    virtual void SetScene() override;
public:
    CImageFile* SaveLoadImage;
    
  
    //CSprite     mAnim;
    CSprite		mBG;

    ANIM_FILE mCharFile;
    
    CFrameSprite mCharSprite;
    CTextOut asdf;

    int YboxPos = 0;
    bool NextScene = false;
    bool samplechange = false;
};

