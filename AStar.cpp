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
    std::list<Node*> OpenNode; // 열린노드
    std::list<Node*> CloseNode; // 닫힌노드
    Node* SNode; // 선택된 노드
    std::list<POS*> path;// 길
    OpenNode.push_back(new Node(StartP, EndP, NULL));//시작좌표 저장
    std::list<Node*>::iterator iter;

    while (OpenNode.end() != OpenNode.begin()&&OpenNode.end() == CoordNode(EndP.x, EndP.y, &OpenNode))
    //end()==begin()이면 오픈노드가 비어있다는 뜻 end()!= CoordNode이면 오픈노드 안에 목적지가 들어있음(목적지를 찾음)
    {

    }
    return path;
}

std::list<AStar::Node*>::iterator AStar::NextNode(std::list<Node*>* SeNode)
{
    std::list<AStar::Node*>::iterator iter = (*SeNode).begin();

    int MinF = 5959595959;//처음 최솟값을 정하기위한 변수값
    int CuNodeNo = 0; //0=노드가 정해지지않음
    for (int i = 1; iter != (*SeNode).end(); i++, iter++)
    {
        if ((*iter)->F <= MinF)
        {
            MinF = (*iter)->F;
            CuNodeNo = i;
        }
    }
    iter= (*SeNode).begin();
    for (int i = 1; i < CuNodeNo; i++)
    {
        iter++;
    }

    return iter;
}

std::list<AStar::Node*>::iterator AStar::CoordNode(int dx, int dy, std::list<AStar::Node*>* SeNode)//선택된 노드리스트에서 x,y의 좌표를 가진 노드를 반환 없으면 end() 반환
{
    std::list<AStar::Node*>::iterator iter = SeNode->begin();
    for (int i = 1; iter != SeNode->end(); i++, iter++)
    {
        if ((*iter)->PointPOS.x == dx && (*iter)->PointPOS.y == dy)
        {
            return iter;
        }
    }
    return SeNode->end();
}

void AStar::ExploreNode(CMap* CurMap, Node* SNode, std::list<Node*> OpenNode, std::list<Node*> CloseNode, POS EndP)
{
    bool up = true, right = true, down = true, left = true; // 이 결과에 따라 대각선 방향 탐색 여부를 결정. true == 장애물 있음, false == 없음
    std::list<Node*>::iterator iter;
    POS point;
}
