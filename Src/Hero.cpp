#include "_StdAfx.h"

Hero::Hero()
{
	m_Stat = HERO;
	m_Scale = { .3f, .3f };
	dx = 200;
	dy = 400;
}

Hero::Hero(LPCWSTR sFile, D3DXVECTOR2 _pos)
{
	//Hero();
	m_Stat = HERO;
	m_Scale = { .3f, .3f };
	dx = 200;
	dy = 400;
	Create(sFile, _pos);
	
	// 애니메이션 데이터 설정...
	m_aniInfo.ImageWidth = m_TexRt.right;
	m_aniInfo.ImageHeight = m_TexRt.bottom;
	
	/////////////////////////////////////////////
	// 애니메이션 없는 통짜 텍스쳐
	m_aniInfo.unitSizeX = m_TexRt.right;
	m_aniInfo.unitSizeY = m_TexRt.bottom;

	m_aniInfo.currentFrame = 0;
	m_aniInfo.totalFrameCount = 0;
	m_aniInfo.aniIndex = 0;
	m_aniInfo.totalAniCount = 0;
	/////////////////////////////////////////////

	m_aniInfo.aniDelay = 0.1f;
	m_aniInfo.aniDuration = m_aniInfo.aniDelay;
}

Hero::~Hero()
{
}

void Hero::Create(LPCWSTR sFile, D3DXVECTOR2 _pos)
{
	CGameObject::Create(sFile, _pos);
}

void Hero::Update(CInput* _pInput, float _dTime)
{
	//m_Pos.x += dx*_dTime;
	//m_Pos.y += dy*_dTime;

	////넘어가면 맞춰주고 방향부호바꿈
	//if (m_Pos.x + m_ObjRt.right / 2 > 800)
	//{
	//	m_Pos.x = 800 - m_ObjRt.right / 2;
	//	dx = -dx;
	//}
	//if (m_Pos.x + m_ObjRt.right / 2 < 0)
	//{
	//	m_Pos.x = 0 - m_ObjRt.right / 2;
	//	dx = -dx;
	//}
	//if (m_Pos.y + m_ObjRt.bottom / 2 > 600)
	//{
	//	m_Pos.y = 600 - m_ObjRt.bottom / 2;
	//	dy = -dy;
	//}
	//if (m_Pos.y + m_ObjRt.bottom / 2 <0)
	//{
	//	m_Pos.y = 0 - m_ObjRt.bottom / 2;
	//	dy = -dy;
	//}
	CGameObject::Update(_pInput, _dTime);
}

void Hero::Draw(CSprite* pCSpr)
{
	CGameObject::Draw(/*pCSpr*/);
}
