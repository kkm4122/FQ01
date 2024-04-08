#include "pch.h"
#include "CMemoryBitmap.h"

CMemoryBitmap::CMemoryBitmap(HDC hdcWnd, int width, int height)//깜박임 방지 더블버퍼
{
	Create(hdcWnd, width, height);
}



CMemoryBitmap::~CMemoryBitmap()
{
	SelectObject(m_HDC, m_Old);
	DeleteDC(m_HDC);
	DeleteObject(m_hBitmap);
}

void CMemoryBitmap::Create(HDC hdcWnd, int width, int height)
{
	ZeroMemory(&m_BMI, sizeof(BITMAPINFO));
	m_BMI.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_BMI.bmiHeader.biWidth = width;
	m_BMI.bmiHeader.biHeight = height;
	m_BMI.bmiHeader.biPlanes = 1;
	m_BMI.bmiHeader.biBitCount = 32;         // four 8-bit components 
	m_BMI.bmiHeader.biCompression = BI_RGB;
	m_BMI.bmiHeader.biSizeImage = width * height * 4;

	m_HDC = CreateCompatibleDC(hdcWnd);
	m_hBitmap = CreateDIBSection(m_HDC, &m_BMI, DIB_RGB_COLORS, (void**)&m_Colors, NULL, 0x0);
	m_Old = (HBITMAP)SelectObject(m_HDC, m_hBitmap);

	Clear(0xFF000000);
}

void CMemoryBitmap::Clear(UINT32 color)
{
	int width = getWidth();
	int height = getHeight();

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			m_Colors[y * width + x] = color;
}
