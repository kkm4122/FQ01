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
		int F = 0;		//비용
		int G = 0;		//지난 거리
		int H = 0;		//남은 거리
		POS EndPoint;
		Node* pParent;
	public:
		Node(POS POINT, POS EndP, Node* _pParent);
		Node();
		~Node();
	};


	std::list<AStar::Node*>::iterator CoordNode(int dx, int dy, std::list<Node*>* SNode);

public:
	std::list<POS*> PathFind(CMap* CurMap, POS StartP, POS EndP);
};