#include "pch.h"
#include "resource.h"
#include "CImageFile.h"
#include "CTitle.h"

CTitle::CTitle()
{
	TitleImage = new CImageFile(MAKEINTRESOURCE(IDB_TITLE),L"IDB_TITLE");
	Fadeout = new CImageFile(MAKEINTRESOURCE(IDB_BITMAP1),L"FADEOUT");
	Fout.Set(0, 0, 0, 0, Fadeout, 0, CSprite::DrawType_AlphaBlend);
	Fout.mAlpha = 255;
	mBG.Set(0, 0, 0, 0, TitleImage, 0, CSprite::DrawType_Draw);
}

CTitle::~CTitle()
{
	delete TitleImage;
	delete Fadeout;
}

bool CTitle::Sample()
{
	return samplechange;
}

bool CTitle::isChanged()
{
	return NextScene;
}

void CTitle::onFrameMove()
{
	if (Fadein == true && Fout.mAlpha > 0)
	{
		Fout.mAlpha -= 5;
		if (Fout.mAlpha <= 0) {
			Fout.mAlpha = 0;
			Fadein = false;
		}
	}
}

void CTitle::onDraw(HDC hdc)
{
	mBG.Draw(hdc);
	
}

void CTitle::onKeyDown(UINT virtual_key)
{
	switch (virtual_key)
	{
	case(VK_RETURN):
		NextScene = true;
		break;
	case(VK_SPACE):
		samplechange = true;
		break;
	default:
		break;
	}
}

void CTitle::SetScene()
{
}

