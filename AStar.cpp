#include "pch.h"
#include "AStar.h"
#include <list>
#include<stdio.h>


class AStar::Node;

AStar::Node::Node(POS POINT, POS EndP, Node* _pParent)
{
    PointPOS = POINT;
    pParent = _pParent;
    EndPoint = EndP;
    if (pParent == NULL)
    {
        G = 0;
    }
    else if (pParent->PointPOS.XYDir(PointPOS) == UP || pParent->PointPOS.XYDir(PointPOS) == DOWN || pParent->PointPOS.XYDir(PointPOS) == LEFT || pParent->PointPOS.XYDir(PointPOS) == RIGHT  )
    {
        G = pParent->G + 10;
    }
    H = (abs(EndPoint.x - PointPOS.x) + abs(EndPoint.y - PointPOS.y)) * 10;
    F = G + H;

}

AStar::Node::Node() : F(0), G(0), H(0)
{
}

AStar::Node::~Node()
{
}







std::list<POS*> AStar::PathFind(CMap* CurMap, POS StartP, POS EndP)
{
    std::list<Node*> OpenNode; // �������
    std::list<Node*> CloseNode; // �������
    Node* SNode; // ���õ� ���
    std::list<POS*> path;// ��
    OpenNode.push_back(new Node(StartP, EndP, NULL));//������ǥ ����
    std::list<Node*>::iterator iter;

    while (OpenNode.end() != OpenNode.begin()) {}
    return path;
}

std::list<AStar::Node*>::iterator CoordNode(int dx, int dy, std::list<AStar::Node*>* SNode)
{
    std::list<AStar::Node*>::iterator iter;
    return SNode->end();
}