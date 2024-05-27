#include "pch.h"

#include <string.h>
#include "IScene.h"
#include "CImageFile.h"
#include "resource.h"
#include "CTextout.h"


CTextOut::~CTextOut()
{
	delete CT;
}

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
	
	//if (DrawText(hdc, str, wcslen(str), &Tbox, DT_WORDBREAK))
	{
		a = DrawText(hdc, str, wcslen(str), &Tbox, DT_WORDBREAK);
	}
	//DrawText(hdc, str, wcslen(str), &Tbox, DT_CALCRECT);
	//DrawText(hdc, str, wcslen(str), &Tbox, DT_WORDBREAK);
	 CHAR astr[23]; 
	 sprintf_s(astr, 23, "font height: %d	\n", a);
	 OutputDebugStringA(astr);
	//sprintf_s(str, 100, "x: %d	y: %d\n", x,y);
	

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

void CTextOut::Draw(HDC hdc, LPCWSTR str, int charsize)
{
	HFONT hFont, oldFont;
	hFont = CreateFontW(fontSize, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("πŸ≈¡√º"));
	oldFont = (HFONT)SelectObject(hdc, hFont);
	RECT Tbox = { dx,dy,width,height };
	RECT Tbox2 = { dx + 1,dy,width + 1,height };
	a = DrawText(hdc, str, wcslen(str), &Tbox, DT_WORDBREAK);
	UIDraw(hdc, charsize);
	//b = (CTS.mImgFile->Height()-a)/4;
	
	//DrawText(hdc, str, wcslen(str), &Tbox, DT_CALCRECT);
	//DrawText(hdc, str, wcslen(str), &Tbox, DT_WORDBREAK);
	DrawText(hdc, str, wcslen(str), &Tbox, DT_WORDBREAK); 
	DrawText(hdc, str, wcslen(str), &Tbox2, DT_WORDBREAK);
	//sprintf_s(str, 100, "x: %d	y: %d\n", x,y);


	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

void CTextOut::UIDraw(HDC hdc, int Charsize)
{
	
	switch (Charsize)//¿Ø¥÷ Ω∫«¡∂Û¿Ã∆Æ ≈©±‚
	{
	case 1:
		switch (a)
		{
		case 16:CT = CImageFile::New(MAKEINTRESOURCE(TUI_1_1), L"TUI_1_1");
			break;
		
		case 32:CT = CImageFile::New(MAKEINTRESOURCE(TUI_2_1), L"TUI_2_1");
			break;
		case 48:CT = CImageFile::New(MAKEINTRESOURCE(TUI_3_1), L"TUI_3_1");
			break;
		case 64:CT = CImageFile::New(MAKEINTRESOURCE(TUI_4_1), L"TUI_4_1");
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (a)
		{
		case 16:CT = CImageFile::New(MAKEINTRESOURCE(TUI_1_2), L"TUI_1_2");
			break;
		case 32:CT = CImageFile::New(MAKEINTRESOURCE(TUI_2_2), L"TUI_2_2");
			break;
		case 48:CT = CImageFile::New(MAKEINTRESOURCE(TUI_3_2), L"TUI_3_2");
			break;
		case 64:CT = CImageFile::New(MAKEINTRESOURCE(TUI_4_2), L"TUI_4_2");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	CTS.Set(81, 175, 0, 0, CT, RGB(255, 0, 255), CSprite::DrawType_Transparent);
	CTS.Draw(hdc);
}
