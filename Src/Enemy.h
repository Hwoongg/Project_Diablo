#pragma once

class Enemy :public CGameObject
{
public:
	Enemy();
	Enemy(LPCWSTR sFile, D3DXVECTOR2 _pos);
	virtual ~Enemy();

	void Create(LPCWSTR sFile, D3DXVECTOR2 _pos);

	// Enemy�� �ڵ� ������
	void Update(CInput*, float _dTime);

	// �θ�� ���� ����
	void Draw(CSprite* pCSpr);
};