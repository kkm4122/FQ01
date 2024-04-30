#include "pch.h"
//#include "CSprite.h"
#include "CAnimation.h"

CAnimation::~CAnimation()
{
	for (int i = 0; i < m_FramAnimations.size(); ++i)
	{
		if (m_FramAnimations[i])
		{
			delete m_FramAnimations[i];
			m_FramAnimations[i] = nullptr;
		}
	}
}

void CAnimation::CreateSample()
{
	int w = 260 / 4;
	int h = 200 / 4;
	

	FrameAnimation* fa_face = new FrameAnimation;
	fa_face->m_Frames.push_back(FRAME(0, 0, w, h));
	fa_face->m_Frames.push_back(FRAME(w, 0, w, h));
	fa_face->m_Frames.push_back(FRAME(w * 2, 0, w, h));
	fa_face->m_Frames.push_back(FRAME(w * 3, 0, w, h));
	fa_face->m_AnimKeys.push_back(ANIM_KEY(0, 100));
	fa_face->m_AnimKeys.push_back(ANIM_KEY(1, 100));
	fa_face->m_AnimKeys.push_back(ANIM_KEY(2, 100));
	fa_face->m_AnimKeys.push_back(ANIM_KEY(3, 100));
	fa_face->m_Name = L"char_F";
	m_FramAnimations.push_back(fa_face);

	//FRAME fm;
	

	FrameAnimation* fa_left = new FrameAnimation;
	fa_left->m_Frames.push_back(FRAME(0, h, w, h));
	fa_left->m_Frames.push_back(FRAME(w, h, w, h));
	fa_left->m_Frames.push_back(FRAME(w * 2, h, w, h));
	fa_left->m_Frames.push_back(FRAME(w * 3, h, w, h));
	fa_left->m_AnimKeys.push_back(ANIM_KEY(0, 100));
	fa_left->m_AnimKeys.push_back(ANIM_KEY(1, 100));
	fa_left->m_AnimKeys.push_back(ANIM_KEY(2, 100));
	fa_left->m_AnimKeys.push_back(ANIM_KEY(3, 100));
	fa_left->m_Name = L"char_L";
	m_FramAnimations.push_back(fa_left);

	FrameAnimation* fa_right = new FrameAnimation;
	fa_right->m_Frames.push_back(FRAME(0, h*2, w, h));
	fa_right->m_Frames.push_back(FRAME(w, h*2, w, h));
	fa_right->m_Frames.push_back(FRAME(w * 2, h*2, w, h));
	fa_right->m_Frames.push_back(FRAME(w * 3, h*2, w, h));
	fa_right->m_AnimKeys.push_back(ANIM_KEY(0, 100));
	fa_right->m_AnimKeys.push_back(ANIM_KEY(1, 100));
	fa_right->m_AnimKeys.push_back(ANIM_KEY(2, 100));
	fa_right->m_AnimKeys.push_back(ANIM_KEY(3, 100));
	fa_right->m_Name = L"char_R";
	m_FramAnimations.push_back(fa_right);

	FrameAnimation* fa_back = new FrameAnimation;

	fa_back->m_Frames.push_back(FRAME(0, h * 3, w, h));
	fa_back->m_Frames.push_back(FRAME(w, h * 3, w, h));
	fa_back->m_Frames.push_back(FRAME(w * 2, h * 3, w, h));
	fa_back->m_Frames.push_back(FRAME(w * 3, h * 3, w, h));
	fa_back->m_AnimKeys.push_back(ANIM_KEY(0, 100));
	fa_back->m_AnimKeys.push_back(ANIM_KEY(1, 100));
	fa_back->m_AnimKeys.push_back(ANIM_KEY(2, 100));
	fa_back->m_AnimKeys.push_back(ANIM_KEY(3, 100));
	fa_back->m_Name = L"char_B";
	m_FramAnimations.push_back(fa_back);

	//delete fa_face;
	//delete fa_left;
	//delete fa_right;
	//delete fa_back;

}
void CAnimation::CreateAniW(int bw, int bh, int fw, int fh, int dt)
{
	
	int w32 = bw / 32;
	int h32 = bh / 32;


	int w = bw / fw;
	int h = bh / fh;
	//가로 세로 
	for (int i = 0; i < fh; i++)
	{
		FrameAnimation* a = new FrameAnimation;
		for (int j = 0; j < fw; j++)
		{
			a->m_Frames.push_back(FRAME(j * w, i * h, w, h));
			a->m_AnimKeys.push_back(ANIM_KEY(j, dt));
		}
		WCHAR AniFno[9];
		swprintf_s(AniFno, 9, L"a.Sno:%d", i);
		a->m_Name = AniFno;
		m_FramAnimations.push_back(a);
		//delete a;
	}
}

