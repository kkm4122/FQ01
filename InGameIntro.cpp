#include "pch.h"
#include "CSprite.h"
#include "resource.h"
#include "CImageFile.h"
#include "CScreen.h"
#include "CApplication.h"
#include "InGameIntro.h"
int y = 160;
int suby = 0;

struct objPos
{
	int x;
	int y;
};
objPos CSPos[27] =
{ {217,143}, {417,143}//상단 병사 좌표
, {57,479}, {157,479}, {107,511}, {57,543}, {157,543}, {107,576}//좌측 병사 좌표
, {484,479}, {534,511}, {584,511}, {484,543}, {584,543}, {534,576}//우측 병사 좌표 14
, {236,776}, {286,792}, {351,792}, {400,776}, {269,842}, {319,842}, {369,842}//계단 밑 용사일행//라이오스 케크 가비 오라슨 미솔렌 사크 마레암
, {220,447}, {252,431}, {284,400}, {316,416}, {388,431}, {421,447}//왕좌 쪽 못난이들 오그2 스리후트2 자닐2 제넬루2 멕가이어3  몰드레드2
};
InGameIntro::InGameIntro()
{

	str = new WCHAR[512];
	MainMap.PosX = 5;
	MainMap.PosY = 47;
	MainMap.MapImg = CImageFile::New(MAKEINTRESOURCE(IDB_CASTLE), L"IDB_CASTLE");
	UI = CImageFile::New(MAKEINTRESOURCE(IDB_UI), L"IDB_UI");
	Textwin = CImageFile::New(MAKEINTRESOURCE(IDB_TEXTBOX), L"IDB_TEXTBOX");
	CharTextwin = CImageFile::New(MAKEINTRESOURCE(IDB_NPCTEXTBOX), L"IDB_NPCTEXTBOX");
	SubScrWin = CImageFile::New(MAKEINTRESOURCE(IDB_SUBSCR), L"IDB_SUBSCR");
	for (int i = 0; i < 14; i++)
	{
		if (i < 2)
		{
			obj[i].m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_SOLDIER), L"IDB_SOLDIER");
		}
		else if (i < 8)
		{
			obj[i].m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_SOLDIER_LEFT), L"IDB_SOLDIER_LEFT");
		}
		else if (i < 14)
		{
			obj[i].m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_SOLDIER_RIGHT), L"IDB_SOLDIER_RIGHT");
		}

	}
	/*for (int i = 14; i < 27; i++)
	{
		obj[i].m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_SOLDIER_RIGHT), L"IDB_SOLDIER_RIGHT");
	}*/

	obj[14].m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_CHAR_LAIOS2), L"IDB_CHAR_LAIOS2");
	obj[15].m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_CHAR_KECK1), L"IDB_CHAR_KECK1");
	obj[16].m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_CHAR_GABI1), L"IDB_CHAR_GABI1");
	obj[17].m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_CHAR_ORASON2), L"IDB_CHAR_ORASON2");
	obj[19].m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_CHAR_SARK3), L"IDB_SOLDIER_SARK3");
	obj[18].m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_CHAR_MYSOLEN2), L"IDB_CHAR_MYSOLEN2");
	obj[20].m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_CHAR_MAREAM2), L"IDB_CHAR_MAREAM2");

	obj[21].m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_CHAR_OGG2), L"IDB_CHAR_OGG2");
	obj[22].m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_CHAR_THRYHOOT2), L"IDB_CHAR_THRYHOOT2");
	obj[23].m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_CHAR_JANIL2), L"IDB_CHAR_JANIL2");
	obj[24].m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_CHAR_GENELU2), L"IDB_CHAR_GENELU2");
	obj[25].m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_CHAR_MACGAIA3), L"IDB_CHAR_MACGAIA3");
	obj[26].m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_CHAR_MOLDRED2), L"IDB_CHAR_MOLDRED2");
	//obj[27].m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_CHAR_GENELU2), L"IDB_CHAR_");

	sScWin.Set(184, 48, 0, 0, SubScrWin, RGB(255, 0, 255), CSprite::DrawType_Transparent);
	sScWin.mSrcHeight = 0;
	sSc.Set(0, 0, 5, 300, MainMap.MapImg, 0, CSprite::DrawType_Draw);
	mBG.Set(0, 0, MainMap.PosX, 0, MainMap.MapImg, 0, CSprite::DrawType_Draw);
	UIs.Set(0, 0, 0, 0, UI, RGB(255, 0, 255), CSprite::DrawType_Transparent);
	TW.Set(144, 175, 0, 0, Textwin, RGB(255, 0, 255), CSprite::DrawType_Transparent);
	CTW.Set(81, 175, 0, 0, CharTextwin, RGB(255, 0, 255), CSprite::DrawType_Transparent);
	for (int i = 0; i < 27; i++)
	{
		Sobj[i].Set(CSPos[i].x - MainMap.PosX, CSPos[i].y - MainMap.PosY, 0, 0, obj[i].m_anifile.imgFile, RGB(255, 0, 255), CSprite::DrawType_Transparent);
	}
	//SWobj[6]
	for (int i = 0; i < 6; i++)
	{
		SWobj[i].Set(CSPos[i+21].x - 5, CSPos[i+21].y - 300, 0, 0, obj[i+21].m_anifile.imgFile, RGB(255, 0, 255), CSprite::DrawType_Transparent);
	}
	TS.Set(152, 183, 488, 248, 16);
	TS2.Set(153, 183, 489, 248, 16);
	CTWC.Set(114- (obj[24].m_anifile.imgFile->Width()/2),207- (obj[24].m_anifile.imgFile->Height() / 2),0,0,obj[24].m_anifile.imgFile,RGB(255,0,255), CSprite::DrawType_Transparent);
}

