#include "pch.h"
#include "CUnitMange.h"
#include "CImageFile.h"
#include "CApplication.h"
#include "InGameIntro2.h"


/*  
* ��¼���
    ��
    �ι� 
    UI 
    �ؽ�Ʈâ
    ��Ʈ�� �ؽ�Ʈ ��
    
*��Ʈ�� ���� ��ǥ
    UI ��ǥ           0     0
    ī���¼� ��ǥ      16     48
    �Ʒ���            304      288
    ������            304      288+80  368
    ����            336      112
    ���ֱ�            242      80
    ����1[0]          208     112
    ����1[1]          272     112
    ����1[2]          400     112
    ����1[3]�������ֽ� 242    320
    ����1[4]�����ֽ�  368     320
    ����2[0]�������ֽ� 97     144
    ����2[1]�����ֽ�  512     144

*/

std::wstring m0 = L"a.Sno:0";//�Ʒ�
std::wstring m1 = L"a.Sno:1";//����
std::wstring m2 = L"a.Sno:2";//������
std::wstring m3 = L"a.Sno:3";//��
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
    CUnitMange::a->Gonrad->Facing = true;
    
    CUnitMange::a->ArchBishop->UnitSet(242, 80, L"a.Sno:0");
    
    CUnitMange::a->Aerain->UnitSet(304, 384, L"a.SnoSTOP:3");

    CUnitMange::a->KarionSoldier[0]->UnitSet(208, 112, L"a.SnoSTOP:0");
    CUnitMange::a->KarionSoldier[1]->UnitSet(272, 112, L"a.SnoSTOP:0");
    CUnitMange::a->KarionSoldier[2]->UnitSet(400, 112, L"a.SnoSTOP:0");
    CUnitMange::a->KarionSoldier[3]->UnitSet(242, 320, L"a.SnoSTOP:2");
    CUnitMange::a->KarionSoldier[4]->UnitSet(368, 320, L"a.SnoSTOP:1");
    for (int i = 0; i < 5; i++)
    {
        CUnitMange::a->KarionSoldier[i]->Facing = true;
        
    }
    CUnitMange::a->KarionSoldier2[0]->UnitSet(97, 144, L"a.SnoSTOP:1");
    CUnitMange::a->KarionSoldier2[1]->UnitSet(512, 144, L"a.SnoSTOP:2");
    CUnitMange::a->KarionSoldier2[0]->Facing = true;
    CUnitMange::a->KarionSoldier2[1]->Facing = true;
    
    UI = CImageFile::New(MAKEINTRESOURCE(IDB_UI), L"IDB_UI");
    UIs.Set(0, 0, 0, 0, UI, RGB(255, 0, 255), CSprite::DrawType_Transparent);

    Textwin = CImageFile::New(MAKEINTRESOURCE(IDB_TEXTBOX), L"IDB_TEXTBOX");
    TW.Set(144, 175, 0, 0, Textwin, RGB(255, 0, 255), CSprite::DrawType_Transparent);

    CharTextwin = CImageFile::New(MAKEINTRESOURCE(IDB_NPCTEXTBOX), L"IDB_NPCTEXTBOX");
    CTW.Set(81, 175, 0, 0, CharTextwin, RGB(255, 0, 255), CSprite::DrawType_Transparent);
    //x+71,y+8
    TS.Set(160, 191, 488, 256, 16);
    TS2.Set(161, 191, 489, 256, 16);

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
    return NextScene;
}

