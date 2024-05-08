#pragma once
#include "POS.h"
#include <list>
#include <stack>
class CMap;
class CUnit;
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

	std::list<AStar::Node*>::iterator NextNode(std::list<Node*>* SeNode);
	std::list<AStar::Node*>::iterator CoordNode(int dx, int dy, std::list<Node*>* SeNode);
	void ExploreNode(CMap* CurMap, Node* SNode, std::list<Node*> *OpenNode, std::list<Node*> *CloseNode, POS EndP);
	void ExPloerUnitNode(CUnit* Unit,CUnit* TUnit, CMap* CurMap, Node* SNode, std::list<Node*>* OpenNode, std::list<Node*>* CloseNode, POS EndP);

public:
	std::list<POS*> PathFind(CUnit* Unit, CUnit* TUnit, CMap* CurMap, POS StartP, POS EndP);
	std::stack<POS*> PathFind_stack(CUnit* Unit, CUnit* TUnit, CMap* CurMap, POS StartP, POS EndP);
};