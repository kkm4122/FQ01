#pragma once
#include "CUnitMange.h"
// 추상클래스
// 인터페이스 클래스
//class CUnitMange;
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
	//CUnitMange UM;
};

