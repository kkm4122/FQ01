#include "pch.h"
#include "CImagefile.h"
#include "CApplication.h"

#pragma comment(lib,"Msimg32.lib")

static std::vector< CImageFile*> g_ImgFileArray;

CImageFile* CImageFile::New(const WCHAR* fileName, const WCHAR* name)
{
	std::wstring n = name;
	for (CImageFile* it : g_ImgFileArray)
	{
		if (it->mName == name)
		{
			it->AddRef();
			return it;
		}
	}
	CImageFile* it = new CImageFile(fileName, name);
	it->AddRef();
	

	bool sucess = false;
	for (int i = 0; i < g_ImgFileArray.size(); i++)
	{
		if (g_ImgFileArray[i] == nullptr)
		{
			g_ImgFileArray[i] = it;
			sucess = true;
			
		}
	}
	if (!sucess) 
	{
		g_ImgFileArray.push_back(it);
	}
	return it;
}

void CImageFile::Delete(CImageFile* delItem)
{
	delItem->Release();
	if (delItem->mRefCount <= 0)
	{
		for (int i = 0; i < g_ImgFileArray.size(); i++)
		{
			if (g_ImgFileArray[i] == delItem)
			{
				g_ImgFileArray[i] = nullptr;
			}
		}//위 배열에서 자기 자신이 있으면 지워주고 delete 호출

		delete delItem;

	}
	
}

void CImageFile::DestroyAll()
{
	for (CImageFile* it : g_ImgFileArray)
	{
		if(it)delete it;
	}
}



CImageFile::CImageFile(const WCHAR* fileName, const WCHAR* name)
{
	mRefCount = 0;
	mName = name;
	mhBitmap = LoadBitmapW(CApplication::theApp->mhInst, fileName);//생성
	GetObject(mhBitmap, sizeof(BITMAP), &mBmpInfo);
}

CImageFile::~CImageFile()
{
	DeleteObject(mhBitmap);//삭제
}



void CImageFile::Draw	(HDC hdc,
						 int dest_x, int dest_y,
						 int src_x,  int src_y,
						 int width,  int height)
{
	HDC hBmpDC = CreateCompatibleDC(hdc);
	HBITMAP old = (HBITMAP)SelectObject(hBmpDC,mhBitmap);
	BitBlt(hdc, 
		dest_x, dest_y,
		width, height,
		hBmpDC, 
		src_x, src_y, SRCCOPY);

	SelectObject(hBmpDC, old);
	DeleteDC(hBmpDC);
}

void CImageFile::TransDraw(HDC hdc, int dest_x, int dest_y, int src_x, int src_y, int width, int height, UINT color)
{
	HDC hBmpDC = CreateCompatibleDC(hdc);

	HBITMAP old = (HBITMAP)SelectObject(hBmpDC, mhBitmap);
	TransparentBlt(hdc,
		dest_x, dest_y,	width, height,
		hBmpDC,
		src_x, src_y, width, height,
		color);

	SelectObject(hBmpDC, old);
	DeleteDC(hBmpDC);
}

void CImageFile::AlphaDraw(HDC hdc, int dest_x, int dest_y, int src_x, int src_y, int width, int height, BYTE alpha)
{
	HDC hBmpDC = CreateCompatibleDC(hdc);
	HBITMAP old = (HBITMAP)SelectObject(hBmpDC, mhBitmap);

	BLENDFUNCTION bf;			//비트맵 정보를 처리	
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = alpha;	//투명도 값 0: 완전 투명, 255 : 불투명
	bf.AlphaFormat = 0;
	AlphaBlend(hdc, dest_x, dest_y, width, height,
		hBmpDC, src_x, src_y, width, height, bf);

	SelectObject(hBmpDC, old);
	DeleteDC(hBmpDC);
}

void CImageFile::FadeInOut(HDC hdcWnd, int dest_x, int dest_y, int src_x, int src_y, int width, int height, BYTE alpha)
{
	BLENDFUNCTION bf;			//비트맵 정보를 처리

	BITMAPINFO bmi;	//bmi.bmiHeader비트맵 색 정보를 포함
	ZeroMemory(&bmi, sizeof(BITMAPINFO));	//
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = height;
	bmi.bmiHeader.biPlanes = 1; //대상 디바이스의 평면수
	bmi.bmiHeader.biBitCount = 32;//픽셀당 비트 수(bpp) 4byte
	bmi.bmiHeader.biCompression = BI_RGB; // 압축되지 않은 rgb 설정 색 직접 지정
	bmi.bmiHeader.biSizeImage = width * height * 4;//(넓이 곱하기 높이=픽셀 수) 픽셀당 4byte이기 때문에 * 4

	VOID* pvBits;			//컬러값 시작점을 받을 주소 반환
	HDC hdc = CreateCompatibleDC(hdcWnd);
	HBITMAP hbitmapDIB = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pvBits, NULL, 0x0);//bitmap(검은창을 위한) 생성
	SelectObject(hdc, hbitmapDIB);

	UINT32* pColors = (UINT32*)pvBits;

	UINT32 rgba = alpha;//질문
	for (int y = 0; y < height; y++)//질문
	{
		for (int x = 0; x < width; x++) {
			pColors[y * width + x] = 0xFF000000;//0x:16진수, FF:ALpha,000000:Red, Green, Blue = Black
		}
	}//검은 창(페이드처리할 이미지의 크기만큼)을 만들어 페이드 인 페이드 아웃을 하기위함
	{
		HDC hBmpDC = CreateCompatibleDC(hdc);
		HBITMAP old = (HBITMAP)SelectObject(hBmpDC, mhBitmap);

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = alpha;	//투명도 값 0: 완전 투명, 255 : 불투명
		bf.AlphaFormat = 0;
		AlphaBlend(hdc, dest_x, dest_y, width, height,
			hBmpDC, src_x, src_y, width, height, bf);

		SelectObject(hBmpDC, old);
		DeleteDC(hBmpDC);
	}//검은창에 알파블랜딩 처리
	BitBlt(hdcWnd, dest_x, dest_y, width, height,
		hdc, 0, 0, SRCCOPY);
	//블랜딩 된 이미지를 출력

	DeleteObject(hbitmapDIB);
	DeleteDC(hdc);
}
