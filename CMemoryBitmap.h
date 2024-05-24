#pragma once
/*
struct ARGB
{
	BYTE b, g, r, a;
	
};

union ARGB_Color
{
	UINT32	c;
	ARGB	argb;
};
UINT getRed(UINT32 color)
{
	UINT a = (color & 0xFF000000) >> 24;
	UINT r = (color & 0x00FF0000) >> 16;
	UINT g = (color & 0x0000FF00) >> 8;
	UINT b = (color & 0x000000FF);

	
	ARGB_Color cc;
	cc.c = color;
	UINT a = cc.argb.a;
	UINT r = cc.argb.b;
	
	
}
*/




class CMemoryBitmap
{
	HBITMAP m_Old;

public:
	HBITMAP m_hBitmap;
	HDC     m_HDC;

	UINT32* m_Colors;
	BITMAPINFO m_BMI;        // bitmap header
	static int ScreenCount;

public:
	CMemoryBitmap(HDC hdcWnd, int width, int height);
	CMemoryBitmap()=default;
	~CMemoryBitmap();
	
	/*
	UINT32 getColor(int x, int y)			{ return m_Colors[y * m_BMI.bmiHeader.biWidth + x]; }
	void setColor(int x, int y, UINT32 c)	{ m_Colors[y * m_BMI.bmiHeader.biWidth + x] = c; }
	특정 좌표에 색을 받아오는 함수 및 색을 바꾸는 함수
	*/
	
	int getWidth()							{ return m_BMI.bmiHeader.biWidth; }
	int getHeight()							{ return m_BMI.bmiHeader.biHeight; }
	void Create(HDC hdcWnd, int width, int height);//hwnd 받아오기 위한
	void Clear(UINT32 color = 0xFF000000);

};

