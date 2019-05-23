#include "_StdAfx.h"

extern CD3DApp* g_pApp;

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

CTexture * ResourceManager::LoadData(LPCWSTR sFile)
{
	CTexture *_texture = new CTexture;
	_texture->Create(g_pApp->m_pd3dDevice, sFile);
	m_TexMap[sFile] = _texture;
	return _texture;
}

CTexture * ResourceManager::GetTexture( LPCWSTR sFile)
{
	CTexture *_texture = m_TexMap[sFile];
	if (_texture == NULL)
	{
		return LoadData(sFile);
	}
	else
	{
		return _texture;
	}
}

void ResourceManager::Destroy(LPCWSTR sFile)
{
	CTexture *temp = m_TexMap[sFile];

	SAFE_DELETE(temp);
}
