#include "pch.h"
#include "resource.h"
#include "CUnit.h"
#include "CImageFile.h"
#include "CUnitMange.h"

CUnitMange* CUnitMange::a = NULL;
//CUnitMange asdf;

CUnitMange::CUnitMange()
{

	if (a == NULL) {
		a = this;
	}
	
}
///////////////////////////////////////////////////////////
/*
다른 클래스에서 호출
ex 아레스
CUnitMange::a->Ares->UnitSet(x좌표, y좌표, L"a.SnoSTOP:0");


*/
///////////////////////////////////////////////////////////
CUnitMange::~CUnitMange()
{
}

void CUnitMange::DestroyAll()
{
	
}

void CUnitMange::SetUnit()
{
	{//아레스 유닛 정보
		Ares = new CUnit;
		Ares->m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_ANI_ARES), L"ANI_ARES");
		Ares->m_anifile.ani = new CAnimation;
		Ares->m_anifile.ani->CreateAni32(Ares->m_anifile.imgFile->Width(), Ares->m_anifile.imgFile->Height(), 100);
		Ares->m_anifile.ani->CreateAniStop32(Ares->m_anifile.imgFile->Width(), Ares->m_anifile.imgFile->Height(), 100);
		Ares->UnitState.Set2(L"a.SnoSTOP:0", 114 - (16), 207 - (16), Ares->m_anifile.ani, Ares->m_anifile.imgFile, RGB(255, 0, 255), CSprite::DrawType_Transparent);
		//Ares->mUnitSprite.Set2(L"a.SnoSTOP:0", 0, 0, Ares->m_anifile.ani, Ares->m_anifile.imgFile, RGB(255, 0, 255), CSprite::DrawType_Transparent);
	
	}
	{//에레인
		Aerain = new CUnit;
		Aerain->m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_AERAIN), L"ANI_AERAIN");
		Aerain->m_anifile.ani = new CAnimation;
		Aerain->m_anifile.ani->CreateAni32(Aerain->m_anifile.imgFile->Width(), Aerain->m_anifile.imgFile->Height(), 100);
		Aerain->m_anifile.ani->CreateAniStop32(Aerain->m_anifile.imgFile->Width(), Aerain->m_anifile.imgFile->Height(), 100);
		Aerain->UnitState.Set2(L"a.Sno:0", 114 - (16), 207 - (16), Aerain->m_anifile.ani, Aerain->m_anifile.imgFile, RGB(255, 0, 255), CSprite::DrawType_Transparent);

	}
	{//곤라드
		Gonrad = new CUnit;
		Gonrad->m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_GONRAD), L"ANI_GONRAD");
		Gonrad->m_anifile.ani = new CAnimation;
		Gonrad->m_anifile.ani->CreateAni32(Gonrad->m_anifile.imgFile->Width(), Gonrad->m_anifile.imgFile->Height(), 100);
		Gonrad->m_anifile.ani->CreateAniStop32(Gonrad->m_anifile.imgFile->Width(), Gonrad->m_anifile.imgFile->Height(), 100);
		Gonrad->UnitState.Set2(L"a.SnoSTOP:0", 114 - (16), 207 - (16), Gonrad->m_anifile.ani, Gonrad->m_anifile.imgFile, RGB(255, 0, 255), CSprite::DrawType_Transparent);
	}
	{//대주교
		ArchBishop = new CUnit;
		ArchBishop->m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_ARCHBISHOP), L"ANI_ARCHBISHOP");
		ArchBishop->m_anifile.ani = new CAnimation;
		ArchBishop->m_anifile.ani->CreateAni32(ArchBishop->m_anifile.imgFile->Width(), ArchBishop->m_anifile.imgFile->Height(), 100);
		ArchBishop->m_anifile.ani->CreateAniStop32(ArchBishop->m_anifile.imgFile->Width(), ArchBishop->m_anifile.imgFile->Height(), 100);
		ArchBishop->UnitState.Set2(L"a.Sno:0", 114 - (16), 207 - (16), ArchBishop->m_anifile.ani, ArchBishop->m_anifile.imgFile, RGB(255, 0, 255), CSprite::DrawType_Transparent);

	}
	{//에크텀
		Actum = new CUnit;
		Actum->m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_KARIONSOLDIER), L"IDB_KARIONSOLDIER");
		Actum->m_anifile.ani = new CAnimation;
		Actum->m_anifile.ani->CreateAni32(Actum->m_anifile.imgFile->Width(), Actum->m_anifile.imgFile->Height(), 100);
		Actum->m_anifile.ani->CreateAniStop32(Actum->m_anifile.imgFile->Width(), Actum->m_anifile.imgFile->Height(), 100);
		Actum->UnitState.Set2(L"a.Sno:0", 114 - (16), 207 - (16), Actum->m_anifile.ani, Actum->m_anifile.imgFile, RGB(255, 0, 255), CSprite::DrawType_Transparent);
	}
	{//제넬루
		Genelu = new CUnit;
		Genelu->m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_GENELU), L"IDB_GENELU");
		Genelu->m_anifile.ani = new CAnimation;
		Genelu->m_anifile.ani->CreateAni32(Genelu->m_anifile.imgFile->Width(), Genelu->m_anifile.imgFile->Height(), 100);
		Genelu->m_anifile.ani->CreateAniStop32(Genelu->m_anifile.imgFile->Width(), Genelu->m_anifile.imgFile->Height(), 100);
		Genelu->UnitState.Set2(L"a.SnoSTOP:0", 114 - (16), 207 - (16), Genelu->m_anifile.ani, Genelu->m_anifile.imgFile, RGB(255, 0, 255), CSprite::DrawType_Transparent);
	}
	{//가르시아장군
		GarshiaGeneral = new CUnit;
		GarshiaGeneral->m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_GARSHIAGENERAL), L"IDB_GARSHIAGENERAL");
		GarshiaGeneral->m_anifile.ani = new CAnimation;
		GarshiaGeneral->m_anifile.ani->CreateAni32(GarshiaGeneral->m_anifile.imgFile->Width(), GarshiaGeneral->m_anifile.imgFile->Height(), 100);
		GarshiaGeneral->m_anifile.ani->CreateAniStop32(GarshiaGeneral->m_anifile.imgFile->Width(), GarshiaGeneral->m_anifile.imgFile->Height(), 100);
		GarshiaGeneral->UnitState.Set2(L"a.SnoSTOP:0", 114 - (16), 207 - (16), GarshiaGeneral->m_anifile.ani, GarshiaGeneral->m_anifile.imgFile, RGB(255, 0, 255), CSprite::DrawType_Transparent);
	}
	{//병사 20
		for (int i = 0; i < 20; i++)
		{
			KarionSoldier[i] = new CUnit;
			KarionSoldier[i]->m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_KARIONSOLDIER), L"IDB_KARIONSOLDIER");
			KarionSoldier[i]->m_anifile.ani = new CAnimation;
			KarionSoldier[i]->m_anifile.ani->CreateAni32(KarionSoldier[i]->m_anifile.imgFile->Width(), KarionSoldier[i]->m_anifile.imgFile->Height(), 100);
				KarionSoldier[i]->m_anifile.ani->CreateAniStop32(KarionSoldier[i]->m_anifile.imgFile->Width(), KarionSoldier[i]->m_anifile.imgFile->Height(), 100);

		}
	}
	{//방패 병사 20
		for (int i = 0; i < 20; i++)
		{
			KarionSoldier2[i] = new CUnit;
			KarionSoldier2[i]->m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_KARIONSOLDIER2), L"IDB_KARIONSOLDIER2");
			KarionSoldier2[i]->m_anifile.ani = new CAnimation;
			KarionSoldier2[i]->m_anifile.ani->CreateAni32(KarionSoldier2[i]->m_anifile.imgFile->Width(), KarionSoldier2[i]->m_anifile.imgFile->Height(), 100);
			KarionSoldier2[i]->m_anifile.ani->CreateAniStop32(KarionSoldier2[i]->m_anifile.imgFile->Width(), KarionSoldier2[i]->m_anifile.imgFile->Height(), 100);
		}
	}
	{//가르시아 병사 30명
		for (int i = 0; i < 30; i++)
		{
			GarshiaSoldier[i] = new CUnit;
			GarshiaSoldier[i]->m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_ENEMYSOL1), L"IDB_ENEMYSOL1");
			GarshiaSoldier[i]->m_anifile.ani = new CAnimation;
			GarshiaSoldier[i]->m_anifile.ani->CreateAni32(GarshiaSoldier[i]->m_anifile.imgFile->Width(), GarshiaSoldier[i]->m_anifile.imgFile->Height(), 100);
			GarshiaSoldier[i]->m_anifile.ani->CreateAniStop32(GarshiaSoldier[i]->m_anifile.imgFile->Width(), GarshiaSoldier[i]->m_anifile.imgFile->Height(), 100);
			//GarshiaSoldier[i]->TileSet(0,0,)
		}
	}
	{
		for (int i = 0; i < 30; i++)
		{
			Garshiaarcher[i] = new CUnit;
			Garshiaarcher[i]->m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_GARSHIAARCHER), L"IDB_GARSHIAARCHER");
			Garshiaarcher[i]->m_anifile.ani = new CAnimation;
			Garshiaarcher[i]->m_anifile.ani->CreateAni32(Garshiaarcher[i]->m_anifile.imgFile->Width(), Garshiaarcher[i]->m_anifile.imgFile->Height(), 100);
			Garshiaarcher[i]->m_anifile.ani->CreateAniStop32(Garshiaarcher[i]->m_anifile.imgFile->Width(), Garshiaarcher[i]->m_anifile.imgFile->Height(), 100);
			//GarshiaSoldier[i]->TileSet(0,0,)
		}
	}
	{//바위인간
		for (int i = 0; i < 20; i++)
		{
			RockMan[i] = new CUnit;
			RockMan[i]->m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_ROCKMAN), L"IDB_ROCKMAN");
			RockMan[i]->m_anifile.ani = new CAnimation;
			RockMan[i]->m_anifile.ani->CreateAni32(RockMan[i]->m_anifile.imgFile->Width(), RockMan[i]->m_anifile.imgFile->Height(), 100);
			RockMan[i]->m_anifile.ani->CreateAniStop32(RockMan[i]->m_anifile.imgFile->Width(), RockMan[i]->m_anifile.imgFile->Height(), 100);
		}
	}
	{//장애물 오브잭 검은색16x16픽셀
		for (int i = 0; i < 100; i++)
		{
			BlackObj[i] = new CUnit;
			BlackObj[i]->size = 1;
			BlackObj[i]->m_anifile.imgFile = CImageFile::New(MAKEINTRESOURCE(IDB_BLACKOBJ), L"IDB_BLACKOBJ");
			BlackObj[i]->m_anifile.ani = new CAnimation;
			BlackObj[i]->m_anifile.ani->CreateAniStop16(BlackObj[i]->m_anifile.imgFile->Width(), BlackObj[i]->m_anifile.imgFile->Height(), 100);
			
		}
	}
}

void CUnitMange::onDestroy()
{
	DestroyUnit(Ares);
	DestroyUnit(Aerain);
	for (int i = 0; i < 20; i++)
	{
		DestroyUnit(KarionSoldier[i]);
		DestroyUnit(KarionSoldier2[i]);
		DestroyUnit(KarionSoldier3[i]);
		DestroyUnit(RockMan[i]);
	}
	DestroyUnit(Gonrad);
	DestroyUnit(ArchBishop);
	DestroyUnit(Genelu);
}

void CUnitMange::DestroyUnit(CUnit* Unit)
{
	if (Unit)
	{
			
		delete Unit;
		Unit=nullptr;
	}
}
