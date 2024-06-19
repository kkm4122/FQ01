#pragma once

#include"CAnimation.h"
#include"CSprite.h"

#include"Astar.h"



#define STATE_Idle      0
#define STATE_Move      1
#define STATE_Attack    2
#define STATE_DEATH		3
#define MOVE_UP			4
#define MOVE_DOWN		5
#define MOVE_LEFT		6
#define MOVE_RIGHT		7
#define MOVE_NONDIR		8

class AstarHandler;
class CMap;
class CUnit;
class POS;
class UnitInfo
{
public:
	float HP = 100;
	float Attack = 10;
};


class CImageFile;
class UnitInfo;


class CUnit
{
public:
	
	~CUnit();
	bool isMoving();
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
	void WalkToAstar(CMap* Map, CUnit* a);
	bool CanMove(CMap* Map);
	void TargetOn(CMap* map);
	void MoveTo(int tile_x, int tile_y)
	{
		// 해당 변수만큼 이동
		TilePos.x += tile_x ;
		TilePos.y += tile_y ;
	}
	void Coordinate(int x, int y)
	{
		TilePos.x = x;
		TilePos.y = y;
	}
	void Move(int x, int y);
	int XDIR()
	{
		if (mDir.x >= 0)return MOVE_RIGHT;
		else if (mDir.x < 0)return MOVE_LEFT;
		else return MOVE_NONDIR;
	}
	int YDIR()
	{
		if (mDir.y >= 0)return MOVE_DOWN;
		else if (mDir.y < 0)return MOVE_UP;
		else return MOVE_NONDIR;
	}
	bool BlockedOnAllSidesT(CMap* Map, CUnit* target);
	void TargetAstar(CMap* Map, CUnit* target);
	bool Searchthis(CMap* Map, CUnit* Target, POS NextP);
	void MovePath(CMap* Map, CUnit* a);
	bool CanMove(CMap* Map, CUnit* Target, POS NextP);
	void WalkOneTile(CMap* Map, int x);
	bool CanMoveXY(CMap* Map, int x, int y);	
	void FacingTarget(CUnit* a)
	{
		if(Facing)
		{
			mDir.x = a->mUnitSprite.mDestX - mUnitSprite.mDestX;
			mDir.y = a->mUnitSprite.mDestY - mUnitSprite.mDestY;
			if (abs(mDir.x) >= abs(mDir.y))
			{
				switch (XDIR())
				{
				case MOVE_RIGHT:
					mUnitSprite.ChangeAnimation(s2);
					break;
				case MOVE_LEFT:
					mUnitSprite.ChangeAnimation(s1);
					break;
				default:
					break;
				}
			}
			else
			{
				switch (YDIR())
				{
				case MOVE_DOWN:

					mUnitSprite.ChangeAnimation(s0);
					break;
				case MOVE_UP:

					mUnitSprite.ChangeAnimation(s3);
					break;
				default:
					break;
				}
			}
		}
		
		
	}
	
	void DirWalk(CUnit* a)
	{
		mTarget = {a->TilePos.x, a->TilePos.y };
		
		mDir = mTarget - TilePos;
		if (abs(mDir.x) >= abs(mDir.y))
		{
			switch (XDIR())
			{
			case MOVE_RIGHT:
				TilePos.x++;
				mUnitSprite.ChangeAnimation(mRight);
				break;
			case MOVE_LEFT:
				TilePos.x--;
				mUnitSprite.ChangeAnimation(mLeft);
				break;
			default:
				break;
			}
		}
		else
		{
			switch (YDIR())
			{
			case MOVE_DOWN:
				TilePos.y++;
				mUnitSprite.ChangeAnimation(mDown);
				break;
			case MOVE_UP:
				TilePos.y--;
				mUnitSprite.ChangeAnimation(mUp);
				break;
			default:
				break;
			}			
		}
	}
	virtual void move() {};
	//void DrawUnit(HDC hdc);
	void searchUnit(CMap* Map);
	void TileSet(int dx, int dy, const WCHAR* Anino)
	{//타일로 받은 좌표값을 변환시켜 화면 출력
		int tx = dx*16;
		int ty = dy*16;
		mUnitSprite.Set2(Anino, tx, ty, m_anifile.ani, m_anifile.imgFile, RGB(255, 0, 255), CSprite::DrawType_Transparent);
	}
	void UnitSet(int dx, int dy, const WCHAR* Anino)
	{//맵 타일 없이 유닛 화면 출력
		mUnitSprite.Set2(Anino, dx, dy, m_anifile.ani, m_anifile.imgFile, RGB(255, 0, 255), CSprite::DrawType_Transparent);
	}
	void UpdateCamPos(int cx, int cy);

public:

	CImageFile* UnitImg;
	ANIM_FILE m_anifile;

	CFrameSprite mUnitSprite;
	CFrameSprite UnitState;

	UnitInfo UInfo;
	AStar A;
	POS TilePos;
	POS mPosition;
	POS mTarget;
	POS mDir;
	bool DrawUnit = true;
	int size = 2;
	float mSpeed;
	int TeamNo;
	int UnitNo;
	int UnitSit = STATE_Idle;
	//bool TargetOn = false;
	CUnit* Target = nullptr;
	//int MapInfo;
	std::list<POS*> path;	//경로 좌표
	bool Facing = false;
	bool Death = false;
	bool targetOn = false;
	int dtAstar = 4;
	bool RandomMove = false;
	std::wstring mDown = L"a.Sno:0";//아래
	std::wstring mLeft = L"a.Sno:1";//왼쪽
	std::wstring mRight = L"a.Sno:2";//오른쪽
	std::wstring mUp = L"a.Sno:3";//위
	std::wstring s0 = L"a.SnoSTOP:0";
	std::wstring s1 = L"a.SnoSTOP:1";
	std::wstring s2 = L"a.SnoSTOP:2";
	std::wstring s3 = L"a.SnoSTOP:3";
};