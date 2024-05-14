#include "pch.h"
#include "CUnitMange.h"
#include "CImageFile.h"
#include "CApplication.h"
#include "InGameIntro2.h"


/*  
* 출력순서
    맵
    인물 
    UI 
    텍스트창
    폰트및 텍스트 컷
    
*비트맵 시작 좌표
    UI 좌표           0     0
    카리온성 좌표      16     48
    아레스            304      288
    에레인            304      288+80  368
    곤라드            336      112
    대주교            242      80
    병사1[0]          208     112
    병사1[1]          272     112
    병사1[2]          400     112
    병사1[3]오른쪽주시 242    320
    병사1[4]왼쪽주시  368     320
    병사2[0]오른쪽주시 97     144
    병사2[1]왼쪽주시  512     144

*/

std::wstring m0 = L"a.Sno:0";//아래
std::wstring m1 = L"a.Sno:1";//왼쪽
std::wstring m2 = L"a.Sno:2";//오른쪽
std::wstring m3 = L"a.Sno:3";//위
std::wstring s0 = L"a.SnoSTOP:0";
std::wstring s1 = L"a.SnoSTOP:1";
std::wstring s2 = L"a.SnoSTOP:2";
std::wstring s3 = L"a.SnoSTOP:3";

InGameIntro2::InGameIntro2()
{
    str = new WCHAR[512];
    MainMap.PosX = 16;
    MainMap.PosY = 48;
    MainMap.MapImg = CImageFile::New(MAKEINTRESOURCE(IDB_KARION_MEET), L"IDB_KARION_MEET");
    mBG.Set(MainMap.PosX,MainMap.PosY,0,0, MainMap.MapImg,0, CSprite::DrawType_Draw);



    CUnitMange::a->Ares->UnitSet(304, 288, L"a.SnoSTOP:0");
    CUnitMange::a->Gonrad->UnitSet(336, 112, L"a.SnoSTOP:0");
    CUnitMange::a->ArchBishop->UnitSet(242, 80, L"a.Sno:0");
    CUnitMange::a->Aerain->UnitSet(304, 384, L"a.SnoSTOP:3");

    CUnitMange::a->KarionSoldier[0]->UnitSet(208, 112, L"a.SnoSTOP:0");
    CUnitMange::a->KarionSoldier[1]->UnitSet(272, 112, L"a.SnoSTOP:0");
    CUnitMange::a->KarionSoldier[2]->UnitSet(400, 112, L"a.SnoSTOP:0");
    CUnitMange::a->KarionSoldier[3]->UnitSet(242, 320, L"a.SnoSTOP:2");
    CUnitMange::a->KarionSoldier[4]->UnitSet(368, 320, L"a.SnoSTOP:1");

    CUnitMange::a->KarionSoldier2[0]->UnitSet(97, 144, L"a.SnoSTOP:1");
    CUnitMange::a->KarionSoldier2[1]->UnitSet(512, 144, L"a.SnoSTOP:2");

    UI = CImageFile::New(MAKEINTRESOURCE(IDB_UI), L"IDB_UI");
    UIs.Set(0, 0, 0, 0, UI, RGB(255, 0, 255), CSprite::DrawType_Transparent);

    Textwin = CImageFile::New(MAKEINTRESOURCE(IDB_TEXTBOX), L"IDB_TEXTBOX");
    TW.Set(144, 175, 0, 0, Textwin, RGB(255, 0, 255), CSprite::DrawType_Transparent);

    CharTextwin = CImageFile::New(MAKEINTRESOURCE(IDB_NPCTEXTBOX), L"IDB_NPCTEXTBOX");
    CTW.Set(81, 175, 0, 0, CharTextwin, RGB(255, 0, 255), CSprite::DrawType_Transparent);
    //x+71,y+8
    TS.Set(152, 183, 488, 248, 16);
    TS2.Set(153, 183, 489, 248, 16);

}

InGameIntro2::~InGameIntro2()
{
    CImageFile::Delete(UI);

    CImageFile::Delete(MainMap.MapImg);
}

bool InGameIntro2::Sample()
{
    return false;
}

bool InGameIntro2::isChanged()
{
    return false;
}

