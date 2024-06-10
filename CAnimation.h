#pragma once
#include "CSprite.h"
struct FRAME 
{
	int x, y, width, height;
	FRAME() :x(0), y(0), width(0), height(0) {}
	FRAME(int _x, int _y, int _w, int _h):x(_x), y(_y), width(_w), height(_h) {}
};

struct ANIM_KEY 
{
	int frameNo;		//프레임 수
	int delayTime;		//딜레이
	ANIM_KEY() :frameNo(0), delayTime(0) {}
	ANIM_KEY(int no, int delay) :frameNo(no), delayTime(delay) {}
};

struct FRAMANIM_INSTANCE
{
	int currentTime;
	int delayTime;
	int anikeyNo;
	FRAME frame;
};

struct FrameAnimation
{
	std::wstring m_Name;
	std::vector<FRAME> m_Frames;
	std::vector<ANIM_KEY> m_AnimKeys;

	void UpdateInstance(FRAMANIM_INSTANCE& inst);
};


class CAnimation
{
public:
	std::vector<FrameAnimation*> m_FramAnimations;//메모리 접근이 많을 예정으로 포인터 선언

	~CAnimation();

	void CreateSample();
	FrameAnimation* Find(std::wstring& name);
	void CreateAni32(int bw, int bh, int dt);
	void CreateAniStop32(int bw, int bh, int dt);
	void CreateAni(int bw, int bh, int dt, int size);
	void CreateStop(int bw, int bh, int dt, int size);
	void CreateAniStop16(int bw, int bh, int dt);
	void CreateAniW(int bw,int bh, int fw, int fh, int dt);
	void CreateAniH(int bw, int bh, int fw, int fh, int dt);
};

struct ANIM_FILE
{
	CImageFile* imgFile;
	CAnimation* ani;
};





class CFrameSprite :public CSprite
{
public:
	FrameAnimation* m_CurrentFAni;
	CAnimation* m_Animation;

	FRAMANIM_INSTANCE m_AnimInst;
	


	void Set2(const WCHAR* pname, int dx, int dy, CAnimation* ani, CImageFile* img, UINT color, TDrawType dt);
	void ChangeAnimation(std::wstring& name);
	void Update(int dt);
};