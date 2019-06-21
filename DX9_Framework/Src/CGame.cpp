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
	// �Է� Ŭ���� ����
	m_pInput = new CInput;
	m_pInput->Create(m_hWnd);
	

	// ��Ʈ �ε�
	if (FAILED(D3DXCreateFont(m_pd3dDevice
		, 20, 0
		, FW_BOLD, 1, FALSE
		, HANGUL_CHARSET
		, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE
		, L"����ü"
		, &m_pDXFont1)))
		return -1;

	// ��������Ʈ ����
	p_CSprite->Create(m_pd3dSprite);

	// ��������Ʈ�� �׸� �ؽ��� �ε�
	//m_pCTx_Zergling->Create(m_pd3dDevice, L"Texture/zerg.png"); //���۸�
	//m_pCTx_Zealot->Create(m_pd3dDevice, L"Texture/zealot.png"); //����


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
	//	// ������ �������� ���� �Լ� �����ߵ� ��. ������Ʈ ���°� ���� �ؽ���
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
	// �߰��� ��ü�� ������ ����Ʈ ���� �Ǵ��ʿ�
	// ��������Ʈ Ŭ������ ���� ����� �ڵ����� �Ҹ��ڿ��� destroy()
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
	m_pInput->FrameMove(); // �Է� ���� ����

	// �Է¿� ���� ��Ÿ ���� ����
	//ObjManager.FrameMoveAllObject(m_pInput, _dTime);
	g_pNowOpened->Update(m_pInput, _dTime);


	return 0;
}


int CGame::Render()
{
	//ȭ���� �ʱ�ȭ �Ѵ�. �������� (0, 120, 160)
	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 77), 1.0f, 0);

	//����� �ĸ� ���ۿ� �׸��� ���� �Լ� ȣ��. �׸����� ������ �˸�
	if (FAILED(m_pd3dDevice->BeginScene()))
		return -1;

	
	// ���� ��������Ʈ Ŭ������ ������ ����
	// --------- CGame Ŭ���� ����� ������ �ϴ°��� ������ ��
	//CSprite *p_CSprite = new CSprite();
	//p_CSprite->Create(m_pd3dSprite);



	////////////////////////////////////////////////////
	// ��������Ʈ Ŭ���� Ȱ���� �׸���
	// (�ؽ���, ����, ũ��, ȸ����, ȸ����, ��ġ, ����)
	//m_pd3dSprite->Draw(m_pTx, &rt1, NULL, &Pos, D3DXCOLOR(1, 1, 1, 0.7f));
	
	//ObjManager.RenderAllObject(/*p_CSprite*/);
	g_pNowOpened->Render();

	//
	// ���� ũ�� ������ ������ ����� �ȳ����� ���� ������ ���� �ذ��ؾ���
	// ������ ���� �̹��� ũ�� �������� �߽��� ������ �����̴�
	///////////////////////////////////////////////////


	///////////////////////////////////////////////////
	// �ý��� ���� ǥ�� �Լ� �����ϵ��� �� ��
	// FPS ���� ǥ��
	//RECT rc;
	//::SetRect(&rc, 0, 0, 400, 0 + 30/*��Ʈũ��*/);
	//m_pDXFont1->DrawText(NULL, m_fpsMessage, -1, &rc, 0, D3DXCOLOR(1, 1, 0, 1));
	//PutFPS();


	// ���콺 ��ǥ ���� ǥ��
	/*RECT rt;
	::SetRect(&rt, 0, 30, 400, 30 + 30);
	TCHAR iMsg[128];
	if (m_pInput)
	{
		D3DXVECTOR3	vcMouse = m_pInput->GetMousePos();
		swprintf(iMsg, L"Mouse X: %.f  Y: %.f  Z: %.f", vcMouse.x, vcMouse.y, vcMouse.z);

		m_pDXFont1->DrawText(NULL, iMsg, -1, &rt, 0, D3DXCOLOR(1, 1, 0, 1));
	}*/


	// EndScene. �� �׷ȴٰ� �˷��ִ� �Լ�
	m_pd3dDevice->EndScene();


	//Run���� ���� ��ü Present�� �����
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
	//::SetRect(&rc, 0, 0, 400, 0 + 30/*��Ʈũ��*/);
	//m_pDXFont1->DrawText(NULL, L"FPS:%.1f/%d", -1, &rc, 0, D3DXCOLOR(1, 1, 0, 1));
	//ynTextDraw(x, y, RGB(0, 0, 255), L"FPS:%.1f/%d", fps, frmcnt );
	/*ynTextDraw(x, y, COLOR(0, 1, 0, 1), L"FPS:%.1f/%d", fps, frmcnt);*/

	RECT rc;
	::SetRect(&rc, 0, 0, 400, 0 + 30);
	TCHAR iMsg[128];
	swprintf(iMsg, L"FPS : %.f", fps);
	m_pDXFont1->DrawText(NULL, iMsg, -1, &rc, 0, D3DXCOLOR(1, 1, 0, 1));
}
