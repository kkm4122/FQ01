#include "pch.h"
#include "resource.h"
#include "CImageFile.h"
#include "CIntroScene.h"
#include "Ctext.h"

Ctext* CurrentText;
std::vector<Ctext> IntroT = {};

CIntroScene::CIntroScene()
{
    WCHAR ImgNo[10] = {};
    TitleImage =  CImageFile::New(MAKEINTRESOURCE(IDB_TITLE), L"IDB_LION");
    for (int i = 0; i < 9; i++)
    {
        swprintf_s(ImgNo, 10, L"INTRO_0%d", i);
        IntroImage[i] =  CImageFile::New(MAKEINTRESOURCE(Image_num+i),ImgNo);
    }
    Fadeout = new CImageFile(MAKEINTRESOURCE(IDB_BITMAP1),L"FADEOUT");
    Fout.Set(0, (540-Fadeout->Height())/4+8, 0, 0, Fadeout, 0, CSprite::DrawType_AlphaBlend);
    Fout.mAlpha = 255;
	mBG.Set(0, (540 - IntroImage[0]->Height())/4+8, 0,0,IntroImage[0],0,CSprite::DrawType_Draw);
    
    IntroT.push_back({
    151,280, { 0,0,0,0,0 },0,
   {L"-��-��! ��~!��������, ���Ӵ�~!",
    L"�� ȥ�� ���� �Ҿ� ���� ������",
    L"�̸��� �� ����� �����ٵ�������!",
    L"��������! ���ʿ��� ���Ⱑ ���� ���±�!",
    L" ���ѷ��߰ڴ�.���⸦ ���� �� ȥ�� �������Ρ�����!"
} });
    IntroT.push_back({
    151,140,{ 0,0,0,0,0 },0,
   {L"������ �α׸����� õ���� ��ȥ���� �ٽ��Ǵ�.",
    L"�׷��� �ΰ����� ������ ����,",
    L"���� �����̴� ��ȥ���� ���� ���� �����."
} });
    IntroT.push_back({
    60,120,{ 0,0,0,0,0 },0,
   {L"���並 �ѷ��� ������� ������ ������ �ʾ�����",
    L"���� �����ϰ� �����ϸ� ��ȭ�� ���Ѱ��� �־���."
} });
    IntroT.push_back({
    180,260,{ 0,0,0,0,0 },0,
   {L"�׸��� �� ��� ���� �����ϴ� ��ǥ�μ�",
    L"�ٸ��þ��� �� [���ڷ�]�� ������.",
    L"",
    L"�ٸ��þƴ� �α׸��� �߾Ӱ� ���ʿ�",
    L"�Ŵ��� ���並 ���� �뱹�̾���."
} });
    IntroT.push_back({
    140,90,{ 0,0,0,0,0 },0,
   {L"�׷��� ��������� ���� �α��� ������",
    L"�� ħ���� ������ ���縮�� �־���.",
    L"",
    L"������ ���ڷ�� ������ �̿��� ���� ���� �����",
    L"���� ���� �װ� ���並 �ܴ��� ���״�."
} });
    IntroT.push_back({
    75,300,{ 0,0,0,0,0 },0,
   {L"�׷� ���ڷ���� �µ��� ������ ���� ������� �ǳʿ�",
    L"     ������ [�ڴ�]�� ���� �ǰ���� ����.",
    L"",
    L"����� [�ٸ��þ�]�� ����� �ް��� �þ� ����."
} });
    IntroT.push_back({
    100,300,{ 0,0,0,0,0 },0,
   {L"�ٸ��þ��� �ֹ��� �ֺ������� Ż���ϱ� �����ߴ�.",
    L"�׵��� ���ƴ�.",
    L"\" ���� �Ǹ����� ������ �Ⱦ� ���� ���ȴ�! \" ���..."
} });
    IntroT.push_back({
    130,90,{ 0,0,0,0,0 },0,
   {L"�ٸ��þƼ������� ��ħ�� �Ҹ��� ������",
    L"�� �Ҹ��� ����ִ� �͵��� ��ġ�� �ߴ�.",
    L"",
    L"���ڷ�� ������� �ڿ��� �����ϰ�,",
    L"������ ������ ���縦 ����� ���µ� �����ߴ�.",
} });
    IntroT.push_back({
    145,200,{ 0,0,0,0,0 },0,
   {L"�� ���ֵ��� ���ѷ� ���並 ��Ű�µ�......",
    L"",
    L"",
    L"",
    L"",
} });
    //IntroT.push_back({0});
    CurrentText = &IntroT[0];
}

