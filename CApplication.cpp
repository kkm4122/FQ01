#include "pch.h"
#include "CApplication.h"


CApplication* CApplication::theApp=NULL;//Ŭ���� �ȿ� ����� ����ƽ Ŭ����
CApplication app;

CApplication::CApplication()
{
	theApp = this;//�� �����͸� ������ �ΰڴ�.
}

void CApplication::ȭ�鰻��()
{
	InvalidateRect(mhWnd, NULL, true);
}
