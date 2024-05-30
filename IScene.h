#pragma once
#include "CUnitMange.h"
// 추상클래스
// 인터페이스 클래스
//class CUnitMange;
class Cscreen;
class IScene		//상속받아 인트로 화면 만들어보기
{
public:

	
	virtual bool Sample() =0;
	virtual bool isChanged() = 0;
	virtual void onFrameMove() = 0;//씬은 반드시 이 함수를 갖고 있어야 한다! 근데 난 구현 안해
	virtual void onDraw(HDC hdc) = 0;//대신 내 상속들은 구현해야해!
	virtual void onKeyDown(UINT virtual_key) {}
	virtual void onMouseDown(UINT x, UINT y, UINT left_right) {}
	virtual void onMouseMove(UINT x, UINT y) {}
	virtual void SetScene() = 0;
	//CUnitMange UM;
	bool SetOn = true;
	std::wstring m0 = L"a.Sno:0";//아래
	std::wstring m1 = L"a.Sno:1";//왼쪽
	std::wstring m2 = L"a.Sno:2";//오른쪽
	std::wstring m3 = L"a.Sno:3";//위
	std::wstring m4 = L"a.Sno:4";
	std::wstring m5 = L"a.Sno:5";
	std::wstring m6 = L"a.Sno:6";
	std::wstring s0 = L"a.SnoSTOP:0";
	std::wstring s1 = L"a.SnoSTOP:1";
	std::wstring s2 = L"a.SnoSTOP:2";
	std::wstring s3 = L"a.SnoSTOP:3";
	std::wstring s4 = L"a.SnoSTOP:4";
	std::wstring s5 = L"a.SnoSTOP:5";
	std::wstring s6 = L"a.SnoSTOP:6";
	std::wstring s7 = L"a.SnoSTOP:7";
	std::wstring s8 = L"a.SnoSTOP:8";
	std::wstring s9 = L"a.SnoSTOP:9";
	std::wstring s10 = L"a.SnoSTOP:10";
	std::wstring s11 = L"a.SnoSTOP:11";
	std::wstring s12 = L"a.SnoSTOP:12";

};

