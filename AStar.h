#pragma once
#include "POS.h"
class CMap;
class AStar {
public:
	
	class NODE
	{
	public:
		POS Point;
		int F = 0;		//���
		int G = 0;		//���� �Ÿ�
		int H = 0;		//���� �Ÿ�
		POS EndPoint;
		NODE* pParent;
	};
	CMap* TileMap;
};