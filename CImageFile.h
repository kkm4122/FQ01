#pragma once

class CImageFile
{
	int mRefCount;//�̹����� ������ Ƚ��
	void AddRef(){ ++mRefCount; }
	int Release() { return --mRefCount; }
public:
	std::wstring mName;		//�̹������� �̸�
	HBITMAP		mhBitmap;	//��Ʈ��
	BITMAP		mBmpInfo;	//��Ʈ�� ����

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
	//dest->ȭ�鿡 ��µ� ��� ��ǥ src->�׸� �׸��� ��ǥ, width heigth�׸� �׸��� ������
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
	int Width()		const{ return mBmpInfo.bmWidth; }//const ����ȭ�ϱ� ����


};

