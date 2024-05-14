#pragma once
#include "CSprite.h"
class CImageFile;

class CTextOut
{
public:
	int dx, dy, width, height, fontSize;
	
	int a;
	HFONT FontInfo;
	
public:

	void Set(int dx, int dy, int w, int h, int fs);
	void OutPut(HDC hdc, LPCWSTR str);
	CImageFile* Textwin[2];
	void Draw(HDC hdc, LPCWSTR str, int a);
};

//DT_CALCRECT
//DT_WORDBREAK
//DrawText 크기 반환
