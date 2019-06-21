#pragma once



class Hero : public CGameObject
{
public:
	bool isMine;

public:
	Hero();
	Hero(LPCWSTR sFile, D3DXVECTOR2 _pos, int _MyKey, int _objKey = -1);
	virtual ~Hero();

	// Hero�� �ؽ��ĸ� ������ ����
	void Create(LPCWSTR sFile, D3DXVECTOR2 _pos, int _objKey = -1);

	// Hero�� �ڵ� ������
	void Update(CInput*, float _dTime);

	// �θ�� ���� ����
	void Draw(CSprite* pCSpr);

};

