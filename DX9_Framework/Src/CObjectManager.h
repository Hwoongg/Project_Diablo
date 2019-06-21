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
	list<CGameObject*> ObjList; // STL 리스트 생성
	list<CGameObject*>::iterator itor; // 반복자 생성
	CGameObject* temp; // 반복자로 포인터처럼 사용 가능한 점 발견. 수정요망

public:
	CObjectManager();
	virtual ~CObjectManager();

	// 팩토리 패턴 연구하며 만들었던 함수. 현재 피드백 내용 적용 된 두번째 함수 사용중
	void AddObject(ObjectType _status, LPCWSTR sFile, float xpos, float ypos);

	// 피드백 내용 : 각자 오브젝트는 new를 통해 생성하고, 주소 반환하여 
	// 매니저 에서는 주소만 받아 리스트에 추가하는 단순 작업만 하도록 한다.
	// 기존 구조를 완전히 없애지 않고 오버로딩하여 구현하였음.
	void AddObject(CGameObject*);

	void RemoveObject(); // 맨뒤삭제
	virtual void RemoveObject(CGameObject*); // 특정 오브젝트를 삭제

	//void ControlAllObject(CInput* _pInput); // 미구현. FrameMove에서 처리
	void RenderAllObject(/*CSprite* _sprite*/);
	void FrameMoveAllObject(CInput* _Input, float _dTime);
	void SetTargetPosition(int _TargetKey, D3DXVECTOR2 _pos);
	void RemoveAllObject();

	CGameObject* Collision(CGameObject* pObject);
	BOOL Collision(CGameObject* obj1, CGameObject* obj2);

};

///////////////////////////////////////////////////////
// RemoveObject() 를 재정의 하기 위한 클래스
class CollisionManager : public CObjectManager
{
public:
	virtual void RemoveObject(CGameObject *_temp); // delete 없이 erase만 하기 위한 재정의
};