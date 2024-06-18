#include "pch.h"
#include "AStar.h"
#include "CMap.h"
#include "CUnit.h"
#include <list>
#include <stack>
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




std::list<POS*> AStar::PathFind(CUnit* Unit, CUnit* TUnit, CMap* CurMap, POS StartP, POS EndP)
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
        iter = NextNode(&OpenNode); // ������� �� F���� ���� ���� ����� �ּҸ� ã�Ƽ� iter �� ����
        SNode = *iter; // ������� �� F���� ���� ���� ��带 SNode�� ����
        // ���õ� SNode �ֺ��� 4���� ��� Ž��, ���� ������ �� �ִ� ���� ���� ��� ���̹Ƿ� ���� ���� �ּҸ� ����.    
        ExPloerUnitNode(Unit, TUnit, CurMap, SNode, &OpenNode, &CloseNode, EndP);
        //ExploreNode(CurMap, SNode, &OpenNode, &CloseNode, EndP);
        CloseNode.push_back(SNode); // ���� Ž���� ��带 ���� ��忡 �߰�
        OpenNode.erase(iter); // ���� ��忡 �߰��� ��带 ���� ��忡�� ����
    }
    if ((OpenNode.end() != OpenNode.begin())) // ���� ã�� ���	OpenNode.end()!= FindCoordNode(EndPoint.x,EndPoint.y,&OpenNode)
    {
        iter = CoordNode(EndP.x, EndP.y, &OpenNode);
        for (SNode = *iter; SNode->pParent != NULL; SNode=SNode->pParent)//�θ� NULL(���۰��)�϶����� ��� ����
        {
            path.push_front(new POS(SNode->PointPOS.x, SNode->PointPOS.y));
        }
        //path.push_front(new POS(SNode->PointPOS.x, SNode->PointPOS.y));//���۰�� ����
        //path.reverse();//�н���θ� �������� ���� (������~����)�� (����~������)��(push_back�϶��� ���)
    }
    else//���� ã�� ���� ��� ����ִ� path ����
    {
        path.empty();
        return path;
    }
    for (; iter != OpenNode.end(); iter++)
    {
        delete* iter; // ���� ��� �����Ҵ� ����
    }
    iter = CloseNode.begin();
    for (; iter != CloseNode.end(); iter++)
    {
        delete* iter; // ���� ��� �����Ҵ� ���� 
    }
    //�н� �������� �˻�� �߰�
    return path;
}

