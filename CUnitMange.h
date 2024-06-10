#pragma once
#include "CUnit.h"


class CUnit;
class CUnitMange
{
public:
	static CUnitMange* a;
	CUnitMange();
	~CUnitMange();
	void DestroyAll();

	void SetUnit();
	void onDestroy();
	void DestroyUnit(CUnit* Unit);
	CUnit* Ares;
	CUnit* Aerain;
	CUnit* Gonrad;
	CUnit* ArchBishop;
	CUnit* Actum;
	CUnit* HActum;
	CUnit* Genelu;
	CUnit* GarshiaGeneral;
	CUnit* GarshiaCom[3];
	CUnit* GarshiaH[5];
	CUnit* BlackObj[100];
	CUnit* KarionSoldier[20];
	CUnit* KarionSoldier2[20];
	CUnit* KarionSoldier3[20];
	CUnit* KarionPawn[30];
	CUnit* GarshiaSoldier[30];
	CUnit* Garshiaarcher[30];
	CUnit* RockMan[20];
};

