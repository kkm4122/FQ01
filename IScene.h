#pragma once
#include "CUnitMange.h"
// �߻�Ŭ����
// �������̽� Ŭ����
//class CUnitMange;
class IScene		//��ӹ޾� ��Ʈ�� ȭ�� ������
{
public:

	
	virtual bool Sample() =0;
	virtual bool isChanged() = 0;
	virtual void onFrameMove() = 0;//���� �ݵ�� �� �Լ��� ���� �־�� �Ѵ�! �ٵ� �� ���� ����
	virtual void onDraw(HDC hdc) = 0;//��� �� ��ӵ��� �����ؾ���!
	virtual void onKeyDown(UINT virtual_key) {}
	virtual void onMouseDown(UINT x, UINT y, UINT left_right) {}
	virtual void onMouseMove(UINT x, UINT y) {}
	//CUnitMange UM;
};

