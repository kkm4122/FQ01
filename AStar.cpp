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
    else//길을 찾지 못한 경우 비어있는 path 리턴
    {
        path.empty();
        return path;
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
    //패스 리턴전에 검사식 추가
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
/*저도 스타크래프트 길찾기에 대해 엄청 많은 고민을 했었는데
일단 경계분할을 스타크래프트처럼 상황에 맞춰하는 알고리즘은 도저히 머리로는 못짜겠더라구요
지형에 따라 알아서 "리전"이 나뉘어야하는데 그걸 하는법을 아무리 고민하거나 구글링해봐도 잘 모르겠었고..

그래서 그냥 256*256의 맵이라면 32*32 크기의 큰 타일 8*8 정도로 나눈다거나 하는 방식으로 크게 지역을 분할해서,
오브젝트 리스트를 그 타일에 귀속시켜서 관리하면서
길찾기는 처음 로딩할 때 큰 타일의 가운데를 기준으로 주변 8타일로 가는 최단경로를 탐색해서 저장해두고,2022.03.20 18:38:01삭제
ㅇㅇ(211.46)만약 이동 명령이 큰 타일 1개의 거리보다 길게 찍히면 그 타일과 타일의 경로를 무조건 따라가게 하는 방식으로 했어요
실제 스타크래프트도 리전 나누기 방식이지만 비슷한 방식을 사용하구요
그리고 적 탐색 같은 거 할 때도 쿼드트리 사용하거나 주변 큰 타일에 들어있는 오브젝트 리스트만 갖고 탐색하면 아무래도 빠르구요

스타가 다수 vs 다수의 길찾기와 적탐색을 계속 실행하다보니까 메모리관리나 실행시간 최적화가 진짜진짜 힘들더라구요
많이 고민해보셔요2022.03.20 18:42:08삭제
Pawn(112.162)말씀만 들어도 고민을 엄청 하신 티가 나네요.. 2d 네비게이션으로 구현을 하고 있다가 적 탐색 알고리즘 최적화를 어떻게 해야할지 모르겠어서 멈춘 상태긴한데 역시 쉬운부분이 아니었군요... 다들 어렵다해주시니까 오히려 나만그런게 아니구나 하면서 힘이 납니다. 감사합니당.2022.03.20 18:46:45삭제
ㅇㅇ(211.46)좀 정리하면
1. 클릭하는 순간만 길찾기를 실행, 매 프레임 이걸 하면 겜 바로 터짐
2. 이동거리가 일정 이상이면 미리 로딩해둔 큰 타일과 타일 사이의 경로를 따라감
3. 거리가 일정 이하일 때만 세밀한 탐색을 실행
4. 이동 중일때 쿼드트리 등 좀 최적화된 자료구조를 통해서 적 탐색, 적 탐색 성공하면 최소한 일정 거리 이하라는 뜻이므로 자세한 길찾기 실행
5. 여기서 건물과 유닛 길막이 들어가는데.. 이거도 머리 엄청아픔..2022.03.20 18:50:42삭제
ㅇㅇ(211.46)제가 검색해보고 고민한 바로는 지형 기반 길찾기(리전 탐색) ->
건물을 포함한 길찾기(크게크게 길을 막음 + 자원채취하는 일꾼은 유닛은 통과하는데 건물은 통과못함) ->
유닛을 포함한 길찾기(내 앞 경로의 유닛이 이동 중인지? 이동중인 유닛이면 그 유닛이 경로를 비워줄때까지 대기, 그래서 질럿이나 저글링이 버벅대면서 일자로 감, 내 앞 경로의 유닛이 멈춤 상태면 실행 시간 어마어마하게 잡아먹을 경로 탐색을 다시하는게 아니라 시계방향으로 도는 방법 등으로 최대한 부하 안주고 돌아갈 수 있게 처리해줘야 함)
등의 절차를 거쳤던 것 같아요.. 그냥 이론만으로 만들어둔 타일 100*100개 에서 탐색하는 A*로는 진짜 택도 없더라구요2022.03.20 18:58:07삭제
ㅇㅇ(211.46)제가 말한 절차가 어떤 느낌인지 저글링 블러드 같은거 보시면 알거에요
저글링 블러드 유즈맵에선 비콘 찍으면 저글링들이 한번에 일정 위치로 어택땅을 찍는데
지형에 따라 움직이고, 건물은 또 돌아가고, 앞에 저글링 갈때까지 기다리다보니 일렬로 쭈욱 늘어서서 뛰고..
암튼 머리 엄청아파요2022.03.20 19:00:49삭제
ㅇㅇ(211.46)그러면서 느낀건 1995년도 컴퓨터 사양으로 1600마리까지 무리없이 돌아가게
최적화한 미친 개발자들이 새삼 대단하게 느껴질 뿐...2022.03.20 19:02:39삭제
Pawn(112.162)아 정말정말 감사합니다. 이렇게나 해주시고 ㅠㅠ 에셋 2d 네비게이션으로 간략하게 나마 만들고 있었는데 유닛을 죽이고 유닛을 재탐색하는 경우 유닛이 멈춰있는 시간이 길어서 a*로 해보려 했는데 이것도 힘들어보이네요 ㅠㅠ 아무튼 머리깨질각오하고 한번 노력해보겠습니다.. 다시한번 너무 감사합니다.*/