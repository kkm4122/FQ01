#include "pch.h"
#include "CApplication.h"


CApplication* CApplication::theApp=NULL;//클래스 안에 선언된 스태틱 클래스
CApplication app;

CApplication::CApplication()
{
	theApp = this;//내 포인터를 저장해 두겠다.
}

void CApplication::화면갱신()
{
	InvalidateRect(mhWnd, NULL, true);
}
