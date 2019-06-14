#pragma once

class Enemy :public CGameObject
{
public:
	Enemy();
	Enemy(LPCWSTR sFile, D3DXVECTOR2 _pos);
	virtual ~Enemy();

	void Create(LPCWSTR sFile, D3DXVECTOR2 _pos);

	// Enemy의 자동 움직임
	void Update(CInput*, float _dTime);

	// 부모와 같은 동작
	void Draw(CSprite* pCSpr);
};