#pragma once

class CImageFile
{
	int mRefCount;//이미지가 참조된 횟수
	void AddRef(){ ++mRefCount; }
	int Release() { return --mRefCount; }
public:
	std::wstring mName;		//이미지파일 이름
	HBITMAP		mhBitmap;	//비트맵
	BITMAP		mBmpInfo;	//비트맵 정보

	CImageFile(const WCHAR* fileName, const WCHAR* name);
	~CImageFile();



	static CImageFile* New(const WCHAR* fileName, const WCHAR* name);
	static void Delete(CImageFile* delItem);
	static void DestroyAll();

	void Draw	(HDC hdc, 
				 int dest_x, int dest_y,
				 int src_x,  int src_y, 
				 int width,  int height);
	void TransDraw(HDC hdc,
		int dest_x, int dest_y,
		int src_x, int src_y,
		int width, int height, UINT color);
	//dest->화면에 출력될 장소 좌표 src->그릴 그림의 좌표, width heigth그릴 그림의 사이즈
	void AlphaDraw(HDC hdc,
		int dest_x, int dest_y,
		int src_x, int src_y,
		int width, int height,
		BYTE alpha);
	void FadeInOut(HDC hdc,
		int dest_x, int dest_y,
		int src_x, int src_y,
		int width, int height,
		BYTE alpha);



	int Height()	const{ return mBmpInfo.bmHeight;}
	int Width()		const{ return mBmpInfo.bmWidth; }//const 최적화하기 수월


};

