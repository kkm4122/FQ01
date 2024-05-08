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
    std::list<Node*> OpenNode; // 열린노드
    std::list<Node*> CloseNode; // 닫힌노드
    Node* SNode; // 선택된 노드
    std::list<POS*> path;// 길
    
    OpenNode.push_back(new Node(StartP, EndP, NULL));//시작좌표 저장
    std::list<Node*>::iterator iter;

    while (OpenNode.end() != OpenNode.begin()&&OpenNode.end() == CoordNode(EndP.x, EndP.y, &OpenNode))
    //end()==begin()이면 오픈노드가 비어있다는 뜻 end()!= CoordNode이면 오픈노드 안에 목적지가 들어있음(목적지를 찾음)
    {
        iter = NextNode(&OpenNode); // 열린노드 중 F값이 제일 작은 노드의 주소를 찾아서 iter 에 저장
        SNode = *iter; // 열린노드 중 F값이 제일 작은 노드를 SNode에 저장
        // 선택된 SNode 주변의 4방향 노드 탐색, 값이 수정될 수 있는 것은 열린 노드 뿐이므로 열린 노드는 주소를 전달.    
        ExPloerUnitNode(Unit, TUnit, CurMap, SNode, &OpenNode, &CloseNode, EndP);
        //ExploreNode(CurMap, SNode, &OpenNode, &CloseNode, EndP);
        CloseNode.push_back(SNode); // 현재 탐색한 노드를 닫힌 노드에 추가
        OpenNode.erase(iter); // 닫힌 노드에 추가한 노드를 열린 노드에서 제거
    }
    if ((OpenNode.end() != OpenNode.begin())) // 길을 찾은 경우	OpenNode.end()!= FindCoordNode(EndPoint.x,EndPoint.y,&OpenNode)
    {
        iter = CoordNode(EndP.x, EndP.y, &OpenNode);
        for (SNode = *iter; SNode->pParent != NULL; SNode=SNode->pParent)//부모가 NULL(시작경로)일때까지 경로 저장
        {
            path.push_front(new POS(SNode->PointPOS.x, SNode->PointPOS.y));
        }
        //path.push_front(new POS(SNode->PointPOS.x, SNode->PointPOS.y));//시작경로 저장
        //path.reverse();//패스경로를 역순으로 저장 (목적지~시작)을 (시작~목적지)로(push_back일때만 사용)
    }
    for (; iter != OpenNode.end(); iter++)
    {
        delete* iter; // 열린 노드 동적할당 해제
    }
    iter = CloseNode.begin();
    for (; iter != CloseNode.end(); iter++)
    {
        delete* iter; // 닫힌 노드 동적할당 해제 
    }
    return path;
}

