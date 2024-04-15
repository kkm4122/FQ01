#pragma once
#include"CAnimation.h"
#include"CSprite.h"


#define STATE_Idle      0
#define STATE_Move      1
#define STATE_Attack    2
#define STATE_DEATH		3


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
		// 타겟 찾기(find)`
		// 이동해야할 목표점 설정
		// 충돌 감지
	}
	void Update(int dt);
	
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
		int tx = dx*16;
		int ty = dy*16;
		mUnitSprite.Set2(Anino, tx, ty, m_anifile.ani, m_anifile.imgFile, RGB(255, 0, 255), CSprite::DrawType_Transparent);
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
	int TeamNo;
	int UnitNo;
	//int MapInfo;
	
	POS mTile;
};




class UnitInfo
{
public:
	
};
