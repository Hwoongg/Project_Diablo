#include "_StdAfx.h"

extern CD3DApp* g_pApp;

CD3DApp::CD3DApp()
{
	g_pApp = this;

	wcscpy(m_sCls, L"DX9_GG171012");

	m_hInst = NULL;
	m_hWnd = NULL;
	m_dWinStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE;
	m_dScnX = 800;
	m_dScnY = 600;

	m_bShowCusor = TRUE;
	m_bWindow = TRUE;

	m_pD3D = NULL; // D3D
	m_pd3dDevice = NULL; // Device
	m_pd3dSprite = NULL; // Sprite
}

CD3DApp::~CD3DApp()
{

}

int CD3DApp::Create(HINSTANCE hInst)
{
	m_hInst = hInst;

	WNDCLASS wc =
	{
		CS_CLASSDC
		, WndProc
		, 0L
		, 0L
		, m_hInst
		, NULL
		, LoadCursor(NULL, IDC_ARROW)
		, (HBRUSH)GetStockObject(WHITE_BRUSH)
		, NULL
		, m_sCls
	};

	RegisterClass(&wc);

	RECT rc;

	SetRect(&rc, 0, 0, m_dScnX, m_dScnY);
	AdjustWindowRect(&rc, m_dWinStyle, FALSE);

	int iScnSysW = ::GetSystemMetrics(SM_CXSCREEN);
	int iScnSysH = ::GetSystemMetrics(SM_CYSCREEN);

	// ����̽� ������ �������ڵ��� �ʿ��ϴ�
	m_hWnd = CreateWindow(m_sCls
		, m_sCls
		, m_dWinStyle
		, (iScnSysW - (rc.right - rc.left)) / 2
		, (iScnSysH - (rc.bottom - rc.top)) / 2
		, (rc.right - rc.left)
		, (rc.bottom - rc.top)
		, NULL
		, NULL
		, m_hInst
		, NULL);

	// D3D����
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return -1;


	// D3D�� ���ؼ� ȭ�� ��带 ã�´�.
	D3DDISPLAYMODE d3ddm;
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		return -1;

	// ����̽��� �����ϱ� ���ؼ��� ������Ʈ �Ķ���� ����ü�� �ʿ�
	// ���� 0���� �����Ѵ��� �Ϻθ� ��������
	// ZeroMemory �Լ��� ����ϴ� ��찡 ������
	memset(&m_d3dpp, 0, sizeof(m_d3dpp));
	m_d3dpp.Windowed = m_bWindow;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpp.BackBufferFormat = d3ddm.Format;
	m_d3dpp.BackBufferCount = 2;
	m_d3dpp.BackBufferWidth = m_dScnX;
	m_d3dpp.BackBufferHeight = m_dScnY;
	m_d3dpp.EnableAutoDepthStencil = TRUE;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// D3DADAPTER_DEFAULT: ��κ��� �׷���ī��� ��� ����� ��� �̺κ��� ����
	// D3DDEVTYPE_HAL : �ϵ���� ����(���� ū �ӵ�)�� ���� ���ΰ�.. �ϵ���� ��
	// ���� ���� ��� D3D�� ����Ʈ����� �̸� ��ü �� �� �ִ�.

	// COM��ü���� ������ �����ϸ� ��������, FAILED�� �̿��ϸ� �����϶� ���̵ȴ�.
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING, &m_d3dpp, &m_pd3dDevice)))
		// �ͽ�(����Ʈ����� �ϵ������ ���� ���) ����ó���� �����Ѵ�
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_d3dpp, &m_pd3dDevice)))
			// �����ϸ� ����Ʈ��� ���� ����ó���� ����
		{
			// �׷��� �����ϸ� ������ ����
			SAFE_RELEASE(m_pd3dDevice);
			SAFE_RELEASE(m_pD3D);
			return -1;
		}
	}

	// DX�� ��������Ʈ�� ����̽��� ������ �Ŀ� ������ �Ѵ�.
	if (FAILED(D3DXCreateSprite(m_pd3dDevice, &m_pd3dSprite)))
	{
		SAFE_RELEASE(m_pd3dDevice);
		SAFE_RELEASE(m_pD3D);
		return -1;
	}

	// ȭ�� ����
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	::ShowCursor(m_bShowCusor);

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0) return 1;


	if (FAILED(DataLoading()))
		return -1;

	return 0;
}

