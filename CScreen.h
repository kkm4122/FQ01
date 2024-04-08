#pragma once
#include "CMemoryBitmap.h"

class CScreen
	: public CMemoryBitmap
{
public:
	CScreen(HDC hdcWnd, int width, int height)//CMemoryBitmap의 매개변수를 받기 위해 CScreen생성시 매개변수 설정
		: CMemoryBitmap(hdcWnd, width, height) {}
	CScreen();
	CScreen(int width, int height);
	//~CScreen();

	
	void Draw(HDC hdc);
	
	void Draw(HDC hdc, int dest_x, int dest_y, int width, int height);
};

