#include "_StdAfx.h"

extern CD3DApp* g_pApp;

Scene* g_pNowOpened;

CGame::CGame()
{
	g_pApp = this;
	m_pInput = NULL;
	//m_pCTx_Zergling = new CTexture();
	//m_pCTx_Zealot = new CTexture();
	p_CSprite = new CSprite();

	g_pNowOpened = NULL;
	scene_main = NULL;
}

int CGame::DataLoading()
{
	// 입력 클래스 생성
	m_pInput = new CInput;
	m_pInput->Create(m_hWnd);
	

	// 폰트 로딩
	if (FAILED(D3DXCreateFont(m_pd3dDevice
		, 20, 0
		, FW_BOLD, 1, FALSE
		, HANGUL_CHARSET
		, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE
		, L"굴림체"
		, &m_pDXFont1)))
		return -1;

	// 스프라이트 생성
	p_CSprite->Create(m_pd3dSprite);

	// 스프라이트로 그릴 텍스쳐 로딩
	//m_pCTx_Zergling->Create(m_pd3dDevice, L"Texture/zerg.png"); //저글링
	//m_pCTx_Zealot->Create(m_pd3dDevice, L"Texture/zealot.png"); //질럿


	/*for (int i = 0; i < 5; i++)
	{
		if (i < 2)
			UnitObj[i] = new Hero();
		else
			UnitObj[i] = new Enemy();
	}*/

	//Pos.x = (m_dScnX - m_pCTx->GetImageWidth()) / 2;
	//Pos.y = (m_dScnY - m_pCTx->GetImageHeight()) / 2;

	//for (int i = 0; i < 5; i++)
	//{
	//	if (i < 2)
	//	{
	//		Pos.x = i * 800.f;
	//		Pos.y = i * 600.f;
	//		UnitObj[i]->Create(m_pCTx_Zergling, Pos);
	//	}
	//	else
	//	{
	//		Pos.x = m_dScnX / 8 * (i - 1) * 2 - (m_pCTx_Zealot->GetImageWidth() *.2f / 2);
	//		Pos.y = 0;
	//		UnitObj[i]->Create(m_pCTx_Zealot, Pos);
	//	}
	//	//UnitObj[i]->m_Stat==HERO ? m_pCTx_Zergling : m_pCTx_Zealot
	//	// 종류가 많아지면 관련 함수 만들어야될 듯. 오브젝트 상태값 따라 텍스쳐
	//}
	//ObjManager.AddObject(HERO, /*m_pCTx_Zergling*/L"Texture/zerg.png", 0.f, 0.f);
	//ObjManager.AddObject(HERO, L"Texture/zerg.png", 800.f, 600.f);
	//ObjManager.AddObject(ENEMY, L"Texture/zealot.png",
	//	m_dScnX / 4 * 1 - (m_rManager.GetTexture(L"Texture/zealot.png")->GetImageWidth() *.2f / 2), 0.f);
	//ObjManager.AddObject(ENEMY, L"Texture/zealot.png",
	//	m_dScnX / 4 * 2 - (/*m_pCTx_Zealot*/m_rManager.GetTexture(L"Texture/zealot.png")->GetImageWidth() *.2f / 2), 0.f);
	//ObjManager.AddObject(ENEMY, L"Texture/zealot.png",
	//	m_dScnX / 4 * 3 - (m_rManager.GetTexture(L"Texture/zealot.png")->GetImageWidth() *.2f / 2), 0.f);
	
	//scene_main.Open();
	//scene_main = new MainScene();

	scene_title = new TitleScene();
	scene_title->Open();

	return 0;
}

void CGame::Destroy()
{
	SAFE_RELEASE(m_pDXFont1);
	// 추가된 객체들 세이프 딜리트 여부 판단필요
	// 스프라이트 클래스는 렌더 벗어나면 자동으로 소멸자에서 destroy()
	SAFE_DELETE(m_pInput);
	ObjManager.RemoveAllObject();
	//SAFE_DELETE(m_pCTx_Zergling);
	//SAFE_DELETE(m_pCTx_Zealot);
	m_rManager.Destroy(L"Texture/zerg.png");
	m_rManager.Destroy(L"Texture/zealot.png");
}


