#include "pch.h"
#include "resource.h"
#include "CSaveData.h"
#include "CImageFile.h"
#include "CSaveLoad.h"
/*
{
    {391, 391, L"������/����"},
    { 80, 391, L"������/����" },
    { 10, 391, L"ī���¼�" },
    { 8, 391, L"ī���¼�" }
};
*/




const WCHAR* text = { L"�����ٶ󸶹ٻ������īŸ���ϰ����ٶ󸶹ٻ������īŸ����" };
std::vector<CSaveData> Data = {};
CSaveLoad::CSaveLoad()
{
    mCharFile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_ANISAMPLE),L"MOVE_CHAR");
    mCharFile.ani = new CAnimation;
    mCharFile.ani->CreateAniW(mCharFile.imgFile->Width(), mCharFile.imgFile->Height(), 4, 4, 100);
   
    
    mCharSprite.Set2(L"a.Sno:0",0,0,mCharFile.ani,mCharFile.imgFile,RGB(255,0,255),CSprite::DrawType_Transparent);
    //mCharSprite


    SaveLoadImage = CImageFile::New(MAKEINTRESOURCE(IDB_SAVELOAD),L"IDB_SAVELOAD");
    mBG.Set(0, 0, 0, 0, SaveLoadImage, 0, CSprite::DrawType_Draw);
    Data.push_back({ 391, L"������/����" });//sprintf�� ī�� (str50 ����) str 
    Data.push_back({ 80, L"������/����" });
    Data.push_back({ 10, L"ī���¼�" });
    Data.push_back({ 8, L"ī���¼�" });
    asdf.Set(152, 183, 488, 248, 16);
}

CSaveLoad::~CSaveLoad()
{
    //delete SaveLoadImage;
    CImageFile::Delete(SaveLoadImage);
    CImageFile::Delete(mCharFile.imgFile);
    delete mCharFile.ani;
}

bool CSaveLoad::Sample()
{
    return samplechange;
}

bool CSaveLoad::isChanged()
{
    return NextScene;
}

void CSaveLoad::onFrameMove()
{
    
    mCharSprite.Update(10);
    
    
}

void CSaveLoad::onMouseMove(UINT x, UINT y)
{
    if (x >= 205 && x<=437)
    {
        if ( y <= 193) { YboxPos = 0; }
        else if (y > 193 && y <= 209) { YboxPos = 1; }
        else if (y > 209 && y <= 225) { YboxPos = 2; }
        else if (y>225&& y<=241){ YboxPos = 3; }
        else if (y > 257 && y <= 273) { YboxPos = 5; }
    }
}
std::wstring l = L"a.Sno:1";//L"char_L";
std::wstring r = L"a.Sno:2";//L"char_R";
std::wstring f = L"a.Sno:0";//L"char_F";
std::wstring b = L"a.Sno:3";//L"char_B";

//L"a.Sno:%d"
void CSaveLoad::onKeyDown(UINT virtual_key)
{
    switch (virtual_key)
    {
    case(VK_RETURN):
        NextScene = true;
        break;
    case(VK_LEFT):


        mCharSprite.ChangeAnimation(l);
        mCharSprite.mDestX -= 16;
        break;
    case(VK_RIGHT):


        mCharSprite.ChangeAnimation(r);
        mCharSprite.mDestX += 16;
        break;
    case(VK_UP):


        mCharSprite.ChangeAnimation(b);
        mCharSprite.mDestY -= 16;
        break;

    case(VK_DOWN):


        mCharSprite.ChangeAnimation(f);
        mCharSprite.mDestY += 16;
        break;
    case(VK_SPACE):
        samplechange = true;
        break;
    default:
        break;
    }
}

void CSaveLoad::onMouseDown(UINT x, UINT y, UINT left_right)
{
    switch (left_right)
    {
    case(MK_LBUTTON):
        if (y > 257 && y <= 273)
        {
            NextScene = true;
        }
        break;
    default:
        break;
    }
}

void CSaveLoad::SetScene()
{
}

    


void CSaveLoad::onDraw(HDC hdc)
{
    WCHAR right_text[8];
    
    mBG.Draw(hdc);
    mCharSprite.Draw(hdc);
    int font = 15;
    HPEN myPen = (HPEN)CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
    HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
    HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
    SetBkMode(hdc, TRANSPARENT);
    Rectangle(hdc, 206, 177 + (YboxPos*16), 437, 193+ (YboxPos * 16)); SelectObject(hdc, oldBrush);

    HFONT hFont, oldFont;
    hFont = CreateFontW(font, 0, 0, 0, 400, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("����"));
    oldFont = (HFONT)SelectObject(hdc, hFont);
    SetTextColor(hdc, RGB(227, 97, 0));
    TextOut(hdc, 225, 129, L"���� ����� ����", 10);
    TextOut(hdc, 226, 129, L"���� ����� ����", 10);
    for (int i = 0; i < 4; i++)
    {
        swprintf_s(right_text, 8, L"%d��", Data[i].PlayTime);
        SetTextColor(hdc, RGB(0, 0, 0));
        TextOut(hdc, 225, 177 + (i * (font + 1)), Data[i].way, wcslen(Data[i].way));
        SetTextColor(hdc, RGB(0, 113, 130));
        TextOut(hdc, 226, 177 + (i * (font + 1)), Data[i].way, wcslen(Data[i].way));

        SetTextAlign(hdc, TA_RIGHT);
        SetTextColor(hdc, RGB(0, 0, 0));
        TextOut(hdc, 425, 177 + (i * (font + 1)), right_text, wcslen(right_text));
        SetTextColor(hdc, RGB(0, 113, 130));
        TextOut(hdc, 426, 177 + (i * (font + 1)), right_text, wcslen(right_text));

        SetTextAlign(hdc, TA_LEFT);//���ʿ��� ���������� ���
    }
    SetTextColor(hdc, RGB(0, 0, 0));
    TextOut(hdc, 225, 257, L"ó������", 5);
    SetTextColor(hdc, RGB(0, 113, 130));
    TextOut(hdc, 226, 257, L"ó������", 5);
    //RECT rc1 = { 100, 100, 200, 200 };
    SetTextColor(hdc, RGB(0,0,0));
    //DrawText(hdc,text,wcslen(text),&rc1, DT_WORDBREAK);
    //asdf.OutPut(hdc, text);
    DeleteObject(myBrush);
    DeleteObject(myPen);
    SelectObject(hdc, oldFont);
    DeleteObject(hFont);
    mCharSprite.Draw(hdc);
    
}

