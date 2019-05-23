#include "_StdAfx.h"

Enemy::Enemy()
{
	m_Stat = ENEMY;
	m_Scale = { .2f, .2f };
}

Enemy::Enemy(LPCWSTR sFile, D3DXVECTOR2 _pos) 
{
	//Enemy();
	m_Stat = ENEMY;
	//m_Scale = { .2f, .2f };
	m_Scale = { 3.f, 3.f };
	Create(sFile, _pos);

	// 애니메이션 데이터 설정...
	m_aniInfo.ImageWidth = m_TexRt.right;
	m_aniInfo.ImageHeight = m_TexRt.bottom;
	
	/////////////////////////////////////////////
	// 애니메이션 있는 텍스쳐
	m_aniInfo.unitSizeX = 60;
	m_aniInfo.unitSizeY = 60;

	m_aniInfo.currentFrame = 0;
	m_aniInfo.totalFrameCount = 6;
	m_aniInfo.aniIndex = 0;
	m_aniInfo.totalAniCount = 1;
	/////////////////////////////////////////////

	m_aniInfo.aniDelay = 0.1f;
	m_aniInfo.aniDuration = m_aniInfo.aniDelay;
}

Enemy::~Enemy()
{
}

void Enemy::Create(LPCWSTR sFile, D3DXVECTOR2 _pos)
{
	CGameObject::Create(sFile, _pos);
	dy = 80;
}

void Enemy::Update(CInput *, float _dTime)
{
	m_Pos.y += dy*_dTime;
	if ((m_Pos.y /*- m_ObjRt.bottom / 2*/) > 600)
		m_Pos.y = 0 - (m_ObjRt.bottom);
	m_aniInfo.Update(_dTime);
}

void Enemy::Draw(CSprite * pCSpr)
{
	CGameObject::Draw(/*pCSpr*/);
}
