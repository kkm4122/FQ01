#include "pch.h"
#include "CMap.h"
#include "CUnit.h"



CUnit::~CUnit()
{
}

bool CUnit::isMoving()
{

	return !(mPosition == mTarget);
}

void CUnit::Update(int dt)
{
	mUnitSprite.Update(dt);
}

void CUnit::Draw(HDC hdc)
{
	mUnitSprite.Draw(hdc);
}



void CUnit::WalkToAstar(CMap* Map, CUnit* target)
{
	if (target == nullptr)
	{
		return;
	}
	else if (target->Death)
	{
		return;
	}
	
	if (!path.empty())
	{
		//POS* destP = path.front()
		if (path.back()->x == target->TilePos.x&& path.back()->y == target->TilePos.y)
		{
			POS* nextP = path.front();
			POS dir;
			dir.x = nextP->x - TilePos.x;
			dir.y = nextP->y - TilePos.y;
			Map->Update();
			//if(Map->mTiles[nextP->y][nextP->x].unit)
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{

					if (Map->mTiles[nextP->y + i][nextP->x + j].unit != this && Map->mTiles[nextP->y + i][nextP->x + j].unit != nullptr)
					{
						path.clear();
						return;
					}
					if (Map->mTiles[nextP->y + i][nextP->x + j].unit == target)
					{
						path.clear();
						return;
					}


				}
			}
			Move(dir.x, dir.y);
			
			path.pop_front();
		}
		else
		{//타겟 유닛 위치가 바뀐경우
			path.clear();
			path=A.PathFind(this, target, Map, TilePos, target->TilePos);
			POS* nextP = path.front();
			POS dir;
			dir.x = nextP->x - TilePos.x;
			dir.y = nextP->y - TilePos.y;
			Map->Update();
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (Map->mTiles[nextP->y + i][nextP->x + j].unit != this && Map->mTiles[nextP->y + i][nextP->x + j].unit != nullptr)
					{
						path.clear();
						return;
					}
					if (Map->mTiles[nextP->y + i][nextP->x + j].unit == target)
					{
						path.clear();
						return;
					}

				}
			}
			Move(dir.x, dir.y);
			
			path.pop_front();
		}
	}
	else
	{
		//패스가 만들어지는 상황이 안될때 추가 PathFind 함수 확인
		path=A.PathFind(this, target, Map, TilePos, target->TilePos);
	}
}



void CUnit::Move(int x, int y)
{
	if (x == 1 && y == 0)
	{
		TilePos.x++;
		mUnitSprite.ChangeAnimation(mRight);
	}
	else if (x == -1 && y == 0)
	{
		TilePos.x--;
		mUnitSprite.ChangeAnimation(mLeft);
	}
	else if (x == 0 && y == 1)
	{
		TilePos.y++;
		mUnitSprite.ChangeAnimation(mDown);
	}
	else if (x == 0 && y == -1)
	{
		TilePos.y--;
		mUnitSprite.ChangeAnimation(mUp);
	}
	
}



bool CUnit::BlockedOnAllSidesT(CMap* Map, CUnit* target)//타겟 방향이 모두 막혀있을때
{
	int s = target->size;
	int y = target->TilePos.y;
	int x = target->TilePos.x;
	if (x> 0 && y > 0)
	{
		if (Map->mTiles[y - 1][x].unit == nullptr|| Map->mTiles[y - 1][x].unit!=this)
		{
			return false;
		}
		
	}
	else if (x>0 && y==0)
	{ }
	else if (x == 0 && y > 0)
	{

	}
	else if(x==0&&y==0)
	return true;
}

void CUnit::TargetAstar(CMap* Map, CUnit* a)
{
	
		mTarget = { a->TilePos.x, a->TilePos.y };
		path = A.PathFind(this,a, Map, TilePos, a->TilePos);
	
}

bool CUnit::Searchthis(CMap* Map, CUnit* Target, POS NextP)
{
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			if (Map->mTiles[NextP.y + y][NextP.x + x].unit == Target)
			{
				return true;
			}
		}
	}
	return false;
}

void CUnit::MovePath(CMap* Map, CUnit* a)
{
	TargetAstar(Map, a);
}

bool CUnit::CanMove(CMap* Map, CUnit* Target, POS NextP)
{
	Map->Update();
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			if (Map->mTiles[NextP.y + y][NextP.x + x].unit != nullptr&& Map->mTiles[NextP.y + y][NextP.x + x].unit!=this)
			{
				return false;
			}
		}
	}
	return true;
}

void CUnit::WalkOneTile(CMap* Map, int x)

{
	Map->Update();
	switch (x)
	{
	case MOVE_UP:
		if (CanMoveXY(Map, 0, -1))
		{
			TilePos.y--;
			mUnitSprite.ChangeAnimation(mUp);
		}
		else
		{
			mUnitSprite.ChangeAnimation(s3);
		}
		break;
	case MOVE_DOWN:
		if (CanMoveXY(Map, 0, 1))
		{
			TilePos.y++;
			mUnitSprite.ChangeAnimation(mDown);
		}
		else
		{
			mUnitSprite.ChangeAnimation(s0);
		}
		break;
	case MOVE_LEFT:
		if (CanMoveXY(Map, -1, 0))
		{
			TilePos.x--;
			mUnitSprite.ChangeAnimation(mLeft);
		}
		else
		{
			mUnitSprite.ChangeAnimation(s1);
		}
		break;
	case MOVE_RIGHT:
		if (CanMoveXY(Map, 1, 0))
		{
			TilePos.x++;
			mUnitSprite.ChangeAnimation(mRight);
		}
		else
		{
			mUnitSprite.ChangeAnimation(s2);
		}
		break;
	default:
		break;
	}
	Map->Update();
}
bool CUnit::CanMoveXY(CMap* Map, int x, int y)
{
	Map->Update();
	int px = TilePos.x + x;
	int py = TilePos.y + y;
	if (px < 0 || py < 0 || px + size - 1>Map->SizeX - 1 || py + size - 1>Map->SizeY - 1)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (Map->mTiles[py + j][px + i].unit != nullptr && Map->mTiles[py + j][px + i].unit != this || Map->mTiles[py + j][px + i].Path != nullptr)
				{
					return false;
				}
			}
		}
	}
	return true;
}
void CUnit::searchUnit(CMap* Map)
{
	int D = 999;	
	if (Target == nullptr)
	{
		
	}
	else
	{
		D= abs(TilePos.x - Target->TilePos.x) + abs(TilePos.y - Target->TilePos.y);
	}
	
	for (CUnit* ic : Map->mCharacters)
	{
		if (ic->UnitNo != UnitNo) {
			int icD = abs(TilePos.x - ic->TilePos.x) + abs(TilePos.y - ic->TilePos.y);
			if (D > icD) {
				D = icD;
				Target = ic;
			}
		}
	}
}
void CUnit::UpdateCamPos(int cx, int cy)
{
	mUnitSprite.mDestX =  cx + (16 * TilePos.x);
	mUnitSprite.mDestY =  cy + (16 * TilePos.y);
}


