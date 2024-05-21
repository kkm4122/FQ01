#include "pch.h"
#include "CApplication.h"
#include "CScreen.h"

CScreen::CScreen()
{
	HDC hdc = GetDC(CApplication::theApp->mhWnd);

	int Width= CApplication::theApp->WinWidth;
	int Height= CApplication::theApp->WinHeight;
	//CMemoryBitmap(hdc, Width, Height);
	//CApplication::theApp->mhWnd, 
	//CApplication::theApp->WinWidth
	//CApplication::theApp->WinHeight
	Create(hdc,Width,Height);

}

CScreen::CScreen(int width, int height)
{
	HDC hdc = GetDC(CApplication::theApp->mhWnd);
	Create(hdc, width, height);
}

void CScreen::Draw(HDC hdc)
{
	BitBlt(hdc,
		0, 0,
		getWidth(), getHeight(),
		m_HDC,
		0, 0, SRCCOPY
	);
}

void CScreen::Draw(HDC hdc, int dest_x, int dest_y, int width, int height)
{
	BitBlt(hdc,
		dest_x, dest_y,
		width, height,
		m_HDC,
		dest_x, dest_y, SRCCOPY
	);
}
void CScreen::Draw(HDC hdc, int sx, int sy, int width, int height,int dx, int dy)
{
	BitBlt(hdc,
		sx, sy,
		width, height,
		m_HDC,
		dx, dy, SRCCOPY
	);
}
