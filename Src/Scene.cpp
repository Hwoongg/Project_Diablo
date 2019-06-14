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

	
	// Enemy ������
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

	// �浹�� �Ͼ ��ü�� ������ ȹ��
	CGameObject* pObj = m_CollisionManager.Collision(m_Hero);

	if (pObj) // �浹�Ѱ� ������
	{
		RemoveObject(pObj); // ��ü��Ͽ��� ����
		m_CollisionManager.RemoveObject(pObj); // �浹ü ��Ͽ��� ����
	}


}

TitleScene::TitleScene()
{
	
	D3DXVECTOR2 tempPos;
	tempPos.x = g_pApp->m_dScnX / 2 - 200;
	tempPos.y = g_pApp->m_dScnY / 2 - 100;

	// �����ڿ� AddObject �����ε����� �߰��Ͽ���.
	// ���� �κ��� �״�� ������...
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
	// ��ŸƮ ��ư ������ ��
	if (pButton == m_btnStart)
	{
		
		g_port = SERVERPORT; // ���� ��Ʈ ����
		
		// ���� ��� ������ ����
		g_hClientThread = CreateThread(NULL, 0, ClientMain, NULL, 0, NULL);
		if (g_hClientThread == NULL) 
		{
			MessageBox(g_pApp->m_hWnd, L"Ŭ���̾�Ʈ�� ������ �� �����ϴ�."
				"\r\n���α׷��� �����մϴ�.", L"����!", MB_ICONERROR);
			EndDialog(g_pApp->m_hWnd, 0);
		}
		else 
		{
			while (g_bStart == FALSE); // ���� ���� ���� ��ٸ�
		}
		
		Scene* tempScene = new MainScene();
		tempScene->Open();
	}
	if (pButton == m_btnExit)
	{
		//g_pApp->Cleanup(); // ������
		PostQuitMessage(0);
	}
}


