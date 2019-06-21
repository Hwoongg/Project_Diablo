#pragma once

using std::list;

//extern enum ObjStatus
//{
//	UNKNOWN,
//	HERO,
//	ENEMY
//};


class CObjectManager
{
public:
	list<CGameObject*> ObjList; // STL ����Ʈ ����
	list<CGameObject*>::iterator itor; // �ݺ��� ����
	CGameObject* temp; // �ݺ��ڷ� ������ó�� ��� ������ �� �߰�. �������

public:
	CObjectManager();
	virtual ~CObjectManager();

	// ���丮 ���� �����ϸ� ������� �Լ�. ���� �ǵ�� ���� ���� �� �ι�° �Լ� �����
	void AddObject(ObjectType _status, LPCWSTR sFile, float xpos, float ypos);

	// �ǵ�� ���� : ���� ������Ʈ�� new�� ���� �����ϰ�, �ּ� ��ȯ�Ͽ� 
	// �Ŵ��� ������ �ּҸ� �޾� ����Ʈ�� �߰��ϴ� �ܼ� �۾��� �ϵ��� �Ѵ�.
	// ���� ������ ������ ������ �ʰ� �����ε��Ͽ� �����Ͽ���.
	void AddObject(CGameObject*);

	void RemoveObject(); // �ǵڻ���
	virtual void RemoveObject(CGameObject*); // Ư�� ������Ʈ�� ����

	//void ControlAllObject(CInput* _pInput); // �̱���. FrameMove���� ó��
	void RenderAllObject(/*CSprite* _sprite*/);
	void FrameMoveAllObject(CInput* _Input, float _dTime);
	void SetTargetPosition(int _TargetKey, D3DXVECTOR2 _pos);
	void RemoveAllObject();

	CGameObject* Collision(CGameObject* pObject);
	BOOL Collision(CGameObject* obj1, CGameObject* obj2);

};

///////////////////////////////////////////////////////
// RemoveObject() �� ������ �ϱ� ���� Ŭ����
class CollisionManager : public CObjectManager
{
public:
	virtual void RemoveObject(CGameObject *_temp); // delete ���� erase�� �ϱ� ���� ������
};