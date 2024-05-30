#pragma once
#include "CUnit.h"


class CUnit;
class CUnitMange
{
public:
	CUnitMange();
	~CUnitMange();
	static CUnitMange* a;
	void DestroyAll();

	void SetUnit();
	void onDestroy();
	void DestroyUnit(CUnit* Unit);
	CUnit* Ares;
	CUnit* Aerain;
	CUnit* Gonrad;
	CUnit* ArchBishop;
	CUnit* Actum;
	CUnit* Genelu;
	CUnit* GarshiaGeneral;
	CUnit* BlackObj[100];
	CUnit* KarionSoldier[20];
	CUnit* KarionSoldier2[20];
	CUnit* KarionSoldier3[20];
	CUnit* GarshiaSoldier[30];
	CUnit* RockMan[20];
};

