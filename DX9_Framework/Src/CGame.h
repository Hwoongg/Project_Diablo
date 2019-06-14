#pragma once


class CGame : public CD3DApp
{
public:
	// 이제는 텍스쳐 클래스 포인터로 갖자
	//D3DXIMAGE_INFO pImgInf;
	//LPDIRECT3DTEXTURE9	m_pTx;
	//CTexture* m_pCTx_Zergling;
	//CTexture* m_pCTx_Zealot;
	//CGameObject* UnitObj[5];

	// 자원 관리 클래스
	CObjectManager ObjManager;
	ResourceManager m_rManager;

	CSprite *p_CSprite;
	LPD3DXFONT m_pDXFont1;
	CInput* m_pInput;

	MainScene* scene_main;
	TitleScene* scene_title;


public:
	CGame();

	// 게임에 사용되는 데이터 로딩
	// 이미지, 폰트, 
	virtual int DataLoading();
	virtual void Destroy();
	//게임 상태 갱신
	virtual int FrameMove();
	virtual int Render();

	// 항상 기본 메시지 프로시저만 사용하게 된다는 보장이 없으니 필요하다.
	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);

	virtual CSprite* GetSprite();
	virtual ResourceManager * GetrManager();

	void PutFPS();
};