InGameIntro::~InGameIntro()
{
	for (int i = 0; i < 27; i++)
	{
		//delete obj[i];
		CImageFile::Delete(obj[i].m_anifile.imgFile);
	}
	//delete CharTextwin;
	//delete Textwin;
	//delete UI;
	//delete MainMap;
	CImageFile::Delete(CharTextwin);
	CImageFile::Delete(Textwin);
	CImageFile::Delete(UI);
	CImageFile::Delete(MainMap.MapImg);
	delete str;
}

bool InGameIntro::Sample()
{
	return samplechange;
}

bool InGameIntro::isChanged()
{
	return NextScene;
}

void InGameIntro::onFrameMove()
{
	switch (tsno)
	{
	case(1):
		if (mBG.mDestY > -483)
		{
			MainMap.PosY -= 16;
			anim = true;
		}
		else if (y >= -15)
		{
			y -= 2;
			suby = suby + 2;
			anim = true;
		}
		else if(SWobj[3].mDestY<=151)
		{
			SWobj[3].mDestY += 8;
		}
		else
		{
			anim = false;
			tsno++;
			Tboxnum++;
			
		}
		break;
	case(2):
		Tbox = true;
		
		if (Tboxnum == 3) {
			anim = true;
			Tbox = false;
			tsno++;
		}
		break;
	case(3):
		anim = true;
		Tbox = false;
		if (Tboxnum==3&&Sobj[15].mDestY >= 262)
		{
			Sobj[15].mDestY -= 8;
		}
		else
		{
			Tbox = true;
			anim = false;
		}
		if (Tboxnum == 4)
		{
			Tbox = false;
			anim = true;
			if (SWobj[3].mDestY >= 124)
			{
				SWobj[3].mDestY -= 8;
			}
			else if (Sobj[15].mDestY<=287)
			{
				Sobj[15].mDestY += 8;
			}
			else
			{
				Tbox = true;
				anim = false;
				tsno++;
			}
			//if
		}
		
		break;
	case(4):
		if (Tboxnum == 9)
		{
			Tbox = false;
			anim = true;
			if (SWobj[3].mDestY <= 151)
			{
				SWobj[3].mDestY += 8;
			}
			else 
			{
				Tbox = true;
				anim = false;
			}
		}
		if (Tboxnum == 11)
		{
			Tbox = false;
			anim = true;
			if (SWobj[3].mDestY <= 183)
			{
				SWobj[3].mDestY += 8;
			}
			else if (Sobj[19].mDestY >= 229)
			{
				Sobj[19].mDestY -= 8;
			}
			else
			{
				Tbox = true;
				anim = false;
			}
		}
		if (Tboxnum ==14)
		{
			Tbox = false;
			anim = true;
			if (SWobj[3].mDestY >= 151)
			{
				SWobj[3].mDestY -= 8;
			}
			else
			{
				Tbox = true;
				anim = false;
			}
		}
		if (Tboxnum == 18)
		{
			NextScene = true;
		}
		break;
	default:
		break;
	}
	if (sScWin.mSrcHeight <= 175) 
	{
		sScWin.mSrcHeight = suby;
	}
	
	mBG.mDestY = MainMap.PosY;
	for (int i = 0; i < 27; i++)
	{
		if(tsno<2)Sobj[i].mDestY = CSPos[i].y + (MainMap.PosY);	//Sprite 안에있는 매개변수(좌표)를 직접 변경
	}

}

