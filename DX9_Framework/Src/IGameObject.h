#pragma once



class IGameObject
{
public:
	virtual void Create(LPCWSTR sFile, D3DXVECTOR2 _pos) =0;
	virtual void Update(CInput*, float _dTime) = 0;
	virtual void Draw(/*CSprite* pCSpr*/) = 0;
	//virtual void Release() = 0;
};