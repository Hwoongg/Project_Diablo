#pragma once

////////////////////////////////////////////////////////
// ��������Ʈ�� ����̽��� 2D������ ����ȭ�� �������̽��� �� �� �ִ�
// �� Ŭ������ ������� ��������Ʈ�� �ּҸ� ���� ��
// ��������Ʈ�� Draw()�� ������ �صξ� �����ϰ� �� �� �ֵ��� ���� ��ü�̴�
// ���� ����� �ʿ伺�� �ִ��� �ǹ��� ���� ����..
// CGame�� ��ҷ� ������
class CSprite
{
protected:
	LPD3DXSPRITE	m_pDxSprite;			// 2D DX Sprite

public:
	CSprite(void);
	virtual ~CSprite(void);

	INT		Create(LPD3DXSPRITE);

	// ��������Ʈ�� �̿��Ͽ� �׸���
	// ��������Ʈ->Draw()�� Ŭ����ȭ
	INT		Draw(LPDIRECT3DTEXTURE9 pTex
		, const RECT* pSrcRect
		, const D3DXVECTOR2* pScaling		// ũ��
		, const D3DXVECTOR2* pCenter		// ȸ�� �߽�
		, FLOAT	fAngle						// ȸ����
		, const D3DXVECTOR2* pPosition		// ��ġ
		, D3DCOLOR Color
	);
};

