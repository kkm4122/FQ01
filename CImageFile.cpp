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
		}//�� �迭���� �ڱ� �ڽ��� ������ �����ְ� delete ȣ��

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
	mhBitmap = LoadBitmapW(CApplication::theApp->mhInst, fileName);//����
	GetObject(mhBitmap, sizeof(BITMAP), &mBmpInfo);
}

CImageFile::~CImageFile()
{
	DeleteObject(mhBitmap);//����
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

	BLENDFUNCTION bf;			//��Ʈ�� ������ ó��	
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = alpha;	//���� �� 0: ���� ����, 255 : ������
	bf.AlphaFormat = 0;
	AlphaBlend(hdc, dest_x, dest_y, width, height,
		hBmpDC, src_x, src_y, width, height, bf);

	SelectObject(hBmpDC, old);
	DeleteDC(hBmpDC);
}

void CImageFile::FadeInOut(HDC hdcWnd, int dest_x, int dest_y, int src_x, int src_y, int width, int height, BYTE alpha)
{
	BLENDFUNCTION bf;			//��Ʈ�� ������ ó��

	BITMAPINFO bmi;	//bmi.bmiHeader��Ʈ�� �� ������ ����
	ZeroMemory(&bmi, sizeof(BITMAPINFO));	//
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = height;
	bmi.bmiHeader.biPlanes = 1; //��� ����̽��� ����
	bmi.bmiHeader.biBitCount = 32;//�ȼ��� ��Ʈ ��(bpp) 4byte
	bmi.bmiHeader.biCompression = BI_RGB; // ������� ���� rgb ���� �� ���� ����
	bmi.bmiHeader.biSizeImage = width * height * 4;//(���� ���ϱ� ����=�ȼ� ��) �ȼ��� 4byte�̱� ������ * 4

	VOID* pvBits;			//�÷��� �������� ���� �ּ� ��ȯ
	HDC hdc = CreateCompatibleDC(hdcWnd);
	HBITMAP hbitmapDIB = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pvBits, NULL, 0x0);//bitmap(����â�� ����) ����
	SelectObject(hdc, hbitmapDIB);

	UINT32* pColors = (UINT32*)pvBits;

	UINT32 rgba = alpha;//����
	for (int y = 0; y < height; y++)//����
	{
		for (int x = 0; x < width; x++) {
			pColors[y * width + x] = 0xFF000000;//0x:16����, FF:ALpha,000000:Red, Green, Blue = Black
		}
	}//���� â(���̵�ó���� �̹����� ũ�⸸ŭ)�� ����� ���̵� �� ���̵� �ƿ��� �ϱ�����
	{
		HDC hBmpDC = CreateCompatibleDC(hdc);
		HBITMAP old = (HBITMAP)SelectObject(hBmpDC, mhBitmap);

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = alpha;	//���� �� 0: ���� ����, 255 : ������
		bf.AlphaFormat = 0;
		AlphaBlend(hdc, dest_x, dest_y, width, height,
			hBmpDC, src_x, src_y, width, height, bf);

		SelectObject(hBmpDC, old);
		DeleteDC(hBmpDC);
	}//����â�� ���ĺ��� ó��
	BitBlt(hdcWnd, dest_x, dest_y, width, height,
		hdc, 0, 0, SRCCOPY);
	//���� �� �̹����� ���

	DeleteObject(hbitmapDIB);
	DeleteDC(hdc);
}