std::stack<POS*> AStar::PathFind_stack(CUnit* Unit,CUnit* TUnit, CMap* CurMap, POS StartP, POS EndP)
{
    std::list<Node*> OpenNode; // �������
    std::list<Node*> CloseNode; // �������
    Node* SNode; // ���õ� ���
    std::stack<POS*> path;// ��

    OpenNode.push_back(new Node(StartP, EndP, NULL));//������ǥ ����
    std::list<Node*>::iterator iter;

    while (OpenNode.end() != OpenNode.begin() && OpenNode.end() == CoordNode(EndP.x, EndP.y, &OpenNode))
        //end()==begin()�̸� ���³�尡 ����ִٴ� �� end()!= CoordNode�̸� ���³�� �ȿ� �������� �������(�������� ã��)
    {
        iter = NextNode(&OpenNode); // ������� �� F���� ���� ���� ����� �ּҸ� ã�Ƽ� iter �� ����
        SNode = *iter; // ������� �� F���� ���� ���� ��带 SNode�� ����
        // ���õ� SNode �ֺ��� 4���� ��� Ž��, ���� ������ �� �ִ� ���� ���� ��� ���̹Ƿ� ���� ���� �ּҸ� ����.    
        //ExploreNode(CurMap, SNode, &OpenNode, &CloseNode, EndP);
        ExPloerUnitNode(Unit, TUnit, CurMap, SNode, &OpenNode, &CloseNode, EndP);
        CloseNode.push_back(SNode); // ���� Ž���� ��带 ���� ��忡 �߰�
        OpenNode.erase(iter); // ���� ��忡 �߰��� ��带 ���� ��忡�� ����
    }
    if ((OpenNode.end() != OpenNode.begin())) // ���� ã�� ���	OpenNode.end()!= FindCoordNode(EndPoint.x,EndPoint.y,&OpenNode)
    {
        iter = CoordNode(EndP.x, EndP.y, &OpenNode);
        for (SNode = *iter; SNode->pParent != NULL; SNode->pParent)//�θ� NULL(���۰��)�϶����� ��� ����
        {
            path.push(new POS(SNode->PointPOS.x, SNode->PointPOS.y));
        }
        path.push(new POS(SNode->PointPOS.x, SNode->PointPOS.y));//���۰�� ����
       //�н���θ� �������� ���� (������~����)�� (����~������)��
    }
    for (; iter != OpenNode.end(); iter++)
    {
        delete* iter; // ���� ��� �����Ҵ� ����
    }
    iter = CloseNode.begin();
    for (; iter != CloseNode.end(); iter++)
    {
        delete* iter; // ���� ��� �����Ҵ� ���� 
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

void AStar::ExploreNode(CMap* CurMap, Node* SNode, std::list<Node*>* OpenNode, std::list<Node*>* CloseNode, POS EndP)//��� Ž��
{
    bool up = true, right = true, down = true, left = true; // �� ����� ���� �밢�� ���� Ž�� ���θ� ����. true == ��ֹ� ����, false == ����
    std::list<Node*>::iterator iter;
    POS point;
    //��
    point.x = SNode->PointPOS.x;
    point.y = SNode->PointPOS.y - 1;
    if (SNode->PointPOS.y > 0 && CurMap->mTiles[point.y][point.x].unit == nullptr)
    {//���� ����� ��ǥ�� ��κ��� �� �ȿ� �����ϰ� ��ֹ��� ���� ���
        up = false;//false = ��ֹ��� ����
        //end() ����� ����ǥ(�ƹ��͵� ������ ����)
        //�����end()!=Coordnode(�����)�� �����ȿ� ��ǥ���� �����³�尡 �߰ߵ� ��� �� end()==coordnode�� ��ǥ���� ���� ��尡 �߰ߵ��� �ʴ°�� ��ǥ�� �� ���ȿ� ���� 
        if (OpenNode->end() != CoordNode(point.x, point.y, OpenNode))
        {
            iter = CoordNode(point.x, point.y, OpenNode);
            if ((*iter)->G > (SNode->G + 10)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
            {
                (*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
            }
        }

        else if (CloseNode->end() != CoordNode(point.x, point.y, CloseNode))
        {
            //������忡 ��ǥ�� �ִ°��
        }
        else
        {
            //��ֹ��� ���� ������� ������忡 �ش� ��ǥ�� �������� �ʴ°��
            OpenNode->push_back(new Node(point, EndP, SNode));
        }
    }
    //��
    point.x = SNode->PointPOS.x + 1;
    point.y = SNode->PointPOS.y;
    if (SNode->PointPOS.x < (CurMap->SizeX - 1) && CurMap->mTiles[point.y][point.x].unit == nullptr)
    {//���� ����� ��ǥ�� ��κ��� �� �ȿ� �����ϰ� ��ֹ��� ���� ���
        right = false;//false = ��ֹ��� ����
        //end() ����� ����ǥ(�ƹ��͵� ������ ����)
        //�����end()!=Coordnode(�����)�� �����ȿ� ��ǥ���� �����³�尡 �߰ߵ� ��� �� end()==coordnode�� ��ǥ���� ���� ��尡 �߰ߵ��� �ʴ°�� ��ǥ�� �� ���ȿ� ���� 
        if (OpenNode->end() != CoordNode(point.x, point.y, OpenNode))
        {
            iter = CoordNode(point.x, point.y, OpenNode);
            if ((*iter)->G > (SNode->G + 10)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
            {
                (*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
            }
        }

        else if (CloseNode->end() != CoordNode(point.x, point.y, CloseNode))
        {
            //������忡 ��ǥ�� �ִ°��
        }
        else
        {
            //��ֹ��� ���� ������� ������忡 �ش� ��ǥ�� �������� �ʴ°��
            OpenNode->push_back(new Node(point, EndP, SNode));
        }
    }
    //��
    point.x = SNode->PointPOS.x;
    point.y = SNode->PointPOS.y + 1;
    if (SNode->PointPOS.y < (CurMap->SizeY - 1) && CurMap->mTiles[point.y][point.x].unit == nullptr)
    {//���� ����� ��ǥ�� ��κ��� �� �ȿ� �����ϰ� ��ֹ��� ���� ���
        down = false;//false = ��ֹ��� ����
        //end() ����� ����ǥ(�ƹ��͵� ������ ����)
        //�����end()!=Coordnode(�����)�� �����ȿ� ��ǥ���� �����³�尡 �߰ߵ� ��� �� end()==coordnode�� ��ǥ���� ���� ��尡 �߰ߵ��� �ʴ°�� ��ǥ�� �� ���ȿ� ���� 
        if (OpenNode->end() != CoordNode(point.x, point.y, OpenNode))
        {
            iter = CoordNode(point.x, point.y, OpenNode);
            if ((*iter)->G > (SNode->G + 10)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
            {
                (*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
            }
        }

        else if (CloseNode->end() != CoordNode(point.x, point.y, CloseNode))
        {
            //������忡 ��ǥ�� �ִ°��
        }
        else
        {
            //��ֹ��� ���� ������� ������忡 �ش� ��ǥ�� �������� �ʴ°��
            OpenNode->push_back(new Node(point, EndP, SNode));
        }
    }
    //��
    point.x = SNode->PointPOS.x - 1;
    point.y = SNode->PointPOS.y;
    if (SNode->PointPOS.x > 0 && CurMap->mTiles[point.y][point.x].unit == nullptr)
    {//���� ����� ��ǥ�� ��κ��� �� �ȿ� �����ϰ� ��ֹ��� ���� ���
        left = false;//false = ��ֹ��� ����
        //end() ����� ����ǥ(�ƹ��͵� ������ ����)
        //�����end()!=Coordnode(�����)�� �����ȿ� ��ǥ���� �����³�尡 �߰ߵ� ��� �� end()==coordnode�� ��ǥ���� ���� ��尡 �߰ߵ��� �ʴ°�� ��ǥ�� �� ���ȿ� ���� 
        if (OpenNode->end() != CoordNode(point.x, point.y, OpenNode))
        {
            iter = CoordNode(point.x, point.y, OpenNode);
            if ((*iter)->G > (SNode->G + 10)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
            {
                (*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
            }
        }

        else if (CloseNode->end() != CoordNode(point.x, point.y, CloseNode))
        {
            //������忡 ��ǥ�� �ִ°��
        }
        else
        {
            //��ֹ��� ���� ������� ������忡 �ش� ��ǥ�� �������� �ʴ°��
            OpenNode->push_back(new Node(point, EndP, SNode));
        }
    }
}
//if (point.y >= 0 && CurMap->mTiles[point.y][point.x].unit == nullptr)
bool NullNode(CUnit* Unit,CUnit* TUnit, CMap* CurMap, POS point)
{
    for (int i = 0; i < Unit->size; i++)
    {
        for (int j = 0; j < Unit->size; j++)
        {
            if (CurMap->mTiles[point.y + j][point.x + i].unit != nullptr&& CurMap->mTiles[point.y + j][point.x + i].unit!=Unit)
            {
                if (CurMap->mTiles[point.y + j][point.x + i].unit != TUnit)
                {//TUnit �� ������ȿ� �� ��� �̵�����ó��
                    return false;
                }
            }
        }
    }
    return true;
}
void AStar::ExPloerUnitNode(CUnit* Unit, CUnit* TUnit, CMap* CurMap, Node* SNode, std::list<Node*>* OpenNode, std::list<Node*>* CloseNode, POS EndP)
{   //1x1�̾ƴ� 2x2�̻��� ���ֵ� Ž�� ���

    bool up = true, right = true, down = true, left = true; // �� ����� ���� �밢�� ���� Ž�� ���θ� ����. true == ��ֹ� ����, false == ����
    std::list<Node*>::iterator iter;
    POS point;
    //��
    point.x = SNode->PointPOS.x;
    point.y = SNode->PointPOS.y - 1;
    if (SNode->PointPOS.y > 0 && NullNode(Unit, TUnit, CurMap, point))
    {//���� ����� ��ǥ�� ��κ��� �� �ȿ� �����ϰ� ��ֹ��� ���� ���
        up = false;//false = ��ֹ��� ����
        //end() ����� ����ǥ(�ƹ��͵� ������ ����)
        //�����end()!=Coordnode(�����)�� �����ȿ� ��ǥ���� �����³�尡 �߰ߵ� ��� �� end()==coordnode�� ��ǥ���� ���� ��尡 �߰ߵ��� �ʴ°�� ��ǥ�� �� ���ȿ� ���� 
        if (OpenNode->end() != CoordNode(point.x, point.y, OpenNode))
        {
            iter = CoordNode(point.x, point.y, OpenNode);
            if ((*iter)->G > (SNode->G + 10)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
            {
                (*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
            }
        }

        else if (CloseNode->end() != CoordNode(point.x, point.y, CloseNode))
        {
            //������忡 ��ǥ�� �ִ°��
        }
        else
        {
            //��ֹ��� ���� ������� ������忡 �ش� ��ǥ�� �������� �ʴ°��
            OpenNode->push_back(new Node(point, EndP, SNode));
        }
    }
    //��
    point.x = SNode->PointPOS.x + 1;
    point.y = SNode->PointPOS.y;
    if (SNode->PointPOS.x + Unit->size - 1 < (CurMap->SizeX - 1) && NullNode(Unit, TUnit,CurMap, point))
    {//���� ����� ��ǥ�� ��κ��� �� �ȿ� �����ϰ� ��ֹ��� ���� ���
        right = false;//false = ��ֹ��� ����
        //end() ����� ����ǥ(�ƹ��͵� ������ ����)
        //�����end()!=Coordnode(�����)�� �����ȿ� ��ǥ���� �����³�尡 �߰ߵ� ��� �� end()==coordnode�� ��ǥ���� ���� ��尡 �߰ߵ��� �ʴ°�� ��ǥ�� �� ���ȿ� ���� 
        if (OpenNode->end() != CoordNode(point.x, point.y, OpenNode))
        {
            iter = CoordNode(point.x, point.y, OpenNode);
            if ((*iter)->G > (SNode->G + 10)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
            {
                (*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
            }
        }

        else if (CloseNode->end() != CoordNode(point.x, point.y, CloseNode))
        {
            //������忡 ��ǥ�� �ִ°��
        }
        else
        {
            //��ֹ��� ���� ������� ������忡 �ش� ��ǥ�� �������� �ʴ°��
            OpenNode->push_back(new Node(point, EndP, SNode));
        }
    }

    //��
    point.x = SNode->PointPOS.x;
    point.y = SNode->PointPOS.y + 1;
    if (SNode->PointPOS.y + Unit->size - 1 < (CurMap->SizeY - 1) && NullNode(Unit, TUnit, CurMap, point))
    {//���� ����� ��ǥ�� ��κ��� �� �ȿ� �����ϰ� ��ֹ��� ���� ���
        down = false;//false = ��ֹ��� ����
        //end() ����� ����ǥ(�ƹ��͵� ������ ����)
        //�����end()!=Coordnode(�����)�� �����ȿ� ��ǥ���� �����³�尡 �߰ߵ� ��� �� end()==coordnode�� ��ǥ���� ���� ��尡 �߰ߵ��� �ʴ°�� ��ǥ�� �� ���ȿ� ���� 
            if (OpenNode->end() != CoordNode(point.x, point.y, OpenNode))
            {
                iter = CoordNode(point.x, point.y, OpenNode);
                if ((*iter)->G > (SNode->G + 10)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
                {
                    (*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
                }
            }

            else if (CloseNode->end() != CoordNode(point.x, point.y, CloseNode))
            {
                //������忡 ��ǥ�� �ִ°��
            }
            else
            {
                //��ֹ��� ���� ������� ������忡 �ش� ��ǥ�� �������� �ʴ°��
                OpenNode->push_back(new Node(point, EndP, SNode));
            }
    }
    //��
    point.x = SNode->PointPOS.x - 1;
    point.y = SNode->PointPOS.y;
    if (SNode->PointPOS.x > 0 && NullNode(Unit, TUnit, CurMap, point))
    {//���� ����� ��ǥ�� ��κ��� �� �ȿ� �����ϰ� ��ֹ��� ���� ���
        left = false;//false = ��ֹ��� ����
        //end() ����� ����ǥ(�ƹ��͵� ������ ����)
        //�����end()!=Coordnode(�����)�� �����ȿ� ��ǥ���� �����³�尡 �߰ߵ� ��� �� end()==coordnode�� ��ǥ���� ���� ��尡 �߰ߵ��� �ʴ°�� ��ǥ�� �� ���ȿ� ���� 
        if (OpenNode->end() != CoordNode(point.x, point.y, OpenNode))
        {
            iter = CoordNode(point.x, point.y, OpenNode);
            if ((*iter)->G > (SNode->G + 10)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
            {
                (*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
            }
        }

        else if (CloseNode->end() != CoordNode(point.x, point.y, CloseNode))
        {
            //������忡 ��ǥ�� �ִ°��
        }
        else
        {
            //��ֹ��� ���� ������� ������忡 �ش� ��ǥ�� �������� �ʴ°��
            OpenNode->push_back(new Node(point, EndP, SNode));
        }
    }
}
/*���� ��Ÿũ����Ʈ ��ã�⿡ ���� ��û ���� ����� �߾��µ�
�ϴ� �������� ��Ÿũ����Ʈó�� ��Ȳ�� �����ϴ� �˰����� ������ �Ӹ��δ� ��¥�ڴ��󱸿�
������ ���� �˾Ƽ� "����"�� ��������ϴµ� �װ� �ϴ¹��� �ƹ��� ����ϰų� ���۸��غ��� �� �𸣰ھ���..

�׷��� �׳� 256*256�� ���̶�� 32*32 ũ���� ū Ÿ�� 8*8 ������ �����ٰų� �ϴ� ������� ũ�� ������ �����ؼ�,
������Ʈ ����Ʈ�� �� Ÿ�Ͽ� �ͼӽ��Ѽ� �����ϸ鼭
��ã��� ó�� �ε��� �� ū Ÿ���� ����� �������� �ֺ� 8Ÿ�Ϸ� ���� �ִܰ�θ� Ž���ؼ� �����صΰ�,2022.03.20 18:38:01����
����(211.46)���� �̵� ����� ū Ÿ�� 1���� �Ÿ����� ��� ������ �� Ÿ�ϰ� Ÿ���� ��θ� ������ ���󰡰� �ϴ� ������� �߾��
���� ��Ÿũ����Ʈ�� ���� ������ ��������� ����� ����� ����ϱ���
�׸��� �� Ž�� ���� �� �� ���� ����Ʈ�� ����ϰų� �ֺ� ū Ÿ�Ͽ� ����ִ� ������Ʈ ����Ʈ�� ���� Ž���ϸ� �ƹ����� ��������

��Ÿ�� �ټ� vs �ټ��� ��ã��� ��Ž���� ��� �����ϴٺ��ϱ� �޸𸮰����� ����ð� ����ȭ�� ��¥��¥ ������󱸿�
���� ����غ��ſ�2022.03.20 18:42:08����
Pawn(112.162)������ �� ����� ��û �Ͻ� Ƽ�� ���׿�.. 2d �׺���̼����� ������ �ϰ� �ִٰ� �� Ž�� �˰��� ����ȭ�� ��� �ؾ����� �𸣰ھ ���� ���±��ѵ� ���� ����κ��� �ƴϾ�����... �ٵ� ��ƴ����ֽôϱ� ������ �����׷��� �ƴϱ��� �ϸ鼭 ���� ���ϴ�. �����մϴ�.2022.03.20 18:46:45����
����(211.46)�� �����ϸ�
1. Ŭ���ϴ� ������ ��ã�⸦ ����, �� ������ �̰� �ϸ� �� �ٷ� ����
2. �̵��Ÿ��� ���� �̻��̸� �̸� �ε��ص� ū Ÿ�ϰ� Ÿ�� ������ ��θ� ����
3. �Ÿ��� ���� ������ ���� ������ Ž���� ����
4. �̵� ���϶� ����Ʈ�� �� �� ����ȭ�� �ڷᱸ���� ���ؼ� �� Ž��, �� Ž�� �����ϸ� �ּ��� ���� �Ÿ� ���϶�� ���̹Ƿ� �ڼ��� ��ã�� ����
5. ���⼭ �ǹ��� ���� �渷�� ���µ�.. �̰ŵ� �Ӹ� ��û����..2022.03.20 18:50:42����
����(211.46)���� �˻��غ��� ����� �ٷδ� ���� ��� ��ã��(���� Ž��) ->
�ǹ��� ������ ��ã��(ũ��ũ�� ���� ���� + �ڿ�ä���ϴ� �ϲ��� ������ ����ϴµ� �ǹ��� �������) ->
������ ������ ��ã��(�� �� ����� ������ �̵� ������? �̵����� �����̸� �� ������ ��θ� ����ٶ����� ���, �׷��� �����̳� ���۸��� ������鼭 ���ڷ� ��, �� �� ����� ������ ���� ���¸� ���� �ð� ���ϰ� ��Ƹ��� ��� Ž���� �ٽ��ϴ°� �ƴ϶� �ð�������� ���� ��� ������ �ִ��� ���� ���ְ� ���ư� �� �ְ� ó������� ��)
���� ������ ���ƴ� �� ���ƿ�.. �׳� �̷и����� ������ Ÿ�� 100*100�� ���� Ž���ϴ� A*�δ� ��¥ �õ� �����󱸿�2022.03.20 18:58:07����
����(211.46)���� ���� ������ � �������� ���۸� ���� ������ ���ø� �˰ſ���
���۸� ���� ����ʿ��� ���� ������ ���۸����� �ѹ��� ���� ��ġ�� ���ö��� ��µ�
������ ���� �����̰�, �ǹ��� �� ���ư���, �տ� ���۸� �������� ��ٸ��ٺ��� �Ϸķ� �޿� �þ�� �ٰ�..
��ư �Ӹ� ��û���Ŀ�2022.03.20 19:00:49����
����(211.46)�׷��鼭 ������ 1995�⵵ ��ǻ�� ������� 1600�������� �������� ���ư���
����ȭ�� ��ģ �����ڵ��� ���� ����ϰ� ������ ��...2022.03.20 19:02:39����
Pawn(112.162)�� �������� �����մϴ�. �̷��Գ� ���ֽð� �Ф� ���� 2d �׺���̼����� �����ϰ� ���� ����� �־��µ� ������ ���̰� ������ ��Ž���ϴ� ��� ������ �����ִ� �ð��� �� a*�� �غ��� �ߴµ� �̰͵� �����̳׿� �Ф� �ƹ�ư �Ӹ����������ϰ� �ѹ� ����غ��ڽ��ϴ�.. �ٽ��ѹ� �ʹ� �����մϴ�.*/