std::stack<POS*> AStar::PathFind_stack(CUnit* Unit,CUnit* TUnit, CMap* CurMap, POS StartP, POS EndP)
{
    std::list<Node*> OpenNode; // 열린노드
    std::list<Node*> CloseNode; // 닫힌노드
    Node* SNode; // 선택된 노드
    std::stack<POS*> path;// 길

    OpenNode.push_back(new Node(StartP, EndP, NULL));//시작좌표 저장
    std::list<Node*>::iterator iter;

    while (OpenNode.end() != OpenNode.begin() && OpenNode.end() == CoordNode(EndP.x, EndP.y, &OpenNode))
        //end()==begin()이면 오픈노드가 비어있다는 뜻 end()!= CoordNode이면 오픈노드 안에 목적지가 들어있음(목적지를 찾음)
    {
        iter = NextNode(&OpenNode); // 열린노드 중 F값이 제일 작은 노드의 주소를 찾아서 iter 에 저장
        SNode = *iter; // 열린노드 중 F값이 제일 작은 노드를 SNode에 저장
        // 선택된 SNode 주변의 4방향 노드 탐색, 값이 수정될 수 있는 것은 열린 노드 뿐이므로 열린 노드는 주소를 전달.    
        //ExploreNode(CurMap, SNode, &OpenNode, &CloseNode, EndP);
        ExPloerUnitNode(Unit, TUnit, CurMap, SNode, &OpenNode, &CloseNode, EndP);
        CloseNode.push_back(SNode); // 현재 탐색한 노드를 닫힌 노드에 추가
        OpenNode.erase(iter); // 닫힌 노드에 추가한 노드를 열린 노드에서 제거
    }
    if ((OpenNode.end() != OpenNode.begin())) // 길을 찾은 경우	OpenNode.end()!= FindCoordNode(EndPoint.x,EndPoint.y,&OpenNode)
    {
        iter = CoordNode(EndP.x, EndP.y, &OpenNode);
        for (SNode = *iter; SNode->pParent != NULL; SNode->pParent)//부모가 NULL(시작경로)일때까지 경로 저장
        {
            path.push(new POS(SNode->PointPOS.x, SNode->PointPOS.y));
        }
        path.push(new POS(SNode->PointPOS.x, SNode->PointPOS.y));//시작경로 저장
       //패스경로를 역순으로 저장 (목적지~시작)을 (시작~목적지)로
    }
    for (; iter != OpenNode.end(); iter++)
    {
        delete* iter; // 열린 노드 동적할당 해제
    }
    iter = CloseNode.begin();
    for (; iter != CloseNode.end(); iter++)
    {
        delete* iter; // 닫힌 노드 동적할당 해제 
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

void AStar::ExploreNode(CMap* CurMap, Node* SNode, std::list<Node*>* OpenNode, std::list<Node*>* CloseNode, POS EndP)//노드 탐색
{
    bool up = true, right = true, down = true, left = true; // 이 결과에 따라 대각선 방향 탐색 여부를 결정. true == 장애물 있음, false == 없음
    std::list<Node*>::iterator iter;
    POS point;
    //상
    point.x = SNode->PointPOS.x;
    point.y = SNode->PointPOS.y - 1;
    if (SNode->PointPOS.y > 0 && CurMap->mTiles[point.y][point.x].unit == nullptr)
    {//현재 노드의 좌표의 상부분이 맵 안에 존재하고 장애물이 없는 경우
        up = false;//false = 장애물이 없다
        //end() 노드의 끝좌표(아무것도 들어가있지 않음)
        //현노드end()!=Coordnode(현노드)는 현노드안에 좌표값을 가지는노드가 발견된 경우 즉 end()==coordnode는 좌표값을 가진 노드가 발견되지 않는경우 좌표가 현 노드안에 없다 
        if (OpenNode->end() != CoordNode(point.x, point.y, OpenNode))
        {
            iter = CoordNode(point.x, point.y, OpenNode);
            if ((*iter)->G > (SNode->G + 10)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
            {
                (*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
            }
        }

        else if (CloseNode->end() != CoordNode(point.x, point.y, CloseNode))
        {
            //닫힌노드에 좌표가 있는경우
        }
        else
        {
            //장애물이 없고 닫힌노드 열린노드에 해당 좌표가 존재하지 않는경우
            OpenNode->push_back(new Node(point, EndP, SNode));
        }
    }
    //우
    point.x = SNode->PointPOS.x + 1;
    point.y = SNode->PointPOS.y;
    if (SNode->PointPOS.x < (CurMap->SizeX - 1) && CurMap->mTiles[point.y][point.x].unit == nullptr)
    {//현재 노드의 좌표의 상부분이 맵 안에 존재하고 장애물이 없는 경우
        right = false;//false = 장애물이 없다
        //end() 노드의 끝좌표(아무것도 들어가있지 않음)
        //현노드end()!=Coordnode(현노드)는 현노드안에 좌표값을 가지는노드가 발견된 경우 즉 end()==coordnode는 좌표값을 가진 노드가 발견되지 않는경우 좌표가 현 노드안에 없다 
        if (OpenNode->end() != CoordNode(point.x, point.y, OpenNode))
        {
            iter = CoordNode(point.x, point.y, OpenNode);
            if ((*iter)->G > (SNode->G + 10)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
            {
                (*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
            }
        }

        else if (CloseNode->end() != CoordNode(point.x, point.y, CloseNode))
        {
            //닫힌노드에 좌표가 있는경우
        }
        else
        {
            //장애물이 없고 닫힌노드 열린노드에 해당 좌표가 존재하지 않는경우
            OpenNode->push_back(new Node(point, EndP, SNode));
        }
    }
    //하
    point.x = SNode->PointPOS.x;
    point.y = SNode->PointPOS.y + 1;
    if (SNode->PointPOS.y < (CurMap->SizeY - 1) && CurMap->mTiles[point.y][point.x].unit == nullptr)
    {//현재 노드의 좌표의 상부분이 맵 안에 존재하고 장애물이 없는 경우
        down = false;//false = 장애물이 없다
        //end() 노드의 끝좌표(아무것도 들어가있지 않음)
        //현노드end()!=Coordnode(현노드)는 현노드안에 좌표값을 가지는노드가 발견된 경우 즉 end()==coordnode는 좌표값을 가진 노드가 발견되지 않는경우 좌표가 현 노드안에 없다 
        if (OpenNode->end() != CoordNode(point.x, point.y, OpenNode))
        {
            iter = CoordNode(point.x, point.y, OpenNode);
            if ((*iter)->G > (SNode->G + 10)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
            {
                (*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
            }
        }

        else if (CloseNode->end() != CoordNode(point.x, point.y, CloseNode))
        {
            //닫힌노드에 좌표가 있는경우
        }
        else
        {
            //장애물이 없고 닫힌노드 열린노드에 해당 좌표가 존재하지 않는경우
            OpenNode->push_back(new Node(point, EndP, SNode));
        }
    }
    //좌
    point.x = SNode->PointPOS.x - 1;
    point.y = SNode->PointPOS.y;
    if (SNode->PointPOS.x > 0 && CurMap->mTiles[point.y][point.x].unit == nullptr)
    {//현재 노드의 좌표의 상부분이 맵 안에 존재하고 장애물이 없는 경우
        left = false;//false = 장애물이 없다
        //end() 노드의 끝좌표(아무것도 들어가있지 않음)
        //현노드end()!=Coordnode(현노드)는 현노드안에 좌표값을 가지는노드가 발견된 경우 즉 end()==coordnode는 좌표값을 가진 노드가 발견되지 않는경우 좌표가 현 노드안에 없다 
        if (OpenNode->end() != CoordNode(point.x, point.y, OpenNode))
        {
            iter = CoordNode(point.x, point.y, OpenNode);
            if ((*iter)->G > (SNode->G + 10)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
            {
                (*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
            }
        }

        else if (CloseNode->end() != CoordNode(point.x, point.y, CloseNode))
        {
            //닫힌노드에 좌표가 있는경우
        }
        else
        {
            //장애물이 없고 닫힌노드 열린노드에 해당 좌표가 존재하지 않는경우
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
                {//TUnit 의 사이즈안에 들어갈 경우 이동가능처리
                    return false;
                }
            }
        }
    }
    return true;
}
void AStar::ExPloerUnitNode(CUnit* Unit, CUnit* TUnit, CMap* CurMap, Node* SNode, std::list<Node*>* OpenNode, std::list<Node*>* CloseNode, POS EndP)
{   //1x1이아닌 2x2이상의 유닛들 탐색 노드

    bool up = true, right = true, down = true, left = true; // 이 결과에 따라 대각선 방향 탐색 여부를 결정. true == 장애물 있음, false == 없음
    std::list<Node*>::iterator iter;
    POS point;
    //상
    point.x = SNode->PointPOS.x;
    point.y = SNode->PointPOS.y - 1;
    if (SNode->PointPOS.y > 0 && NullNode(Unit, TUnit, CurMap, point))
    {//현재 노드의 좌표의 상부분이 맵 안에 존재하고 장애물이 없는 경우
        up = false;//false = 장애물이 없다
        //end() 노드의 끝좌표(아무것도 들어가있지 않음)
        //현노드end()!=Coordnode(현노드)는 현노드안에 좌표값을 가지는노드가 발견된 경우 즉 end()==coordnode는 좌표값을 가진 노드가 발견되지 않는경우 좌표가 현 노드안에 없다 
        if (OpenNode->end() != CoordNode(point.x, point.y, OpenNode))
        {
            iter = CoordNode(point.x, point.y, OpenNode);
            if ((*iter)->G > (SNode->G + 10)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
            {
                (*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
            }
        }

        else if (CloseNode->end() != CoordNode(point.x, point.y, CloseNode))
        {
            //닫힌노드에 좌표가 있는경우
        }
        else
        {
            //장애물이 없고 닫힌노드 열린노드에 해당 좌표가 존재하지 않는경우
            OpenNode->push_back(new Node(point, EndP, SNode));
        }
    }
    //우
    point.x = SNode->PointPOS.x + 1;
    point.y = SNode->PointPOS.y;
    if (SNode->PointPOS.x + Unit->size - 1 < (CurMap->SizeX - 1) && NullNode(Unit, TUnit,CurMap, point))
    {//현재 노드의 좌표의 상부분이 맵 안에 존재하고 장애물이 없는 경우
        right = false;//false = 장애물이 없다
        //end() 노드의 끝좌표(아무것도 들어가있지 않음)
        //현노드end()!=Coordnode(현노드)는 현노드안에 좌표값을 가지는노드가 발견된 경우 즉 end()==coordnode는 좌표값을 가진 노드가 발견되지 않는경우 좌표가 현 노드안에 없다 
        if (OpenNode->end() != CoordNode(point.x, point.y, OpenNode))
        {
            iter = CoordNode(point.x, point.y, OpenNode);
            if ((*iter)->G > (SNode->G + 10)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
            {
                (*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
            }
        }

        else if (CloseNode->end() != CoordNode(point.x, point.y, CloseNode))
        {
            //닫힌노드에 좌표가 있는경우
        }
        else
        {
            //장애물이 없고 닫힌노드 열린노드에 해당 좌표가 존재하지 않는경우
            OpenNode->push_back(new Node(point, EndP, SNode));
        }
    }

    //하
    point.x = SNode->PointPOS.x;
    point.y = SNode->PointPOS.y + 1;
    if (SNode->PointPOS.y + Unit->size - 1 < (CurMap->SizeY - 1) && NullNode(Unit, TUnit, CurMap, point))
    {//현재 노드의 좌표의 상부분이 맵 안에 존재하고 장애물이 없는 경우
        down = false;//false = 장애물이 없다
        //end() 노드의 끝좌표(아무것도 들어가있지 않음)
        //현노드end()!=Coordnode(현노드)는 현노드안에 좌표값을 가지는노드가 발견된 경우 즉 end()==coordnode는 좌표값을 가진 노드가 발견되지 않는경우 좌표가 현 노드안에 없다 
            if (OpenNode->end() != CoordNode(point.x, point.y, OpenNode))
            {
                iter = CoordNode(point.x, point.y, OpenNode);
                if ((*iter)->G > (SNode->G + 10)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
                {
                    (*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
                }
            }

            else if (CloseNode->end() != CoordNode(point.x, point.y, CloseNode))
            {
                //닫힌노드에 좌표가 있는경우
            }
            else
            {
                //장애물이 없고 닫힌노드 열린노드에 해당 좌표가 존재하지 않는경우
                OpenNode->push_back(new Node(point, EndP, SNode));
            }
    }
    //좌
    point.x = SNode->PointPOS.x - 1;
    point.y = SNode->PointPOS.y;
    if (SNode->PointPOS.x > 0 && NullNode(Unit, TUnit, CurMap, point))
    {//현재 노드의 좌표의 상부분이 맵 안에 존재하고 장애물이 없는 경우
        left = false;//false = 장애물이 없다
        //end() 노드의 끝좌표(아무것도 들어가있지 않음)
        //현노드end()!=Coordnode(현노드)는 현노드안에 좌표값을 가지는노드가 발견된 경우 즉 end()==coordnode는 좌표값을 가진 노드가 발견되지 않는경우 좌표가 현 노드안에 없다 
        if (OpenNode->end() != CoordNode(point.x, point.y, OpenNode))
        {
            iter = CoordNode(point.x, point.y, OpenNode);
            if ((*iter)->G > (SNode->G + 10)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
            {
                (*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
            }
        }

        else if (CloseNode->end() != CoordNode(point.x, point.y, CloseNode))
        {
            //닫힌노드에 좌표가 있는경우
        }
        else
        {
            //장애물이 없고 닫힌노드 열린노드에 해당 좌표가 존재하지 않는경우
            OpenNode->push_back(new Node(point, EndP, SNode));
        }
    }
}