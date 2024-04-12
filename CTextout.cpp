#include "pch.h"
#include "CTextout.h"

void CTextOut::Set(int dx, int dy, int w, int h, int fs)
{
	this->dx = dx;
	this->dy = dy;
	width = w;
	height = h;
	fontSize = fs;
	
}

void CTextOut::OutPut(HDC hdc,LPCWSTR str)
{
	HFONT hFont, oldFont;
	hFont = CreateFontW(fontSize, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("πŸ≈¡√º"));
	oldFont = (HFONT)SelectObject(hdc, hFont);
	RECT Tbox = { dx,dy,width,height };
	if (DrawText(hdc, str, wcslen(str), &Tbox, DT_WORDBREAK))
	{
		a = DrawText(hdc, str, wcslen(str), &Tbox, DT_WORDBREAK);
	}
	//DrawText(hdc, str, wcslen(str), &Tbox, DT_CALCRECT);
	DrawText(hdc, str, wcslen(str), &Tbox, DT_WORDBREAK);
	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}