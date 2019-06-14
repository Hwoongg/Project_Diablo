#pragma once

//////////////////////////////////////
// ���� ���� �⺻ Ʋ
//
class Scene : public CObjectManager
{
public:
	Scene();
	virtual ~Scene();

	void Open();

	// �ش� ���� ������������ �̷�������� �������ϰ� �� ��
	//virtual void Close() = 0;
	
	virtual void Update(CInput* _Input, float _dTime);
	void Render();

	virtual void Command(CGameObject* pButton);
};

////////////////////////////////////
// ���� ȭ��
class MainScene : public Scene
{
public:
	Hero* m_Hero; // �浹 ����ü
	CollisionManager m_CollisionManager; // �浹 ���ü ���

public:
	// �ش� ���� ����Ÿ�ε��� �̷������.
	MainScene();

	virtual void Update(CInput* _Input, float _dTime);

	//virtual void Close();

};


//////////////////////////////////
// Ÿ��Ʋ ȭ��
class TitleScene :public Scene
{
public:
	// ���� ���Ե� ��ư���� ����
	CGameObject* m_btnStart;
	CGameObject* m_btnExit;

public:
	TitleScene();

	virtual void Update(CInput* _Input, float _dTime);

	virtual void Command(CGameObject* pButton);
};