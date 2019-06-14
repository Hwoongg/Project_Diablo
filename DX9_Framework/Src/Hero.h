#pragma once



class Hero : public CGameObject
{
public:
	Hero();
	Hero(LPCWSTR sFile, D3DXVECTOR2 _pos);
	virtual ~Hero();

	// Hero의 텍스쳐를 입히고 생성
	void Create(LPCWSTR sFile, D3DXVECTOR2 _pos);

	// Hero의 자동 움직임
	void Update(CInput*, float _dTime);

	// 부모와 같은 동작
	void Draw(CSprite* pCSpr);

};