int CD3DApp::Run()
{

	MSG msg;
	memset(&msg, 0, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (FAILED(Render3D()))
				break;

			// �ĸ���� ������� ��ü(flipping) ���� �ĸ���� �����͸� ������۷�
			// ��ӹ��� CGame::Render �κп��� EndScene �̷������.
			m_pd3dDevice->Present(0, 0, 0, 0);
		}
	}

	// �޽����������� Ż��Ǹ� ������Ŭ���� ��� ����
	UnregisterClass(m_sCls, m_hInst);

	return 0;
}

void CD3DApp::Cleanup()
{
	Destroy();
	SAFE_RELEASE(m_pd3dSprite);
	SAFE_RELEASE(m_pd3dDevice);
	SAFE_RELEASE(m_pD3D);
}

int CD3DApp::Render3D()
{
	if (NULL == m_pd3dDevice) // ����̽� ��ȿ���� Ȯ��
		return -1;

	if (FAILED(FrameMove())) // ���°���
		return -1;

	if (FAILED(Render())) // �׸���
		return -1;

	// ������ ���
	GetEngineTime();

	return 0;
}

LRESULT WINAPI CD3DApp::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return g_pApp->MsgProc(hWnd, msg, wParam, lParam);
}

LRESULT CD3DApp::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			SendMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;

	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

float CD3DApp::GetEngineTime()
{
	//static int		iCnt = 0;
	//static DWORD	dB = timeGetTime();
	//DWORD			dE = timeGetTime();
	//iCnt++;
	

	// 30ȸ ���Ÿ��� ���
	/*if (iCnt>30)
	{
		m_fFps = FLOAT(dE - dB);
		m_fFps = iCnt * 1000 / m_fFps;

		iCnt = 0;
		dB = dE;
	}

	
	swprintf(m_fpsMessage, L"�ʴ� ������ : %.3f", m_fFps);*/

	// ���� ������ ȹ��&����� PutFps �Լ��� �ٽ� ���鵵�� �� ��


	static int oldtime = GetTickCount();
	int nowtime = GetTickCount();
	float dTime = (nowtime - oldtime) * 0.001f;
	oldtime = nowtime;

	return dTime;
}

//void CD3DApp::PutFPS(int x, int y)
//{
//	static int oldtime = GetTickCount();
//	int nowtime = GetTickCount();
//
//	static int frmcnt = 0;
//	static float fps = 0.0f;
//
//	++frmcnt;
//
//	int time = nowtime - oldtime;
//	if (time >= 999)
//	{
//		oldtime = nowtime;
//
//		fps = (float)frmcnt * 1000 / (float)time;
//		frmcnt = 0;
//	}
//
//	//RECT rc;
//	//::SetRect(&rc, 0, 0, 400, 0 + 30/*��Ʈũ��*/);
//	//m_pDXFont1->DrawText(NULL, L"FPS:%.1f/%d", -1, &rc, 0, D3DXCOLOR(1, 1, 0, 1));
//	//ynTextDraw(x, y, RGB(0, 0, 255), L"FPS:%.1f/%d", fps, frmcnt );
//	/*ynTextDraw(x, y, COLOR(0, 1, 0, 1), L"FPS:%.1f/%d", fps, frmcnt);*/
//
//	RECT rc;
//	::SetRect(&rc, 0, 0, 400, 0 + 30);
//	TCHAR iMsg[128];
//
//	swprintf(iMsg, L"FPS : %.f", fps);
//
//	m_pDXFont1
//}
