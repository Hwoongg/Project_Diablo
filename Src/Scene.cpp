#include "_StdAfx.h"

extern CD3DApp* g_pApp;
extern Scene* g_pNowOpened;
extern volatile BOOL g_bStart;
extern u_short g_port;
extern HANDLE g_hClientThread;

Scene::Scene()
{

}


Scene::~Scene()
{

}

void Scene::Open()
{
	if (g_pNowOpened != NULL)
	{
		//g_pNowOpened->Close();
	}
	g_pNowOpened = this;
}

void Scene::Update(CInput* _Input, float _dTime)
{
	FrameMoveAllObject(_Input, _dTime);
}

void Scene::Render()
{
	RenderAllObject();
}

void Scene::Command(CGameObject * pButton)
{

}



MainScene::MainScene()
{
	D3DXVECTOR2 tempPos;
	tempPos.x = 0.f;
	tempPos.y = 0.f;
	m_Hero = new Hero(L"Texture/zerg.png", tempPos);
	AddObject(m_Hero);

	
	// Enemy 생성부
	/*tempPos.x = g_pApp->m_dScnX / 4 * 1 - (g_pApp->GetrManager()->GetTexture(L"Texture/zealot.png")->GetImageWidth() *.2f / 2);
	CGameObject* temp = new Enemy(L"Texture/enemy1.png", tempPos);
	AddObject(temp);
	m_CollisionManager.AddObject(temp);


	tempPos.x = g_pApp->m_dScnX / 4 * 2 - (g_pApp->GetrManager()->GetTexture(L"Texture/zealot.png")->GetImageWidth() *.2f / 2);
	temp = new Enemy(L"Texture/enemy1.png", tempPos);
	AddObject(temp);
	m_CollisionManager.AddObject(temp);


	tempPos.x = g_pApp->m_dScnX / 4 * 3 - (g_pApp->GetrManager()->GetTexture(L"Texture/zealot.png")->GetImageWidth() *.2f / 2);
	temp = new Enemy(L"Texture/enemy1.png", tempPos);
	AddObject(temp);
	m_CollisionManager.AddObject(temp);*/

}

void MainScene::Update(CInput * _Input, float _dTime)
{
	FrameMoveAllObject(_Input, _dTime);

	// 충돌이 일어난 객체의 포인터 획득
	CGameObject* pObj = m_CollisionManager.Collision(m_Hero);

	if (pObj) // 충돌한게 있으면
	{
		RemoveObject(pObj); // 전체목록에서 삭제
		m_CollisionManager.RemoveObject(pObj); // 충돌체 목록에서 삭제
	}


}

TitleScene::TitleScene()
{
	
	D3DXVECTOR2 tempPos;
	tempPos.x = g_pApp->m_dScnX / 2 - 200;
	tempPos.y = g_pApp->m_dScnY / 2 - 100;

	// 생성자와 AddObject 오버로딩으로 추가하였음.
	// 기존 부분은 그대로 유지중...
	m_btnStart = new UIButton(this, L"Texture/start.png", tempPos);
	AddObject(m_btnStart);

	tempPos.y += 200;
	m_btnExit = new UIButton(this, L"Texture/exit.png", tempPos);
	AddObject(m_btnExit);
}

void TitleScene::Update(CInput * _Input, float _dTime)
{
	Scene::Update(_Input, _dTime);
}

void TitleScene::Command(CGameObject * pButton)
{
	// 스타트 버튼 눌렸을 때
	if (pButton == m_btnStart)
	{
		
		g_port = SERVERPORT; // 서버 포트 설정
		
		// 소켓 통신 스레드 시작
		g_hClientThread = CreateThread(NULL, 0, ClientMain, NULL, 0, NULL);
		if (g_hClientThread == NULL) 
		{
			MessageBox(g_pApp->m_hWnd, L"클라이언트를 시작할 수 없습니다."
				"\r\n프로그램을 종료합니다.", L"실패!", MB_ICONERROR);
			EndDialog(g_pApp->m_hWnd, 0);
		}
		else 
		{
			while (g_bStart == FALSE); // 서버 접속 성공 기다림
		}
		
		Scene* tempScene = new MainScene();
		tempScene->Open();
	}
	if (pButton == m_btnExit)
	{
		//g_pApp->Cleanup(); // 에러남
		PostQuitMessage(0);
	}
}


