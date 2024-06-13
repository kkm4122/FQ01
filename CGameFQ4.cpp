#include "pch.h"
#include "CIntroScene.h"
#include "CTitle.h"
#include "CSaveLoad.h"
#include "InGameIntro.h"
#include "InGameIntro2.h"
#include "InGameIntro3.h"
#include "CBattleScene.h"
#include "FieldBattle.h"
#include "CUnitMange.h"

#include "CGameFQ4.h"


CGameFQ4::~CGameFQ4()
{
	//CUnitMange::a->onDestroy();
	CImageFile::DestroyAll();
}

void CGameFQ4::OnCreate()
{
	CUnitMange::a->SetUnit();
	mIntroS = new CIntroScene;
	
	
	
	//mFieldBattle = new FieldBattle;
	//mGameIntro3 = new InGameIntro3;
	mBattleScene = new CBattleScene;
	//mCurrent = mIntroS;
	mCurrent = mBattleScene;
	//mCurrent = mFieldBattle;
	//mCurrent = mGameIntro3;
}

void CGameFQ4::OnDestroy()
{
	if (mBattleScene)delete mBattleScene;
	if (mGameIntro3)delete mGameIntro3;
	if (mGameIntro2)delete mGameIntro2;
	if (mGameIntro)delete mGameIntro;
	if (mSaveLoad)delete mSaveLoad;
	if (mTitle)delete mTitle;
	if (mIntroS)delete mIntroS;

}

void CGameFQ4::onChangeScene()
{
	
	if (mCurrent->isChanged())
	{
		
		if (mCurrent == mIntroS) 
		{
			mTitle = new CTitle; 
			mCurrent = mTitle;
		}
		else if (mCurrent == mTitle)
		{
			mSaveLoad = new CSaveLoad;
			mCurrent = mSaveLoad;
		}
		else if (mCurrent == mSaveLoad)
		{
			mGameIntro = new InGameIntro;
			mCurrent = mGameIntro;
		}
		else if (mCurrent == mGameIntro)
		{
			mGameIntro2 = new InGameIntro2;
			mCurrent = mGameIntro2;
		}
		else if (mCurrent == mGameIntro2)
		{
			mGameIntro3 = new InGameIntro3;
			mCurrent = mGameIntro3;
		}
	}
}

