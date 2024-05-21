#include "pch.h"
#include "CIntroScene.h"
#include "CTitle.h"
#include "CSaveLoad.h"
#include "InGameIntro.h"
#include "InGameIntro2.h"
#include "InGameIntro3.h"
#include "CBattleScene.h"
#include "CUnitMange.h"
#include "CGameFQ4.h"


CGameFQ4::~CGameFQ4()
{
	CImageFile::DestroyAll();
}

void CGameFQ4::OnCreate()
{
	CUnitMange::a->SetUnit();
	mIntroS = new CIntroScene;
	mTitle = new CTitle;
	mSaveLoad = new CSaveLoad;
	mGameIntro = new InGameIntro;
	mGameIntro2 = new InGameIntro2;
	mGameIntro3 = new InGameIntro3;
	//mBattleScene = new CBattleScene;
	//mCurrent = mIntroS;
	//mCurrent = mBattleScene;7
	mCurrent = mGameIntro;
}

void CGameFQ4::OnDestroy()
{
	delete mBattleScene;
	delete mGameIntro3;
	delete mGameIntro2;
	delete mGameIntro;
	delete mSaveLoad;
	delete mTitle;
	delete mIntroS;

}

void CGameFQ4::onChangeScene()
{
	if (mCurrent->Sample())
	{
		mCurrent = mGameIntro2;
	}
	if (mCurrent->isChanged())
	{
		
		if (mCurrent == mIntroS) { mCurrent = mTitle; }
		else if (mCurrent == mTitle) { mCurrent = mSaveLoad; }
		else if (mCurrent == mSaveLoad) { mCurrent = mGameIntro; }
		else if (mCurrent == mGameIntro){ mCurrent = mGameIntro2; }
		else if (mCurrent == mGameIntro2) { mCurrent = mGameIntro3; }
	}
}

