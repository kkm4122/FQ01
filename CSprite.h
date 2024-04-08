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

	UINT mTransColor;		//ũ�θ�Ű ����
	CImageFile* mImgFile;	
	BYTE mAlpha;			
	
public:
	enum TDrawType{
		DrawType_Transparent,	//Ư�� ������ �����ϰ� �׸���
		DrawType_Draw,			
		DrawType_AlphaBlend,	//�������ϰ� �׸���
		DrawType_FadeInOut		//
	};
	TDrawType mDrawType;



public:
	CSprite() : mAlpha(0xFF) {};
	void Set(int dx, int dy, int sx, int sy, CImageFile* img, UINT color, TDrawType dt);
	void Draw(HDC hdc);

};

