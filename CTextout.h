#pragma once
class CTextOut
{
public:
	int dx, dy, width, height, fontSize;
	
	
	HFONT FontInfo;
	
public:

	void Set(int dx, int dy, int w, int h, int fs);
	void OutPut(HDC hdc, LPCWSTR str);
	
	
};

//DT_CALCRECT
//DT_WORDBREAK
//DrawText 크기 반환