void InGameIntro2::onFrameMove()
{
    int i = 10;
    if (tsno > 10) { i = 20; }
    CUnitMange::a->Ares->mUnitSprite.Update(i);
    CUnitMange::a->Ares->UnitState.Update(10);

    CUnitMange::a->Gonrad->mUnitSprite.Update(10);
    CUnitMange::a->Gonrad->UnitState.Update(10);
    CUnitMange::a->Gonrad->FacingTarget(CUnitMange::a->Ares);
    
    CUnitMange::a->ArchBishop->mUnitSprite.Update(10);
    CUnitMange::a->ArchBishop->UnitState.Update(10);

    CUnitMange::a->Aerain->mUnitSprite.Update(10);
    CUnitMange::a->Aerain->UnitState.Update(10);
    CUnitMange::a->Actum->UnitState.Update(10);
    for (int i = 0; i < 5; i++)
    {
        CUnitMange::a->KarionSoldier[i]->mUnitSprite.Update(10);
        CUnitMange::a->KarionSoldier[i]->FacingTarget(CUnitMange::a->Ares);
    }
    CUnitMange::a->KarionSoldier2[0]->mUnitSprite.Update(10);
    CUnitMange::a->KarionSoldier2[1]->mUnitSprite.Update(10);
    CUnitMange::a->KarionSoldier2[0]->FacingTarget(CUnitMange::a->Ares);
    CUnitMange::a->KarionSoldier2[1]->FacingTarget(CUnitMange::a->Ares);

    switch (tsno)
    {
    case (1)://�Ʒ��� �ִϸ��̼Ǻ���(����)
        CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(m2);
        CUnitMange::a->Ares->mUnitSprite.m_AnimInst.anikeyNo = 1;
        CUnitMange::a->Ares->mUnitSprite.m_AnimInst.delayTime = 0;

        dt = 9;
        tsno++;
        break;
    case (2)://�Ʒ��� �����̵�
        dt++;
        if (dt % 10 == 0)
        {
            dt = 0;
            if (CUnitMange::a->Ares->mUnitSprite.mDestX < 464)
            {
                CUnitMange::a->Ares->mUnitSprite.mDestX += 16;
            }
        }
        
        if (CUnitMange::a->Ares->mUnitSprite.mDestX == 464)
        {//�Ʒ��� ���� �̵�
            
            if (dt == 9)//�̵��� �ִϸ��̼� ������ ���߱� ����
            {
                CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(m3);
                CUnitMange::a->Ares->mUnitSprite.m_AnimInst.anikeyNo = 1;
                CUnitMange::a->Ares->mUnitSprite.m_AnimInst.delayTime = 0;
                tsno++;
                // ���� �Ʒ��� y��ǥ 288
            }
        }
        break;
    case(3)://�Ʒ��� ����
        dt++;
        if (dt % 10 == 0)
        {
            dt = 0;
            if (CUnitMange::a->Ares->mUnitSprite.mDestY > 192)
            {
                CUnitMange::a->Ares->mUnitSprite.mDestY -= 16;
            }
        }
        
        if (CUnitMange::a->Ares->mUnitSprite.mDestY == 192)
        {
            if (dt == 9)//�̵��� �ִϸ��̼� ������ ���߱� ����
            {
                CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s1);

                tsno++;
                Tboxnum++;
                // ���� �Ʒ��� y��ǥ 192
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
            CUnitMange::a->Gonrad->Facing = false;
            CUnitMange::a->Gonrad->mUnitSprite.ChangeAnimation(m3);
            dt = 9;
            CUnitMange::a->Gonrad->mUnitSprite.m_AnimInst.anikeyNo = 1;
            CUnitMange::a->Gonrad->mUnitSprite.m_AnimInst.delayTime = 0;
            tsno++;
        }
        break;
    case(5)://���� ����
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
            if (dt == 9)//�̵��� �ִϸ��̼� ������ ���߱� ����
            {
                CUnitMange::a->Gonrad->mUnitSprite.ChangeAnimation(m2);

                dt = 9;
                CUnitMange::a->Gonrad->mUnitSprite.m_AnimInst.anikeyNo = 1;
                CUnitMange::a->Gonrad->mUnitSprite.m_AnimInst.delayTime = 0;
                tsno++;

                // ���� ���� y��ǥ 80
            }
        }
        break;
    case(6)://���� 16x8 ��ŭ ������
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


            }   //���� ���� x��ǥ 464
        }
        break;
    case(7)://���� 16x8 ��ŭ �̵�
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
            if (dt == 9)//�̵��� �ִϸ��̼� ������ ���߱� ����
            {
                CUnitMange::a->Gonrad->mUnitSprite.ChangeAnimation(s0);


                tsno++;
                
                // ���� ���� y��ǥ 128
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
    case(13)://�Ʒ��� �Ʒ��� �̵�
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
            if (dt == 4)//�̵��� �ִϸ��̼� ������ ���߱� ����
            {
                CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(m1);
                CUnitMange::a->Ares->mUnitSprite.m_AnimInst.anikeyNo = 1;
                CUnitMange::a->Ares->mUnitSprite.m_AnimInst.delayTime = 0;
                tsno++;
                // ���� �Ʒ��� y��ǥ 288
            }
        }
        break;
    case(14)://�Ʒ��� �·� �̵�
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
            if (dt == 4)//�̵��� �ִϸ��̼� ������ ���߱� ����
            {
                CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(m0);
                CUnitMange::a->Ares->mUnitSprite.m_AnimInst.anikeyNo = 1;
                CUnitMange::a->Ares->mUnitSprite.m_AnimInst.delayTime = 0;
                tsno++;
                //  ���� �Ʒ��� ��ǥ 304 288
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
        if (CUnitMange::a->Ares->mUnitSprite.mDestY == 320)
        {
            if (dt == 4)
            {
                CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(s0);
                CUnitMange::a->Aerain->mUnitSprite.ChangeAnimation(m3);
                tsno++;
                //  ���� �Ʒ��� ��ǥ 304 320
            }
        }
        break;
    case(16):
        dt++;
        if (dt % 5 == 0)
        {
            dt = 0;
            if (CUnitMange::a->Aerain->mUnitSprite.mDestY > 352)
            {
                CUnitMange::a->Aerain->mUnitSprite.mDestY -= 16;
            }
        }
        if (CUnitMange::a->Aerain->mUnitSprite.mDestY == 352)
        {
            if (dt == 4)
            {
                CUnitMange::a->Aerain->mUnitSprite.ChangeAnimation(s3);

                tsno++;
                //Tboxnum++;
            }
        }
        break;
    case(17):
        Tbox = true;
        ClickEvent = true;
        if (Tboxnum == 12)
        {
            Tbox = false;
            ClickEvent = false;
            CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(m2);
            CUnitMange::a->Ares->mUnitSprite.m_AnimInst.anikeyNo = 1;
            CUnitMange::a->Ares->mUnitSprite.m_AnimInst.delayTime = 0;
            tsno++;
            //�Ʒ��� ��ǥ 304 320
        }
        break;
    case(18):
        dt++;
        if (dt % 5 == 0)
        {
            dt = 0;
            if (CUnitMange::a->Ares->mUnitSprite.mDestX < 336)
            {
                CUnitMange::a->Ares->mUnitSprite.mDestX += 16;
            }
        }
        if (CUnitMange::a->Ares->mUnitSprite.mDestX == 336)
        {
            if (dt == 4)//�̵��� �ִϸ��̼� ������ ���߱� ����
            {
                CUnitMange::a->Ares->mUnitSprite.ChangeAnimation(m0);
                CUnitMange::a->Ares->mUnitSprite.m_AnimInst.anikeyNo = 1;
                CUnitMange::a->Ares->mUnitSprite.m_AnimInst.delayTime = 0;
                tsno++;
                CUnitMange::a->KarionSoldier[3]->Facing = false;
                CUnitMange::a->KarionSoldier[4]->Facing = false;
                //  ���� �Ʒ��� ��ǥ 336 320
            }
        }
        break;
    case(19)://�Ʒ��� �Ʒ��� �̵�
        dt++;
        if (dt % 5 == 0)
        {
            dt = 0;
            if (CUnitMange::a->Ares->mUnitSprite.mDestY < 388)
            {
                CUnitMange::a->Ares->mUnitSprite.mDestY += 16;
            }// ���� �Ʒ��� ��ǥ 336 388
            if (CUnitMange::a->Ares->mUnitSprite.mDestY >= 388)
            {
                if (CUnitMange::a->KarionSoldier[4]->mUnitSprite.mDestX > 336)
                    CUnitMange::a->KarionSoldier[4]->mUnitSprite.mDestX -= 16;
            }
            if (CUnitMange::a->KarionSoldier[4]->mUnitSprite.mDestX <= 336)
            {
                if (CUnitMange::a->KarionSoldier[3]->mUnitSprite.mDestX < 274)
                {
                    CUnitMange::a->KarionSoldier[3]->mUnitSprite.ChangeAnimation(s2);
                    CUnitMange::a->KarionSoldier[3]->mUnitSprite.mDestX += 16;
                }
            }
            if (CUnitMange::a->KarionSoldier[3]->mUnitSprite.mDestX >= 274)
            {
                CUnitMange::a->KarionSoldier[4]->mUnitSprite.ChangeAnimation(s0);
                CUnitMange::a->KarionSoldier[4]->mUnitSprite.mDestY += 16;
            }
            if (CUnitMange::a->KarionSoldier[4]->mUnitSprite.mDestY >= 352)
            {
                if (CUnitMange::a->KarionSoldier[3]->mUnitSprite.mDestX < 274) {
                    CUnitMange::a->KarionSoldier[3]->mUnitSprite.mDestX += 16;
                }
            }
            if (CUnitMange::a->KarionSoldier[3]->mUnitSprite.mDestX >= 274)
            {
                CUnitMange::a->KarionSoldier[3]->mUnitSprite.ChangeAnimation(s0);
                CUnitMange::a->KarionSoldier[3]->mUnitSprite.mDestY += 16;
            }
            if (CUnitMange::a->KarionSoldier[3]->mUnitSprite.mDestY >= 388)
            {
                NextScene = true;
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
    {//��Ʈ ����
        LoadString(CApplication::theApp->mhInst, IDS_CUT2 + Tboxnum, str, 512);
        SetBkMode(hdc, TRANSPARENT);
        HFONT hFont, oldFont;
        hFont = CreateFontW(16, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("����ü"));
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
