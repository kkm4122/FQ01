#pragma once
#include "CSprite.h"
#include "CUnit.h"
#include "CMap.h"
#include "IScene.h"
//#include "CScreen.h"
#include "CTextout.h"
#include"resource.h"
/*iscene���
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
	//CImageFile* SubScene;//���� ��ǥ�� �ʿ� ����!
	CImageFile* UI;
	CImageFile* Textwin;
	CImageFile* CharTextwin;
	CImageFile* SubScrWin;
	//CImageFile* obj[28];
	CUnit obj[27];
	CSprite mBG;		//set���� �Ű������� �� �޾ƾ� �ϱ⶧���� 
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

	int tsno = 0;//�̺�Ʈ ����  ��ȣ
	bool Tbox = false;
	bool anim = false;
	int Tboxnum = 0;
};

