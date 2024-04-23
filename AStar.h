#pragma once
#include "POS.h"
class CMap;
class AStar {
public:
	
	class NODE
	{
	public:
		POS Point;
		int F = 0;		//비용
		int G = 0;		//지난 거리
		int H = 0;		//남은 거리
		POS EndPoint;
		NODE* pParent;
	};
	CMap* TileMap;
};