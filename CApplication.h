#pragma once
//���������� �Ѵ� ������ ����
class CApplication
{
public:
	CApplication();

	void ȭ�鰻��();

public:

	static CApplication* theApp;

	HINSTANCE	mhInst;
	HWND		mhWnd;
	int WinWidth;
	int WinHeight;
};



