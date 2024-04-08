#pragma once
#include "CMemoryBitmap.h"

class CScreen
	: public CMemoryBitmap
{
public:
	CScreen(HDC hdcWnd, int width, int height)//CMemoryBitmap�� �Ű������� �ޱ� ���� CScreen������ �Ű����� ����
		: CMemoryBitmap(hdcWnd, width, height) {}
	CScreen();
	CScreen(int width, int height);
	//~CScreen();

	
	void Draw(HDC hdc);
	
	void Draw(HDC hdc, int dest_x, int dest_y, int width, int height);
};

