#pragma once

class CD3DApp
{
public:
	TCHAR m_sCls[128];
	HINSTANCE m_hInst;
	HWND m_hWnd;
	DWORD m_dWinStyle;
	DWORD m_dScnX;
	DWORD m_dScnY;
	BOOL m_bShowCusor;
	BOOL m_bWindow;

	RECT m_rcWin;

	D3DPRESENT_PARAMETERS m_d3dpp;
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	LPD3DXSPRITE m_pd3dSprite;

	
	FLOAT m_fFps;
	TCHAR m_fpsMessage[30];

public:
	CD3DApp();
	virtual ~CD3DApp();

	// ������ ���� �� COM ��ü �ʱ�ȭ
	int Create(HINSTANCE hInst);
	// �޽��� ����
	int Run();
	// ����� ������ ���� ���ַ� ����
	void Cleanup();
	int Render3D();

	virtual int DataLoading() = 0;
	virtual void Destroy() = 0;
	virtual int Render() = 0;
	virtual int FrameMove() = 0;

	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	static LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);

	float GetEngineTime();
	//void PutFPS(int x, int y); CGame�� �̵�

	virtual CSprite* GetSprite() = 0;
	virtual ResourceManager* GetrManager() = 0;

};