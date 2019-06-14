#pragma once


class CGame : public CD3DApp
{
public:
	// ������ �ؽ��� Ŭ���� �����ͷ� ����
	//D3DXIMAGE_INFO pImgInf;
	//LPDIRECT3DTEXTURE9	m_pTx;
	//CTexture* m_pCTx_Zergling;
	//CTexture* m_pCTx_Zealot;
	//CGameObject* UnitObj[5];

	// �ڿ� ���� Ŭ����
	CObjectManager ObjManager;
	ResourceManager m_rManager;

	CSprite *p_CSprite;
	LPD3DXFONT m_pDXFont1;
	CInput* m_pInput;

	MainScene* scene_main;
	TitleScene* scene_title;


public:
	CGame();

	// ���ӿ� ���Ǵ� ������ �ε�
	// �̹���, ��Ʈ, 
	virtual int DataLoading();
	virtual void Destroy();
	//���� ���� ����
	virtual int FrameMove();
	virtual int Render();

	// �׻� �⺻ �޽��� ���ν����� ����ϰ� �ȴٴ� ������ ������ �ʿ��ϴ�.
	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);

	virtual CSprite* GetSprite();
	virtual ResourceManager * GetrManager();

	void PutFPS();
};