void InGameIntro::onDraw(HDC hdc)
{
	mBG.Draw(hdc);
	for (int i = 0; i < 27; i++)
	{
		Sobj[i].Draw(hdc);
	}



	CScreen rendtarget;
	//rendtarget.Clear(0xffff00ff);

	

	
	UIs.Draw(hdc);
	if (substart)
	{

	}
	//16font
	
	
	//auto b = TEXT(MAKEINTRESOURCE(IDS_CUT1));
	
	LoadString(CApplication::theApp->mhInst, IDS_CUT1+Tboxnum, str, 512);
	//str = MAKEINTRESOURCE(IDS_CUT1);
	
	
	SetBkMode(hdc, TRANSPARENT);
	HFONT hFont, oldFont;
	hFont = CreateFontW(16, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("바탕체"));
	oldFont = (HFONT)SelectObject(hdc, hFont);
	sSc.Draw(rendtarget.m_HDC);
	for (int i = 0; i < 6; i++) {		//이중 스크린(서브 창)
		SWobj[i].Draw(rendtarget.m_HDC);
	}
	//TW.Draw(rendtarget.m_HDC);

	rendtarget.Draw(hdc, 199, 48, 258, 160-y);
	sScWin.Draw(hdc);

	if (tsno == 0)
	{
		TW.Draw(hdc);
		SetTextAlign(hdc, TA_CENTER);
		TextOut(hdc, 326, 192, str, wcslen(str));
		TextOut(hdc, 327, 192, str, wcslen(str));
		
		SetTextAlign(hdc, TA_LEFT);
	}
	else if (Tbox)
	{
		CTW.Draw(hdc);
		CTWC.Draw(hdc);
		TS.OutPut(hdc, str);
		TS2.OutPut(hdc, str);
	}

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

void InGameIntro::onKeyDown(UINT virtual_key)
{
	switch (virtual_key)
	{
	case(VK_DOWN):
		
		break;
	case(VK_UP):
		
		break;
	case(VK_RIGHT):
		
		break;
	case(VK_SPACE):
		samplechange = true;
		break;
	default:
		break;
	}
}

void InGameIntro::onMouseDown(UINT x, UINT y, UINT left_right)
{
	switch (left_right)
	{
	case(MK_LBUTTON):
		if (tsno==0)
		{
			tsno++;
		}
		if (Tbox)
		{
			Tboxnum++;
		}
		break;
	default:
		break;
	}
}