int CGame::FrameMove()
{
	float _dTime = GetEngineTime();
	m_pInput->FrameMove(); // 입력 상태 갱신

	// 입력에 맞춰 기타 상태 갱신
	//ObjManager.FrameMoveAllObject(m_pInput, _dTime);
	g_pNowOpened->Update(m_pInput, _dTime);


	return 0;
}


int CGame::Render()
{
	//화면을 초기화 한다. 이전색상 (0, 120, 160)
	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 77), 1.0f, 0);

	//장면을 후면 버퍼에 그리기 위한 함수 호출. 그리기의 시작을 알림
	if (FAILED(m_pd3dDevice->BeginScene()))
		return -1;

	
	// 만든 스프라이트 클래스에 포인터 연결
	// --------- CGame 클래스 멤버로 갖도록 하는것이 유용할 듯
	//CSprite *p_CSprite = new CSprite();
	//p_CSprite->Create(m_pd3dSprite);



	////////////////////////////////////////////////////
	// 스프라이트 클래스 활용한 그리기
	// (텍스쳐, 영역, 크기, 회전축, 회전각, 위치, 색상)
	//m_pd3dSprite->Draw(m_pTx, &rt1, NULL, &Pos, D3DXCOLOR(1, 1, 1, 0.7f));
	
	//ObjManager.RenderAllObject(/*p_CSprite*/);
	g_pNowOpened->Render();

	//
	// 현재 크기 변동이 있으면 가운데에 안나오는 현상 있으니 차차 해결해야함
	// 원인은 원본 이미지 크기 기준으로 중심이 잡혔기 때문이다
	///////////////////////////////////////////////////


	///////////////////////////////////////////////////
	// 시스템 상태 표시 함수 생성하도록 할 것
	// FPS 정보 표시
	//RECT rc;
	//::SetRect(&rc, 0, 0, 400, 0 + 30/*폰트크기*/);
	//m_pDXFont1->DrawText(NULL, m_fpsMessage, -1, &rc, 0, D3DXCOLOR(1, 1, 0, 1));
	//PutFPS();


	// 마우스 좌표 정보 표시
	/*RECT rt;
	::SetRect(&rt, 0, 30, 400, 30 + 30);
	TCHAR iMsg[128];
	if (m_pInput)
	{
		D3DXVECTOR3	vcMouse = m_pInput->GetMousePos();
		swprintf(iMsg, L"Mouse X: %.f  Y: %.f  Z: %.f", vcMouse.x, vcMouse.y, vcMouse.z);

		m_pDXFont1->DrawText(NULL, iMsg, -1, &rt, 0, D3DXCOLOR(1, 1, 0, 1));
	}*/


	// EndScene. 다 그렸다고 알려주는 함수
	m_pd3dDevice->EndScene();


	//Run에서 버퍼 교체 Present가 진행됨
	return 0;
}


LRESULT CGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

	case WM_PAINT:
		break;

	}

	return CD3DApp::MsgProc(hWnd, msg, wParam, lParam);
}

CSprite* CGame::GetSprite()
{
	return p_CSprite;
}

ResourceManager* CGame::GetrManager()
{
	return &m_rManager;
}

void CGame::PutFPS()
{
	static int oldtime = GetTickCount();
	int nowtime = GetTickCount();

	static int frmcnt = 0;
	static float fps = 0.0f;

	++frmcnt;

	int time = nowtime - oldtime;
	if (time >= 999)
	{
		oldtime = nowtime;

		fps = (float)frmcnt * 1000 / (float)time;
		frmcnt = 0;
	}

	//RECT rc;
	//::SetRect(&rc, 0, 0, 400, 0 + 30/*폰트크기*/);
	//m_pDXFont1->DrawText(NULL, L"FPS:%.1f/%d", -1, &rc, 0, D3DXCOLOR(1, 1, 0, 1));
	//ynTextDraw(x, y, RGB(0, 0, 255), L"FPS:%.1f/%d", fps, frmcnt );
	/*ynTextDraw(x, y, COLOR(0, 1, 0, 1), L"FPS:%.1f/%d", fps, frmcnt);*/

	RECT rc;
	::SetRect(&rc, 0, 0, 400, 0 + 30);
	TCHAR iMsg[128];
	swprintf(iMsg, L"FPS : %.f", fps);
	m_pDXFont1->DrawText(NULL, iMsg, -1, &rc, 0, D3DXCOLOR(1, 1, 0, 1));
}
