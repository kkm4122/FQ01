#include "pch.h"
#include "CImagefile.h"
#include "CSprite.h"

void CSprite::Set(int dx, int dy, int sx, int sy, CImageFile* img, UINT color, TDrawType dt)
{
	mDestX = dx;
	mDestY = dy;
	mSrcX = sx;
	mSrcY = sy;
	mSrcHeight = img->Height();
	mSrcWidth = img->Width();
	mTransColor = color;
	mDrawType = dt;
	mImgFile = img;

}

void CSprite::Draw(HDC hdc)
{
	switch (mDrawType)
	{
	case(DrawType_Draw):
			mImgFile->Draw(hdc, mDestX, mDestY,
								mSrcX, mSrcY,
								mSrcWidth, mSrcHeight);
		break;
	case(DrawType_Transparent):
		mImgFile->TransDraw(hdc, mDestX, mDestY,
								 mSrcX, mSrcY, mSrcWidth, mSrcHeight,
								 mTransColor);
		break;
	case(DrawType_AlphaBlend):
		mImgFile->AlphaDraw(hdc, mDestX, mDestY,
			mSrcX, mSrcY, mSrcWidth, mSrcHeight,
			mAlpha);
		break;
	case(DrawType_FadeInOut):
		mImgFile->FadeInOut(hdc, mDestX, mDestY,
			mSrcX, mSrcY, mSrcWidth, mSrcHeight,
			mAlpha);
		break;
	}
	
}
