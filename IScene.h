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
	virtual void SetScene() = 0;
	//CUnitMange UM;
	bool SetOn = true;
	std::wstring m0 = L"a.Sno:0";//�Ʒ�
	std::wstring m1 = L"a.Sno:1";//����
	std::wstring m2 = L"a.Sno:2";//������
	std::wstring m3 = L"a.Sno:3";//��
	std::wstring s0 = L"a.SnoSTOP:0";
	std::wstring s1 = L"a.SnoSTOP:1";
	std::wstring s2 = L"a.SnoSTOP:2";
	std::wstring s3 = L"a.SnoSTOP:3";
};

