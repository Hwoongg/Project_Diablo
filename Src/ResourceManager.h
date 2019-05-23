#pragma once

using std::map;

class ResourceManager
{
public:
	map<LPCWSTR, CTexture*> m_TexMap;

public:
	ResourceManager();
	virtual ~ResourceManager();

	CTexture* LoadData(LPCWSTR sFile);
	CTexture* GetTexture( LPCWSTR sFile);
	
	void Destroy(LPCWSTR sFile);
};