void CAnimation::CreateAniH(int bw, int bh, int fw, int fh, int dt)
{
	int w = bw / fw;
	int h = bh / fh;
	//세로 가로
	for (int i = 0; i < fh; i++)
	{
		FrameAnimation* a = new FrameAnimation;
		for (int j = 0; j < fw; j++)
		{
			a->m_Frames.push_back(FRAME(i * w, j * h, w, h));
			a->m_AnimKeys.push_back(ANIM_KEY(j, dt));
		}
		WCHAR AniFno[9];
		swprintf_s(AniFno, 9, L"a.Sno:%d", i);
		a->m_Name = AniFno;
		m_FramAnimations.push_back(a);
		//delete a;
	}
}

void CAnimation::CreateAni32(int bw, int bh, int dt)
{
	int w32 = bw / 32;
	int h32 = bh / 32;


	
	//가로 세로 
	for (int i = 0; i < h32; i++)
	{
		FrameAnimation* a = new FrameAnimation;
		for (int j = 0; j < w32; j++)
		{
			a->m_Frames.push_back(FRAME(j * 32, i * 32, 32, 32));
			a->m_AnimKeys.push_back(ANIM_KEY(j, dt));
		}
		WCHAR AniFno[100];
		swprintf_s(AniFno, 100, L"a.Sno:%d", i);
		a->m_Name = AniFno;
		m_FramAnimations.push_back(a);
		//delete a;
	}
}

void CAnimation::CreateAniStop32(int bw, int bh, int dt)
{
	int w32 = bw / 32;
	int h32 = bh / 32;



	//가로 세로 
	for (int j = 0; j < w32; j++)
	{
		for (int i = 0; i < h32; i++)
		{
			FrameAnimation* a = new FrameAnimation;
			a->m_Frames.push_back(FRAME(j*32, i * 32, 32, 32));
			a->m_AnimKeys.push_back(ANIM_KEY(0, dt));

			WCHAR AniFno[100];
			swprintf_s(AniFno, 100, L"a.SnoSTOP:%d", i+(j*h32));
			a->m_Name = AniFno;
			m_FramAnimations.push_back(a);
			//delete a;
		}

	}
}
void CAnimation::CreateAniStop16(int bw, int bh, int dt)
{
	int w16 = bw / 16;
	int h16 = bh / 16;



	//가로 세로 
	for (int j = 0; j < w16; j++)
	{
		for (int i = 0; i < h16; i++)
		{
			FrameAnimation* a = new FrameAnimation;
			a->m_Frames.push_back(FRAME(j * 16, i * 16, 16, 16));
			a->m_AnimKeys.push_back(ANIM_KEY(0, dt));

			WCHAR AniFno[100];
			swprintf_s(AniFno, 100, L"a.SnoSTOP:%d", i + (j * h16));
			a->m_Name = AniFno;
			m_FramAnimations.push_back(a);
			//delete a;
		}

	}
}

FrameAnimation* CAnimation::Find(std::wstring& name)
{
	for (FrameAnimation* it:m_FramAnimations)
	{
		
		if(it->m_Name==name)
		{
			return it;
		}
	}

	return nullptr;
}



void CFrameSprite::Set2(const WCHAR* pname, int dx, int dy, CAnimation* ani, CImageFile* img, UINT color, TDrawType dt)
{
	std::wstring name(pname);
	CSprite::Set(dx, dy, 0, 0, img, color, dt);
	m_Animation = ani;

	ChangeAnimation(name);
}

void CFrameSprite::ChangeAnimation(std::wstring& name)
{
	//int keyNoCu = m_AnimInst.anikeyNo;	//애니메이션이 바뀔때  현재 키넘버(프레임페이즈)를 저장 다른애니메이션에서 같은 움직임으로 옮길수 있게
	m_CurrentFAni = m_Animation->Find(name);
	ANIM_KEY key = m_CurrentFAni->m_AnimKeys[0];
	m_AnimInst.anikeyNo = 0;
	m_AnimInst.currentTime = 0;
	m_AnimInst.delayTime = key.delayTime;
	m_AnimInst.frame = m_CurrentFAni->m_Frames[key.frameNo];
}

void CFrameSprite::Update(int dt)
{
	m_AnimInst.currentTime += dt;
	m_AnimInst.delayTime -= dt;

	m_CurrentFAni->UpdateInstance(m_AnimInst);
	
	mSrcX = m_AnimInst.frame.x;
	mSrcY = m_AnimInst.frame.y;
	mSrcWidth = m_AnimInst.frame.width;
	mSrcHeight = m_AnimInst.frame.height;

}

void FrameAnimation::UpdateInstance(FRAMANIM_INSTANCE& inst)
{
	if(inst.delayTime>0)
	{
		return;
	}

	++inst.anikeyNo;
	if (inst.anikeyNo >= m_AnimKeys.size()) 
	{
		inst.anikeyNo = 0;
	}
	inst.delayTime = m_AnimKeys[inst.anikeyNo].delayTime;

	inst.frame = m_Frames[m_AnimKeys[inst.anikeyNo].frameNo];
}
