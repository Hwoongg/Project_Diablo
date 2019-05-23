#pragma once

///////////////////////////////////////////////////////
// 기존 텍스쳐 포인터에 여러가지 달아둠
// 디바이스 링크, 파일명 받아 텍스쳐 생성
// 이미지 크기 조회
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


	// 갖고있는 텍스쳐의 포인터(주소)를 반환
	LPDIRECT3DTEXTURE9	GetTexture();
};

