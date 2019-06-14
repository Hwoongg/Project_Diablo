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

	// 디바이스 생성에 윈도우핸들이 필요하다
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

	// D3D생성
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return -1;


	// D3D를 통해서 화면 모드를 찾는다.
	D3DDISPLAYMODE d3ddm;
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		return -1;

	// 디바이스를 생성하기 위해서는 프리젠트 파라메터 구조체가 필요
	// 전부 0으로 셋팅한다음 일부만 변수세팅
	// ZeroMemory 함수를 사용하는 경우가 많았음
	memset(&m_d3dpp, 0, sizeof(m_d3dpp));
	m_d3dpp.Windowed = m_bWindow;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpp.BackBufferFormat = d3ddm.Format;
	m_d3dpp.BackBufferCount = 2;
	m_d3dpp.BackBufferWidth = m_dScnX;
	m_d3dpp.BackBufferHeight = m_dScnY;
	m_d3dpp.EnableAutoDepthStencil = TRUE;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// D3DADAPTER_DEFAULT: 대부분의 그래픽카드는 모노 듀얼일 경우 이부분을 수정
	// D3DDEVTYPE_HAL : 하드웨어 가속(가장 큰 속도)을 받을 것인가.. 하드웨어 지
	// 원이 없을 경우 D3D는 소프트웨어로 이를 대체 할 수 있다.

	// COM객체들은 생성에 실패하면 음수리턴, FAILED를 이용하면 음수일때 참이된다.
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING, &m_d3dpp, &m_pd3dDevice)))
		// 믹스(소프트웨어와 하드웨어의 양쪽 모두) 정점처리를 지정한다
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_d3dpp, &m_pd3dDevice)))
			// 실패하면 소프트웨어에 의한 정점처리를 지정
		{
			// 그래도 실패하면 데이터 해제
			SAFE_RELEASE(m_pd3dDevice);
			SAFE_RELEASE(m_pD3D);
			return -1;
		}
	}

	// DX의 스프라이트는 디바이스가 생성된 후에 만들어야 한다.
	if (FAILED(D3DXCreateSprite(m_pd3dDevice, &m_pd3dSprite)))
	{
		SAFE_RELEASE(m_pd3dDevice);
		SAFE_RELEASE(m_pD3D);
		return -1;
	}

	// 화면 띄우기
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	::ShowCursor(m_bShowCusor);

	// 윈속 초기화
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

			// 후면버퍼 전면버퍼 교체(flipping) 현재 후면버퍼 데이터를 전면버퍼로
			// 상속받은 CGame::Render 부분에서 EndScene 이루어졌음.
			m_pd3dDevice->Present(0, 0, 0, 0);
		}
	}

	// 메시지펌프에서 탈출되면 윈도우클래스 등록 해제
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
	if (NULL == m_pd3dDevice) // 디바이스 유효한지 확인
		return -1;

	if (FAILED(FrameMove())) // 상태갱신
		return -1;

	if (FAILED(Render())) // 그리기
		return -1;

	// 프레임 계산
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
	

	// 30회 갱신마다 계산
	/*if (iCnt>30)
	{
		m_fFps = FLOAT(dE - dB);
		m_fFps = iCnt * 1000 / m_fFps;

		iCnt = 0;
		dB = dE;
	}

	
	swprintf(m_fpsMessage, L"초당 프레임 : %.3f", m_fFps);*/

	// 기존 프레임 획득&출력은 PutFps 함수로 다시 만들도록 할 것


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
//	//::SetRect(&rc, 0, 0, 400, 0 + 30/*폰트크기*/);
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
