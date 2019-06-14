#pragma once

///////////////////////////////////////////////////////
// ���� �ؽ��� �����Ϳ� �������� �޾Ƶ�
// ����̽� ��ũ, ���ϸ� �޾� �ؽ��� ����
// �̹��� ũ�� ��ȸ
class CTexture
{
protected:
	LPDIRECT3DDEVICE9	m_pDev;

	D3DXIMAGE_INFO		m_Img;
	LPDIRECT3DTEXTURE9	m_pTx;

public:
	CTexture(void);
	~CTexture(void);

	virtual INT		Create(LPDIRECT3DDEVICE9 pDev, LPCWSTR sFile);
	virtual void	Destroy();

	INT		GetImageWidth();
	INT		GetImageHeight();
	void	GetImageRect(RECT* pRc);


	// �����ִ� �ؽ����� ������(�ּ�)�� ��ȯ
	LPDIRECT3DTEXTURE9	GetTexture();
};

