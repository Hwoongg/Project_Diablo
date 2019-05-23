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
	, const D3DXVECTOR2* pScaling		// ũ��
	, const D3DXVECTOR2* pCenter		// ȸ���߽�
	, FLOAT	fAngle						// ȸ����
	, const D3DXVECTOR2* pPosition		// ��ġ��ȯ
	, D3DCOLOR Color
)
{
	// �׸��� ����
	m_pDxSprite->Begin(D3DXSPRITE_ALPHABLEND);

	// ��������� ����� ����ȭ �صд�
	D3DXMATRIX mtW;
	D3DXMatrixIdentity(&mtW);

	// ȸ���� �� ��ȯ��ĵ� ����
	FLOAT			fTheta = D3DXToRadian(fAngle);
	D3DXMATRIX		mtScl;		// ũ�⺯ȯ��� S
	D3DXMATRIX		mtRot;		// ȸ����� R
	D3DXMATRIX		mtTrn;		// ��ġ��ȯ��� T
	D3DXMATRIX		mtRct;		// Rotation Center Matrix, �߽��� ����ġ
	D3DXMATRIX		mtRctI;		// Rotation Center Matrix Inverse, ...��������

	// �ϴ� ������ķ� �ʱ�ȭ
	D3DXMatrixIdentity(&mtScl);
	D3DXMatrixIdentity(&mtRct);
	D3DXMatrixIdentity(&mtRot);
	D3DXMatrixIdentity(&mtTrn);
	D3DXMatrixIdentity(&mtRctI);

	// ũ�⺯������ �ִٸ�
	if (pScaling) // ũ�⺯ȯ��� �����Լ�. x, y, z ������
		D3DXMatrixScaling(&mtScl, pScaling->x, pScaling->y, 1);

	// Z��ȸ�� = 2���� ȸ���� ����. �� ���ǹ��� ������ �� �𸣰ڴ�
	D3DXMatrixRotationZ(&mtRot, -fTheta);

	// ...
	if (pCenter)
		D3DXMatrixTranslation(&mtRct, pCenter->x, pCenter->y, 0);


	//	D3DXMatrixInverse(&mtRctI, NULL, &mtRct);
	if (pCenter)
		D3DXMatrixTranslation(&mtRctI, -pCenter->x, -pCenter->y, 0);


	if (pPosition)
		D3DXMatrixTranslation(&mtTrn, pPosition->x, pPosition->y, 0);


	// ���� = S * R * T, R=(mtRctI * mtRot * mtRct). �߽������ȭ-ȸ��-����ġ
	mtW = mtScl * mtRctI * mtRot * mtRct * mtTrn;

	// ������� ����
	m_pDxSprite->SetTransform(&mtW);
	m_pDxSprite->Draw(pTex, pSrcRect, NULL, NULL, Color);

	// �׸� �� ������� ����ȭ
	D3DXMatrixIdentity(&mtW);
	m_pDxSprite->SetTransform(&mtW);

	m_pDxSprite->End();

	return 0;
}