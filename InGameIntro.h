#pragma once
#include "CSprite.h"
#include "CUnit.h"
#include "CMap.h"
#include "IScene.h"
//#include "CScreen.h"
#include "CTextout.h"
#include"resource.h"
/*iscene상속
iscene	-scene	-map
		-unit-char
		-unit-npc*/
//class CScreen;
class CImageFile;

class InGameIntro :
    public IScene
{
public:
	InGameIntro();
	~InGameIntro();
	virtual bool Sample() override;
	virtual bool isChanged() override;
	virtual void onFrameMove() override;
	virtual void onDraw(HDC hdc) override;
	virtual void onKeyDown(UINT virtual_key)override;

	virtual void onMouseDown(UINT x, UINT y, UINT left_right) override;
	virtual void SetScene() override;
public:
	CMap MainMap;
	//CImageFile* SubScene;//서브 좌표는 필요 없다!
	CImageFile* UI;
	CImageFile* Textwin;
	CImageFile* CharTextwin;
	CImageFile* SubScrWin;
	//CImageFile* obj[28];
	CUnit obj[27];
	CSprite mBG;		//set으로 매개변수를 다 받아야 하기때문에 
	CSprite sSc;
	CSprite UIs;
	CSprite sScWin;
	
	CSprite TW;
	CSprite CTW;
	CSprite CTWC;
	WCHAR* str;
	CSprite Sobj[27];
	CSprite SWobj[6];
	CTextOut TS;
	CTextOut TS2;
	

	int subPosx=0;
	int subPosy=0;
	bool NextScene = false;
	bool samplechange = false;

	bool substart = false;

	int tsno = 0;//이벤트 순서  번호
	bool Tbox = false;
	bool anim = false;
	int Tboxnum = 0;
};

