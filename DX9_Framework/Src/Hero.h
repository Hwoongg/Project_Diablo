#pragma once



class Hero : public CGameObject
{
public:
	Hero();
	Hero(LPCWSTR sFile, D3DXVECTOR2 _pos);
	virtual ~Hero();

	// Hero�� �ؽ��ĸ� ������ ����
	void Create(LPCWSTR sFile, D3DXVECTOR2 _pos);

	// Hero�� �ڵ� ������
	void Update(CInput*, float _dTime);

	// �θ�� ���� ����
	void Draw(CSprite* pCSpr);

};