void InGameIntro2::onFrameMove()
{
    int i = 10;
    if (tsno > 10) { i = 20; }
    CUnitMange::a->Ares->mUnitSprite.Update(i);
    CUnitMange::a->Ares->UnitState.Update(10);

    CUnitMange::a->Gonrad->mUnitSprite.Update(10);
    CUnitMange::a->Gonrad->UnitState.Update(10);
    
    CUnitMange::a->ArchBishop->mUnitSprite.Update(10);
    CUnitMange::a->ArchBishop->UnitState.Update(10);

    CUnitMange::a->Aerain->UnitState.Update(10);
    CUnitMange::a->Actum->UnitState.Update(10);
    for (int i = 0; i < 5; i++)
    {
        CUnitMange::a->KarionSoldier[i]->mUnitSprite.Update(10);
    }
    CUnitMange::a->KarionSoldier2[0]->mUnitSprite.Update(10);
    CUnitMange::a->KarionSoldier2[1]->mUnitSprite.Update(10);

    switch (tsno)
    {
    case (1)://아레스 애니메이션변경(우측)
        CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(m2);
        CUnitMange::a->Ares->mUnitSprite.m_AnimInst.anikeyNo = 1;
        CUnitMange::a->Ares->mUnitSprite.m_AnimInst.delayTime = 0;

        dt = 9;
        tsno++;
        break;
    case (2)://아레스 우측이동
        dt++;
        if (dt % 10 == 0)
        {
            dt = 0;
            if (CUnitMange::a->Ares->mUnitSprite.mDestX < 464)
            {
                CUnitMange::a->Ares->mUnitSprite.mDestX += 16;
            }
        }
        if (CUnitMange::a->Ares->mUnitSprite.mDestX == 368)
        {
            CUnitMange::a->KarionSoldier2[1]->mUnitSprite.ChangeAnimation(s0);
        }
        if (CUnitMange::a->Ares->mUnitSprite.mDestX == 400)
        {
            CUnitMange::a->KarionSoldier[0]->mUnitSprite.ChangeAnimation(s2);
        }
        if (CUnitMange::a->Ares->mUnitSprite.mDestX == 464)
        {//아레스 위로 이동
            CUnitMange::a->KarionSoldier[1]->mUnitSprite.ChangeAnimation(s2);
            if (dt == 9)//이동과 애니메이션 프레임 맞추기 위함
            {
                CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(m3);
                CUnitMange::a->Ares->mUnitSprite.m_AnimInst.anikeyNo = 1;
                CUnitMange::a->Ares->mUnitSprite.m_AnimInst.delayTime = 0;
                tsno++;
                // 현재 아레스 y좌표 288
            }
        }
        break;
    case(3)://아레스 위로
        dt++;
        if (dt % 10 == 0)
        {
            dt = 0;
            if (CUnitMange::a->Ares->mUnitSprite.mDestY > 192)
            {
                CUnitMange::a->Ares->mUnitSprite.mDestY -= 16;
            }
        }
        if (CUnitMange::a->Ares->mUnitSprite.mDestY == 224)
        {
            CUnitMange::a->Gonrad->mUnitSprite.ChangeAnimation(s1);
        }
        if (CUnitMange::a->Ares->mUnitSprite.mDestY == 192)
        {
            if (dt == 9)//이동과 애니메이션 프레임 맞추기 위함
            {
                CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s1);

                tsno++;
                Tboxnum++;
                // 현재 아레스 y좌표 192
            }
        }
        break;
    case(4):
        Tbox = true;

        ClickEvent = true;
        if (Tboxnum == 3)
        {
            Tbox = false;
            ClickEvent = false;
            CUnitMange::a->Gonrad->mUnitSprite.ChangeAnimation(m2);
            dt = 9;
            CUnitMange::a->Gonrad->mUnitSprite.m_AnimInst.anikeyNo = 1;
            CUnitMange::a->Gonrad->mUnitSprite.m_AnimInst.delayTime = 0;
            tsno++;
        }
        break;
    case(5)://곤라드 위로
        dt++;
        if (dt % 10 == 0)
        {
            dt = 0;
            if (CUnitMange::a->Gonrad->mUnitSprite.mDestY > 80)
            {
                CUnitMange::a->Gonrad->mUnitSprite.mDestY -= 16;
            }

        }
        if (CUnitMange::a->Gonrad->mUnitSprite.mDestY == 80)
        {
            if (dt == 9)//이동과 애니메이션 프레임 맞추기 위함
            {
                CUnitMange::a->Gonrad->mUnitSprite.ChangeAnimation(m1);

                dt = 9;
                CUnitMange::a->Gonrad->mUnitSprite.m_AnimInst.anikeyNo = 1;
                CUnitMange::a->Gonrad->mUnitSprite.m_AnimInst.delayTime = 0;
                tsno++;

                // 현재 곤라드 y좌표 80
            }
        }
        break;
    case(6)://곤라드 16x8 만큼 오른쪽
        dt++;
        if (dt % 10 == 0)
        {
            dt = 0;
            if (CUnitMange::a->Gonrad->mUnitSprite.mDestX < 336 + 128)
            {
                CUnitMange::a->Gonrad->mUnitSprite.mDestX += 16;
            }
        }
        if (CUnitMange::a->Gonrad->mUnitSprite.mDestX == 336 + 128)
        {
            if (dt == 9)
            {
                CUnitMange::a->Gonrad->mUnitSprite.ChangeAnimation(m0);

                dt = 9;
                CUnitMange::a->Gonrad->mUnitSprite.m_AnimInst.anikeyNo = 1;
                CUnitMange::a->Gonrad->mUnitSprite.m_AnimInst.delayTime = 0;
                tsno++;


            }   //현재 곤라드 x좌표 464
        }
        break;
    case(7)://곤라드 16x8 만큼 이동
        dt++;
        if (dt % 10 == 0)
        {
            dt = 0;
            if (CUnitMange::a->Gonrad->mUnitSprite.mDestY < 80 + 48)
            {
                CUnitMange::a->Gonrad->mUnitSprite.mDestY += 16;
            }
        }
        if (CUnitMange::a->Gonrad->mUnitSprite.mDestY == 80 + 48)
        {
            if (dt == 9)//이동과 애니메이션 프레임 맞추기 위함
            {
                CUnitMange::a->Gonrad->mUnitSprite.ChangeAnimation(s0);


                tsno++;
                
                // 현재 곤라드 y좌표 128
            }
        }
        break;
    case(8):
        Tbox = true;
        ClickEvent = true;
        if (Tboxnum == 4)
        {
            Tbox = false;
            ClickEvent = false;
            CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s0);
            dt = 0;
            tsno++;
        }

        break;
    case(9):
        dt++;
        if (dt == 4)
        {
            CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s1);
        }
        if (dt == 8)
        {
            CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s2);
        }
        if (dt == 12)
        {
            CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s1);
        }
        if (dt == 16)
        {
            CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s2);
        }
        if (dt == 20)
        {
            CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s3);
            

        }
        if (dt == 24)
        {
            dt = 0;
            tsno++;
        }
        break;
    case(10):
        Tbox = true;
        ClickEvent = true;
        if (Tboxnum == 6)
        {
            Tbox = false;
            ClickEvent = false;
            
            dt = 0;
            tsno++;
        }
        break;
    case(11):
        dt++;
        if (dt == 4)
        {
            CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s3);
        }
        if (dt == 8)
        {
            CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s1);
        }
        if (dt == 12)
        {
            CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s0);
        }
        if (dt == 16)
        {
            CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s2);
        }
        if (dt == 20)
        {
            CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s3);
            

        }
        if (dt == 24)
        {
            dt = 0;
            tsno++;
        }
        break;
    case(12):
        Tbox = true;
        ClickEvent = true;
        if (Tboxnum == 10)
        {
            Tbox = false;
            ClickEvent = false;


            CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(m0);
            CUnitMange::a->Ares->mUnitSprite.m_AnimInst.anikeyNo = 1;
            CUnitMange::a->Ares->mUnitSprite.m_AnimInst.delayTime = 0;
            tsno++;
        
                
            
        }
        break;
    case(13)://아레스 아래로 이동
        dt++;
        if (dt % 5 == 0)
        {
            dt = 0;
            if (CUnitMange::a->Ares->mUnitSprite.mDestY < 288)
            {
                CUnitMange::a->Ares->mUnitSprite.mDestY += 16;
            }
        }
        if (CUnitMange::a->Ares->mUnitSprite.mDestY == 288)
        {
            if (dt == 4)//이동과 애니메이션 프레임 맞추기 위함
            {
                CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(m1);
                CUnitMange::a->Ares->mUnitSprite.m_AnimInst.anikeyNo = 1;
                CUnitMange::a->Ares->mUnitSprite.m_AnimInst.delayTime = 0;
                tsno++;
                // 현재 아레스 y좌표 288
            }
        }
        break;
    case(14):
        dt++;
        if (dt % 5 == 0)
        {
            dt = 0;
            if (CUnitMange::a->Ares->mUnitSprite.mDestX > 304)
            {
                CUnitMange::a->Ares->mUnitSprite.mDestX -= 16;
            }
        }
        if (CUnitMange::a->Ares->mUnitSprite.mDestX == 304)
        {
            if (dt == 4)//이동과 애니메이션 프레임 맞추기 위함
            {
                CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(m0);
                CUnitMange::a->Ares->mUnitSprite.m_AnimInst.anikeyNo = 1;
                CUnitMange::a->Ares->mUnitSprite.m_AnimInst.delayTime = 0;
                tsno++;
                //  현재 아레스 좌표 304 288
            }
        }
        break;
    case(15):
        dt++;
        if (dt % 5 == 0)
        {
            dt = 0;
            if (CUnitMange::a->Ares->mUnitSprite.mDestY < 320)
            {
                CUnitMange::a->Ares->mUnitSprite.mDestY += 16;
            }
        }
        break;
    default:
        break;
    }
    
}