CIntroScene::~CIntroScene()
{
    for (int i = 0; i < 9; i++)
    {
        //delete IntroImage[i];
        CImageFile::Delete(IntroImage[i]);
    }
    CImageFile::Delete(TitleImage);
    //delete TitleImage;
    //delete Fadeout;
    CImageFile::Delete(Fadeout);
}

bool CIntroScene::Sample()
{
    return samplechange;
}

bool CIntroScene::isChanged()
{
	return NextScene;
}

void CIntroScene::onFrameMove()
{
    //wcslen(text1)
    Textframe++;
    if (Fadein == true && Fout.mAlpha > 0)
    {
        Fout.mAlpha -= 5;
        if (Fout.mAlpha <= 0) {
            Fout.mAlpha = 0;
            Fadein = false;
        }
    }
    //���̵���
    else if (CurrentText->IntroFrame[0] < wcslen(CurrentText->text[0]))
    {
        if (Textframe > 5)
        {
            CurrentText->IntroFrame[0]++;
            Textframe = 0;
        }
    }
    else if (CurrentText->IntroFrame[1] < wcslen(CurrentText->text[1]))
    {
        if (Textframe > 5)
        {
            CurrentText->IntroFrame[1]++;
            Textframe = 0;
        }
    }
    else if (CurrentText->IntroFrame[2] < wcslen(CurrentText->text[2]))
    {
        if (Textframe > 5)
        {
            CurrentText->IntroFrame[2]++;
            Textframe = 0;
        }
    }
    else if (CurrentText->IntroFrame[3] < wcslen(CurrentText->text[3]))
    {
        if (Textframe > 5)
        {
            CurrentText->IntroFrame[3]++;
            Textframe = 0;
        }
    }
    else if (CurrentText->IntroFrame[4] < wcslen(CurrentText->text[4]))
    {
        if (Textframe > 5)
        {
            CurrentText->IntroFrame[4]++;
            Textframe = 0;
        }
    }
    //�ؽ�Ʈ ���
    else if (CurrentText->Introlast < 50)
    {

        
        CurrentText->Introlast++;
    }
    else if (CurrentText->Introlast == 50)
    {
        //�ؽ�Ʈ ��� �� ���ð�
        if (Fadein == false && Fout.mAlpha < 255)
        {
            Fout.mAlpha += 5;
        }
        if (Fout.mAlpha >= 255)
        {
            Fout.mAlpha = 255;
            CurrentText->Introlast++;
        }
        //���̵� �ƿ�
    }
    else
    {
        for (int i = 0; i < 5; i++) {
            CurrentText->IntroFrame[i] = 0;
        }
        //Fout.mAlpha = 0;
        CurrentText->Introlast = 0;
        if (Intro_num < 8)
        {
            Text_num++;
            Intro_num++;
            //mBG.mAlpha = 0;
            //Fadein = true;
            mBG.Set(0, (540- IntroImage[Intro_num]->Height())/4+8, 0, 0, IntroImage[Intro_num], 0, CSprite::DrawType_Draw);

            CurrentText = &IntroT[Text_num];
        }
        else {
            /**/
            Text_num = 0;
            Intro_num = 0;
            //mBG.mAlpha = 0;
        
            mBG.Set(0, (540 - IntroImage[Intro_num]->Height()) / 4 + 8, 0, 0, IntroImage[Intro_num], 0, CSprite::DrawType_Draw);

            CurrentText = &IntroT[Text_num];
            Fout.mAlpha = 255;
            Fadein = true;
            /*
            mBG.Set(0, (540 - TitleImage->Height())/4, 0, 0, TitleImage, 0, CSprite::DrawType_Draw);
            //CurrentText = &IntroT[9];
            CurrentText = &IntroT[Text_num];
            *///NextScene = true;
        }
        Fadein = true;
    }
}

