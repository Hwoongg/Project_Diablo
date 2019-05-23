#include "_StdAfx.h"



CSprite::CSprite(void)
{
	m_pDxSprite = NULL;
}


CSprite::~CSprite(void)
{
}
INT CSprite::Create(LPD3DXSPRITE pSprite)
{
	m_pDxSprite = pSprite;

	return 0;
}

INT CSprite::Draw(LPDIRECT3DTEXTURE9 pTex
	, const RECT* pSrcRect
	, const D3DXVECTOR2* pScaling		// 크기
	, const D3DXVECTOR2* pCenter		// 회전중심
	, FLOAT	fAngle						// 회전각
	, const D3DXVECTOR2* pPosition		// 위치변환
	, D3DCOLOR Color
)
{
	// 그리기 시작
	m_pDxSprite->Begin(D3DXSPRITE_ALPHABLEND);

	// 월드행렬을 만들어 단위화 해둔다
	D3DXMATRIX mtW;
	D3DXMatrixIdentity(&mtW);

	// 회전각 및 변환행렬들 생성
	FLOAT			fTheta = D3DXToRadian(fAngle);
	D3DXMATRIX		mtScl;		// 크기변환행렬 S
	D3DXMATRIX		mtRot;		// 회전행렬 R
	D3DXMATRIX		mtTrn;		// 위치변환행렬 T
	D3DXMATRIX		mtRct;		// Rotation Center Matrix, 중심을 원위치
	D3DXMATRIX		mtRctI;		// Rotation Center Matrix Inverse, ...원점으로

	// 일단 단위행렬로 초기화
	D3DXMatrixIdentity(&mtScl);
	D3DXMatrixIdentity(&mtRct);
	D3DXMatrixIdentity(&mtRot);
	D3DXMatrixIdentity(&mtTrn);
	D3DXMatrixIdentity(&mtRctI);

	// 크기변동값이 있다면
	if (pScaling) // 크기변환행렬 생성함수. x, y, z 변위량
		D3DXMatrixScaling(&mtScl, pScaling->x, pScaling->y, 1);

	// Z축회전 = 2차원 회전과 같음. 왜 조건문이 없는지 잘 모르겠다
	D3DXMatrixRotationZ(&mtRot, -fTheta);

	// ...
	if (pCenter)
		D3DXMatrixTranslation(&mtRct, pCenter->x, pCenter->y, 0);


	//	D3DXMatrixInverse(&mtRctI, NULL, &mtRct);
	if (pCenter)
		D3DXMatrixTranslation(&mtRctI, -pCenter->x, -pCenter->y, 0);


	if (pPosition)
		D3DXMatrixTranslation(&mtTrn, pPosition->x, pPosition->y, 0);


	// 월드 = S * R * T, R=(mtRctI * mtRot * mtRct). 중심축원점화-회전-원위치
	mtW = mtScl * mtRctI * mtRot * mtRct * mtTrn;

	// 월드행렬 세팅
	m_pDxSprite->SetTransform(&mtW);
	m_pDxSprite->Draw(pTex, pSrcRect, NULL, NULL, Color);

	// 그린 뒤 월드행렬 단위화
	D3DXMatrixIdentity(&mtW);
	m_pDxSprite->SetTransform(&mtW);

	m_pDxSprite->End();

	return 0;
}