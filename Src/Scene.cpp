#include "_StdAfx.h"


extern CD3DApp* g_pApp;
extern Scene* g_pNowOpened;

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
	//AddObject(HERO, /*m_pCTx_Zergling*/L"Texture/zerg.png", 0.f, 0.f);
	D3DXVECTOR2 tempPos;
	tempPos.x = 0.f;
	tempPos.y = 0.f;
	m_Hero = new Hero(L"Texture/zerg.png", tempPos);
	AddObject(m_Hero);

	

	/*AddObject(ENEMY, L"Texture/zealot.png",
		g_pApp->m_dScnX / 4 * 1 - (g_pApp->GetrManager()->GetTexture(L"Texture/zealot.png")->GetImageWidth() *.2f / 2), 0.f);*/
	tempPos.x = g_pApp->m_dScnX / 4 * 1 - (g_pApp->GetrManager()->GetTexture(L"Texture/zealot.png")->GetImageWidth() *.2f / 2);
	//CGameObject* temp = new Enemy(L"Texture/zealot.png", tempPos);
	CGameObject* temp = new Enemy(L"Texture/enemy1.png", tempPos);
	AddObject(temp);
	m_CollisionManager.AddObject(temp);


	/*AddObject(ENEMY, L"Texture/zealot.png",
		g_pApp->m_dScnX / 4 * 2 - (g_pApp->GetrManager()->GetTexture(L"Texture/zealot.png")->GetImageWidth() *.2f / 2), 0.f);*/
	tempPos.x = g_pApp->m_dScnX / 4 * 2 - (g_pApp->GetrManager()->GetTexture(L"Texture/zealot.png")->GetImageWidth() *.2f / 2);
	temp = new Enemy(L"Texture/enemy1.png", tempPos);
	AddObject(temp);
	m_CollisionManager.AddObject(temp);


	/*AddObject(ENEMY, L"Texture/zealot.png",
		g_pApp->m_dScnX / 4 * 3 - (g_pApp->GetrManager()->GetTexture(L"Texture/zealot.png")->GetImageWidth() *.2f / 2), 0.f);*/
	tempPos.x = g_pApp->m_dScnX / 4 * 3 - (g_pApp->GetrManager()->GetTexture(L"Texture/zealot.png")->GetImageWidth() *.2f / 2);
	temp = new Enemy(L"Texture/enemy1.png", tempPos);
	AddObject(temp);
	m_CollisionManager.AddObject(temp);

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
	//AddObject(UNKNOWN, L"Texture/start.png", g_pApp->m_dScnX / 2, g_pApp->m_dScnY / 2 - 100);
	//AddObject(UNKNOWN, L"Texture/exit.png", g_pApp->m_dScnX / 2, g_pApp->m_dScnY / 2 + 100);
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
	if (pButton == m_btnStart)
	{
		Scene* tempScene = new MainScene();
		tempScene->Open();
	}
	if (pButton == m_btnExit)
	{
		//g_pApp->Cleanup(); // 에러남
		PostQuitMessage(0);
	}
}
