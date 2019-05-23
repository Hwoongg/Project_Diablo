#include "_StdAfx.h"



CTexture::CTexture()
{
	m_pDev = NULL;

	m_pTx = NULL;
	memset(&m_Img, 0, sizeof m_Img);
}


CTexture::~CTexture()
{
	Destroy();
}

void CTexture::Destroy()
{
	if (m_pTx)
	{
		m_pTx->Release();
		m_pTx = NULL;
	}
}

INT CTexture::Create(LPDIRECT3DDEVICE9 pDev, LPCWSTR sFile)
{
	// 디바이스 받아다 링크
	m_pDev = pDev;

	DWORD	dColorKey = 0xFFFFFFFF;

	if (FAILED(D3DXCreateTextureFromFileEx(
		m_pDev
		, sFile
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 1
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_FILTER_NONE
		, D3DX_FILTER_NONE
		, dColorKey
		, &m_Img
		, NULL
		, &m_pTx
	)))
	{
		m_pTx = NULL;
		MessageBox(GetActiveWindow()
			, L"Create Texture Failed"
			, L"Err"
			, MB_ICONEXCLAMATION
		);
		return -1;
	}

	return 0;
}


INT CTexture::GetImageWidth()
{
	return m_Img.Width;
}


INT CTexture::GetImageHeight()
{
	return m_Img.Height;
}

void CTexture::GetImageRect(RECT* pRc)
{
	pRc->left = 0;
	pRc->top = 0;
	pRc->right = m_Img.Width;
	pRc->bottom = m_Img.Height;
}

LPDIRECT3DTEXTURE9 CTexture::GetTexture()
{
	return m_pTx;
}