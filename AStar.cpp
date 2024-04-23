#include "pch.h"
#include "AStar.h"



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

std::list<POS*> AStar::PathFind(CMap* CurMap, POS StartP, POS EndP)
{
    std::list<Node*> OpenNode; // 열린노드
    std::list<Node*> CloseNode; // 닫힌노드
    Node* SNode; // 선택된 노드
    std::list<POS*> path;// 길
    return std::list<POS*>();
}