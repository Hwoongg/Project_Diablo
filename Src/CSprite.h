#pragma once

////////////////////////////////////////////////////////
// 스프라이트는 디바이스의 2D용으로 최적화된 인터페이스라 볼 수 있다
// 이 클래스는 만들어진 스프라이트의 주소만 따온 뒤
// 스프라이트의 Draw()를 재정의 해두어 간략하게 쓸 수 있도록 돕는 객체이다
// 굳이 사용할 필요성이 있는지 의문이 남은 상태..
// CGame의 요소로 만들어둠
class CSprite
{
protected:
	LPD3DXSPRITE	m_pDxSprite;			// 2D DX Sprite

public:
	CSprite(void);
	virtual ~CSprite(void);

	INT		Create(LPD3DXSPRITE);

	// 스프라이트를 이용하여 그리기
	// 스프라이트->Draw()의 클래스화
	INT		Draw(LPDIRECT3DTEXTURE9 pTex
		, const RECT* pSrcRect
		, const D3DXVECTOR2* pScaling		// 크기
		, const D3DXVECTOR2* pCenter		// 회전 중심
		, FLOAT	fAngle						// 회전각
		, const D3DXVECTOR2* pPosition		// 위치
		, D3DCOLOR Color
	);
};

