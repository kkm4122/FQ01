#pragma once
#include"CAnimation.h"
#include"CSprite.h"

class CUnit;





struct POS
{
	int x;
	int y;

	bool operator == (const POS& other)const
	{
		return x == other.x && y == other.y;
	}
	bool operator != (const POS& other)const
	{
		return x != other.x || y != other.y;
	}
};

class CImageFile;
class UnitInfo;


class CUnit
{
public:
	
	~CUnit();
	bool isMoving()
	{
		return !(mPosition == mTarget);
	}

	void Think()
	{
		// Ÿ�� ã��(find)`
		// �̵��ؾ��� ��ǥ�� ����
		// �浹 ����
	}
	void Update()
	{
		if(isMoving())
		{
			mDir.x = mTarget.x - mPosition.x;
			mDir.y = mTarget.y - mPosition.y;

			float len = sqrt((mDir.x * mDir.x) + (mDir.y * mDir.y));
			
			if (len < mSpeed) {
				mPosition.x = mTarget.x;
				mPosition.y = mTarget.y;
			}
			else
			{
				float fx = (float)mDir.x / len;//cos
				float fy = (float)mDir.y / len;//sin
				//�������� ���ϱ� �ӵ�

				fx = fx * mSpeed;
				fy = fy * mSpeed;
				mDir.x = fx;
				mDir.y = fx;

				mPosition.x += mDir.x;
				mPosition.y += mDir.y;
			}
			//�밢�� �̵��� ���� //��������
			//g_Map->SetUnit(this);
		}
	}
	void Draw(HDC hdc);

	void SetPostion(int tile_x, int tile_y)
	{
		mPosition.x = tile_x * 16;
		mPosition.y = tile_y * 16;
	}
	void MoveTo(int tile_x, int tile_y)
	{
		//asdf
		mTarget.x = tile_x * 16;
		mTarget.y = tile_y * 16;
		//if (isMoving)
		
		
	}
	virtual void move() {};
	//void DrawUnit(HDC hdc);
	void TileSet(int dx, int dy, const WCHAR* Anino)
	{
		dx *= 16;
		dy *= 16;
		mUnitSprite.Set2(Anino, dx, dy, m_anifile.ani, m_anifile.imgFile, RGB(255, 0, 255), CSprite::DrawType_Transparent);
	}
	void UnitSet(int dx, int dy, const WCHAR* Anino)
	{
		mUnitSprite.Set2(Anino, dx, dy, m_anifile.ani, m_anifile.imgFile, RGB(255, 0, 255), CSprite::DrawType_Transparent);
	}
	void UpdateCamPos(int cx, int cy);

public:

	CImageFile* UnitImg;
	ANIM_FILE m_anifile;

	CFrameSprite mUnitSprite;
	CFrameSprite UnitState;

	UnitInfo* UInfo;

	POS TilePos;
	POS mPosition;
	POS mTarget;
	POS mDir;
	int size = 2;
	float mSpeed;
	
	//int MapInfo;
	
	POS mTile;
};




class UnitInfo
{
public:
	
};
