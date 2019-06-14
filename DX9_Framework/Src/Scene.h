#pragma once

//////////////////////////////////////
// 씬에 대한 기본 틀
//
class Scene : public CObjectManager
{
public:
	Scene();
	virtual ~Scene();

	void Open();

	// 해당 씬의 데이터해제가 이루어지도록 재정의하게 될 것
	//virtual void Close() = 0;
	
	virtual void Update(CInput* _Input, float _dTime);
	void Render();

	virtual void Command(CGameObject* pButton);
};

////////////////////////////////////
// 메인 화면
class MainScene : public Scene
{
public:
	Hero* m_Hero; // 충돌 기준체
	CollisionManager m_CollisionManager; // 충돌 대상체 목록

public:
	// 해당 씬의 데이타로딩이 이루어진다.
	MainScene();

	virtual void Update(CInput* _Input, float _dTime);

	//virtual void Close();

};


//////////////////////////////////
// 타이틀 화면
class TitleScene :public Scene
{
public:
	// 씬에 포함된 버튼들의 정보
	CGameObject* m_btnStart;
	CGameObject* m_btnExit;

public:
	TitleScene();

	virtual void Update(CInput* _Input, float _dTime);

	virtual void Command(CGameObject* pButton);
};