#pragma once



class Hero : public CGameObject
{
public:
	bool isMine;

public:
	Hero();
	Hero(LPCWSTR sFile, D3DXVECTOR2 _pos, int _MyKey, int _objKey = -1);
	virtual ~Hero();

	// Hero의 텍스쳐를 입히고 생성
	void Create(LPCWSTR sFile, D3DXVECTOR2 _pos, int _objKey = -1);

	// Hero의 자동 움직임
	void Update(CInput*, float _dTime);

	// 부모와 같은 동작
	void Draw(CSprite* pCSpr);

};

