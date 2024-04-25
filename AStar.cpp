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

    while (OpenNode.end() != OpenNode.begin()&&OpenNode.end() == CoordNode(EndP.x, EndP.y, &OpenNode))
    //end()==begin()�̸� ���³�尡 ����ִٴ� �� end()!= CoordNode�̸� ���³�� �ȿ� �������� �������(�������� ã��)
    {

    }
    return path;
}

std::list<AStar::Node*>::iterator AStar::NextNode(std::list<Node*>* SeNode)
{
    std::list<AStar::Node*>::iterator iter = (*SeNode).begin();

    int MinF = 5959595959;//ó�� �ּڰ��� ���ϱ����� ������
    int CuNodeNo = 0; //0=��尡 ������������
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

std::list<AStar::Node*>::iterator AStar::CoordNode(int dx, int dy, std::list<AStar::Node*>* SeNode)//���õ� ��帮��Ʈ���� x,y�� ��ǥ�� ���� ��带 ��ȯ ������ end() ��ȯ
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
    bool up = true, right = true, down = true, left = true; // �� ����� ���� �밢�� ���� Ž�� ���θ� ����. true == ��ֹ� ����, false == ����
    std::list<Node*>::iterator iter;
    POS point;
}
