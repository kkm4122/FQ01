#pragma once
#include "POS.h"
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
};