void CIntroScene::onDraw(HDC hdc)
{
   
    mBG.Draw(hdc);

    int f = 20;//���� ����(����)  ��Ʈ ������=f-3�� �����Ǿ� 
    //17�������� ��Ʈ�� �׸��� ������ ���ڿ��� ��ǥ�� 20���� ���� �� ������ 3�ȼ� ���� ���̳�

    SetBkMode(hdc, TRANSPARENT);
    
    HFONT hFont, oldFont;
    hFont = CreateFontW(f-3, 0, 0, 0, 400, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("�ü�"));
    oldFont = (HFONT)SelectObject(hdc, hFont);
    //TextOut(hdc, CurrentText->tx+1, CurrentText->ty+2, CurrentText->text[0], CurrentText->IntroFrame[0]);
    //TextOut(hdc, CurrentText->tx+1, CurrentText->ty+f+2, CurrentText->text[1], CurrentText->IntroFrame[1]);
    //TextOut(hdc, CurrentText->tx+1, CurrentText->ty+(f*2)+2, CurrentText->text[2], CurrentText->IntroFrame[2]);
    //TextOut(hdc, CurrentText->tx+1, CurrentText->ty+(f*3)+2, CurrentText->text[3], CurrentText->IntroFrame[3]);
    //TextOut(hdc, CurrentText->tx+1, CurrentText->ty+(f*4)+2, CurrentText->text[4], CurrentText->IntroFrame[4]);
    //TextOut(hdc, CurrentText->tx, CurrentText->ty, CurrentText->text[0], CurrentText->IntroFrame[0]);
    //TextOut(hdc, CurrentText->tx, CurrentText->ty+f, CurrentText->text[1], CurrentText->IntroFrame[1]);
    //TextOut(hdc, CurrentText->tx, CurrentText->ty+(f*2), CurrentText->text[2], CurrentText->IntroFrame[2]);
    //TextOut(hdc, CurrentText->tx, CurrentText->ty+(f*3), CurrentText->text[3], CurrentText->IntroFrame[3]);
    //TextOut(hdc, CurrentText->tx, CurrentText->ty+(f*4), CurrentText->text[4], CurrentText->IntroFrame[4]);
    for (int i = 0; i < 5; i++)
    {
        SetTextColor(hdc, RGB(0, 0, 0));
        TextOut(hdc, CurrentText->tx + 1, CurrentText->ty+(f*i) + 2, CurrentText->text[i], CurrentText->IntroFrame[i]);
        SetTextColor(hdc, RGB(200, 200, 200));
        TextOut(hdc, CurrentText->tx, CurrentText->ty + (f * i), CurrentText->text[i], CurrentText->IntroFrame[i]);
    }
    Fout.Draw(hdc);
    SelectObject(hdc, oldFont);
    DeleteObject(hFont);
    if (Intro_num==8)
    {

    }
}

void CIntroScene::onKeyDown(UINT virtual_key)
{
    switch (virtual_key)
    {
    case VK_RETURN:
        Text_num = 0;
        Intro_num = 0;
        //mBG.mAlpha = 0;
        mBG.Set(0, (540-TitleImage->Height())/4, 0, 0, TitleImage, 0, CSprite::DrawType_Draw);
        //CurrentText = &IntroT[9];
        CurrentText = &IntroT[Text_num];
       NextScene = true;
        break;
    case(VK_SPACE):
        samplechange = true;
        break;
    case VK_RIGHT:
        if (Intro_num < 8) {
            for (int i = 0; i < 5; i++) {
                CurrentText->IntroFrame[i] = 0;
            }
            
            CurrentText->Introlast = 0;
            Text_num++;
            Intro_num++;
            
            mBG.Set(0, (540 - IntroImage[Intro_num]->Height()) / 4+8 , 0, 0, IntroImage[Intro_num], 0, CSprite::DrawType_Draw);

            CurrentText = &IntroT[Text_num];
            Fout.mAlpha = 255;
            Fadein = true;
        }
        else
        {

            Text_num = 0;
            Intro_num = 0;
            //mBG.mAlpha = 0;
            mBG.Set(0, (540 - IntroImage[Intro_num]->Height()) / 4 + 8, 0, 0, IntroImage[Intro_num], 0, CSprite::DrawType_Draw);

            CurrentText = &IntroT[Text_num];
            Fout.mAlpha = 255;
            Fadein = true;
            /*
            mBG.Set(0, (540 - TitleImage->Height()) / 2, 0, 0, TitleImage, 0, CSprite::DrawType_Draw);
            *///NextScene = true;
        }
        break;
    }
}

void CIntroScene::SetScene()
{
}
