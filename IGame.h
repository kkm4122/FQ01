#pragma once
#include "CApplication.h"
#include "IScene.h"
#include "CScreen.h"
class IScene;

class IGame
{
public:
	IGame() : mCurrent(NULL)//not 코드 (데이터를 만들어서 한번에 만드는 구조)
	{}
	virtual void onChangeScene() = 0;
	//mCurrent = NULL->코드	컴파일러가 알아서 하는 구조(옵티마이징)
	virtual void onFrameMove()
	{
		onChangeScene();//씬 변환
		if (mCurrent) 
		{
			if (mCurrent->SetOn)mCurrent->SetScene();
			mCurrent->SetOn = false;
			mCurrent->onFrameMove();
		}
		InvalidateRect(CApplication::theApp->mhWnd, NULL, FALSE);
	}
	virtual void onDraw(HDC hdc)
	{
		if (mCurrent)
		{

			CScreen screen(hdc, 642, 480);
			mCurrent->onDraw(screen.m_HDC);
			screen.Draw(hdc);
		}
	}

	virtual void onKeyDown( UINT virtual_key) 
	{
		CHAR str[100];
		sprintf_s(str, 100, "Vkey: %d\n", virtual_key );
		OutputDebugStringA(str);
		//if (mCurrent->Sample())
		if (mCurrent) mCurrent->onKeyDown(virtual_key);
		InvalidateRect(CApplication::theApp->mhWnd, NULL, FALSE);
	}
	virtual void onMouseMove(UINT x, UINT y) 
	{
		char str[100];
		//sprintf_s(str, 100, "x: %d	y: %d\n", x,y);
		sprintf_s(str, 100, "x: %d	y: %d\n", x, y);
		if (mCurrent) 
		{
			mCurrent->onMouseMove(x, y);
			OutputDebugStringA(str);
		}
		
		
	}
	virtual void onMouseDown(UINT x, UINT y, UINT left_right)
	{
		char str[100];
		
		sprintf_s(str, 100, "x: %d	y: %d vkey: %d\n", x, y,left_right);
		if (mCurrent)
		{
			mCurrent->onMouseDown(x, y, left_right);
			OutputDebugStringA(str);			
		}
		//if (mCurrent) mCurrent->onMouseDown(x, y,left_right);
	}
public:
	
	IScene* mCurrent;
};

