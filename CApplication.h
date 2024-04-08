#pragma once
//전역변수를 한대 모으기 위함
class CApplication
{
public:
	CApplication();

	void 화면갱신();

public:

	static CApplication* theApp;

	HINSTANCE	mhInst;
	HWND		mhWnd;
	int WinWidth;
	int WinHeight;
};



