#pragma once
#include "POS.h"
#include <list>
class CMap;
class AStar {
public:
	
	class Node
	{
	public:
		POS PointPOS;
		int F = 0;		//���
		int G = 0;		//���� �Ÿ�
		int H = 0;		//���� �Ÿ�
		POS EndPoint;
		Node* pParent;
	public:
		Node(POS POINT, POS EndP, Node* _pParent);
	};
	std::list<POS*> PathFind(CMap* CurMap, POS StartP, POS EndP);
};