void InGameIntro2::onDraw(HDC hdc)
{
    mBG.Draw(hdc);
    {
    CUnitMange::a->Ares->mUnitSprite.Draw(hdc);
    CUnitMange::a->Gonrad->mUnitSprite.Draw(hdc);
    CUnitMange::a->ArchBishop->mUnitSprite.Draw(hdc);
    CUnitMange::a->Aerain->mUnitSprite.Draw(hdc);
    for (int i = 0; i < 5; i++)
    {
        CUnitMange::a->KarionSoldier[i]->mUnitSprite.Draw(hdc);
    }
    CUnitMange::a->KarionSoldier2[0]->mUnitSprite.Draw(hdc);
    CUnitMange::a->KarionSoldier2[1]->mUnitSprite.Draw(hdc);
    }

    UIs.Draw(hdc);
    {//폰트 설정
        LoadString(CApplication::theApp->mhInst, IDS_CUT2 + Tboxnum, str, 512);
        SetBkMode(hdc, TRANSPARENT);
        HFONT hFont, oldFont;
        hFont = CreateFontW(16, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("바탕체"));
        oldFont = (HFONT)SelectObject(hdc, hFont);
    }

    if(tsno==0)
    {
        TW.Draw(hdc);
        SetTextAlign(hdc, TA_CENTER);
        TextOut(hdc, 326, 192, str, wcslen(str));
        TextOut(hdc, 327, 192, str, wcslen(str));
        SetTextAlign(hdc, TA_LEFT);
    }
    else if (Tbox)
    {
        //CTW.Draw(hdc);
        TS.Draw(hdc, str, 1);
        switch (Tboxnum)
        {
        case(1):CUnitMange::a->Ares->UnitState.Draw(hdc);
            break;
        case(2):CUnitMange::a->Actum->UnitState.Draw(hdc);
            break;
        case(3):CUnitMange::a->Gonrad->UnitState.Draw(hdc);
            break;
        case(4):CUnitMange::a->Ares->UnitState.Draw(hdc);
            break;
        case(5):CUnitMange::a->Gonrad->UnitState.Draw(hdc); 
            break;
        case(6):CUnitMange::a->Ares->UnitState.Draw(hdc); 
            break;
        case(7):CUnitMange::a->Gonrad->UnitState.Draw(hdc); 
            break;
        case(8):CUnitMange::a->Ares->UnitState.Draw(hdc); 
            break;
        case(9):CUnitMange::a->ArchBishop->UnitState.Draw(hdc); 
            break;
        case(10):CUnitMange::a->Aerain->UnitState.Draw(hdc);
            break;
        case(11):CUnitMange::a->Ares->UnitState.Draw(hdc);
            break;
        default:
            break;
        }
        //CUnitMange::a->Ares->UnitState.Draw(hdc);
        //CUnitMange::a->Gonrad->UnitState.Draw(hdc);
        //CUnitMange::a->ArchBishop->UnitState.Draw(hdc);
        //CUnitMange::a->Aerain->UnitState.Draw(hdc);


       // TS.OutPut(hdc, str);
       // TS2.OutPut(hdc, str);
    }
   
    
}




void InGameIntro2::onKeyDown(UINT virtual_key)
{
    switch (virtual_key)
    {
    case(VK_DOWN):
        CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(m0);
        break;
    case(VK_LEFT):
        CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(m1);
        break;
    case(VK_RIGHT):
        CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(m2);
        
        break;
    case(VK_UP):
        CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(m3);
        break;
    default:
        break;
    }
}

void InGameIntro2::onMouseDown(UINT x, UINT y, UINT left_right)
{
    switch (left_right)
    {
    case(MK_LBUTTON):
        if (ClickEvent)
        {
            if(Tbox)
            {
                Tboxnum++;
            }
            else 
            {
                tsno++;
                ClickEvent = false;
            }
        }
        break;
    default:
        break;
    }
}
