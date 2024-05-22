#pragma once
#include "CSprite.h"
#include "CUnit.h"
#include "CMap.h"
#include "IScene.h"

#include "CTextout.h"
#include"resource.h"
class CImageFile;
class InGameIntro2 :
    public IScene
{
public:
	InGameIntro2();
	~InGameIntro2();
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
	
	CSprite mBG;		//set���� �Ű������� �� �޾ƾ� �ϱ⶧���� 
	
	CSprite UIs;
	

	CSprite TW;
	CSprite CTW;

	WCHAR* str;
	CTextOut TS;
	CTextOut TS2;


	int subPosx = 0;
	int subPosy = 0;
	bool NextScene = false;

	bool substart = false;

	int tsno = 0;//�̺�Ʈ ����  ��ȣ
	bool Tbox = false;
	bool anim = false;
	bool ClickEvent = true;
	int Tboxnum = 0;//��� ��ũ��Ʈ ��ȣ
	int CTboxnum = 0;
	int dt = 0;
};

