#pragma once
class CImageFile;

class CSprite
{
public:
	int mDestX;
	int mDestY;
	int mDestWidth;
	int mDestHeight;

	int mSrcX;
	int mSrcY;
	int mSrcWidth;
	int mSrcHeight;

	UINT mTransColor;		//크로마키 색상
	CImageFile* mImgFile;	
	BYTE mAlpha;			
	
public:
	enum TDrawType{
		DrawType_Transparent,	//특정 색상을 제외하고 그리기
		DrawType_Draw,			
		DrawType_AlphaBlend,	//반투명하게 그리기
		DrawType_FadeInOut		//
	};
	TDrawType mDrawType;



public:
	CSprite() : mAlpha(0xFF) {};
	void Set(int dx, int dy, int sx, int sy, CImageFile* img, UINT color, TDrawType dt);
	void Draw(HDC hdc);

};

