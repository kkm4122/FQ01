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
   {L"-아-아! 으~!···괴, 괴롭다~!",
    L"내 혼에 열을 불어 넣지 않으면",
    L"이몸은 곧 사라져 버릴텐데···!",
    L"···오! 북쪽에서 열기가 느껴 지는군!",
    L" 서둘러야겠다.열기를 따라 내 혼을 북쪽으로···!"
} });
    IntroT.push_back({
    151,140,{ 0,0,0,0,0 },0,
   {L"옛날에 로그리스는 천지의 영혼들이 다스렷다.",
    L"그러나 인간들이 들어오게 되자,",
    L"원래 주인이던 영혼들은 차츰 몸을 숨겼다."
} });
    IntroT.push_back({
    60,120,{ 0,0,0,0,0 },0,
   {L"영토를 둘러싼 사람들의 분쟁은 끊이지 않았으나",
    L"서로 협력하고 자제하며 평화를 지켜가고 있었다."
} });
    IntroT.push_back({
    180,260,{ 0,0,0,0,0 },0,
   {L"그리고 이 모든 나라를 통합하는 대표로서",
    L"바르시아의 왕 [제넬루]가 뽑혔다.",
    L"",
    L"바르시아는 로그리스 중앙과 북쪽에",
    L"거대한 영토를 가진 대국이었다."
} });
    IntroT.push_back({
    140,90,{ 0,0,0,0,0 },0,
   {L"그러나 나라면적에 비해 인구가 부족해",
    L"늘 침략의 위험이 도사리고 있었다.",
    L"",
    L"하지만 제넬루는 마법을 이용해 강한 성과 요새를",
    L"여러 곳에 쌓고 영토를 단단히 지켰다."
} });
    IntroT.push_back({
    75,300,{ 0,0,0,0,0 },0,
   {L"그런 제넬루왕의 태도가 돌변한 것은 대륙에서 건너온",
    L"     마법사 [자닐]이 참모가 되고부터 였다.",
    L"",
    L"어느새 [바르시아]의 병사는 급격히 늘어 났다."
} });
    IntroT.push_back({
    100,300,{ 0,0,0,0,0 },0,
   {L"바르시아의 주민은 주변국가로 탈출하기 시작했다.",
    L"그들은 외쳤다.",
    L"\" 왕은 악마에게 마음을 팔아 변해 버렸다! \" 라고..."
} });
    IntroT.push_back({
    130,90,{ 0,0,0,0,0 },0,
   {L"바르시아성에서는 음침한 소리가 퍼지고",
    L"그 소리는 살아있는 것들을 미치게 했다.",
    L"",
    L"제넬루는 사람들을 뒤에서 조종하고,",
    L"마법의 힘으로 병사를 만들어 내는데 성공했다.",
} });
    IntroT.push_back({
    145,200,{ 0,0,0,0,0 },0,
   {L"각 영주들은 서둘러 영토를 지키는데......",
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
    //페이드인
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
    //텍스트 출력
    else if (CurrentText->Introlast < 50)
    {

        
        CurrentText->Introlast++;
    }
    else if (CurrentText->Introlast == 50)
    {
        //텍스트 출력 후 대기시간
        if (Fadein == false && Fout.mAlpha < 255)
        {
            Fout.mAlpha += 5;
        }
        if (Fout.mAlpha >= 255)
        {
            Fout.mAlpha = 255;
            CurrentText->Introlast++;
        }
        //페이드 아웃
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

    int f = 20;//글자 간격(세로)  폰트 사이즈=f-3로 설정되어 
    //17사이즈의 폰트를 그리고 다음줄 문자열의 좌표는 20으로 글자 간 간격은 3픽셀 정도 차이남

    SetBkMode(hdc, TRANSPARENT);
    
    HFONT hFont, oldFont;
    hFont = CreateFontW(f-3, 0, 0, 0, 400, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("궁서"));
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
