#pragma once
#include "IGame.h"

class CIntroScene;
class CTitle;
class CSaveLoad;
class InGameIntro;
class InGameIntro2;
class InGameIntro3;
class CBattleScene;
class FieldBattle;
class CGameFQ4 :
    public IGame
{
public:
    ~CGameFQ4();
    void OnCreate();
    void OnDestroy();
    void onChangeScene();

    //virtual void onKeyDown(UINT virtual_key) override;
public:
    CIntroScene* mIntroS;
    CTitle* mTitle;
    CSaveLoad* mSaveLoad;
    InGameIntro* mGameIntro;
    InGameIntro2* mGameIntro2;
    InGameIntro3* mGameIntro3;
    CBattleScene* mBattleScene;
    FieldBattle* mFieldBattle;
};

