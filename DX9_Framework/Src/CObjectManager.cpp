#include "_StdAfx.h"


CObjectManager::CObjectManager()
{
	itor = ObjList.begin();
}

CObjectManager::~CObjectManager()
{

}

void CObjectManager::AddObject(ObjectType _status, LPCWSTR sFile, float xpos, float ypos)
{
	D3DXVECTOR2 _pos = { xpos, ypos };
	switch (_status)
	{
	case UNKNOWN:
		temp = new CGameObject();
		// 자칫 temp가 고정된 주소를 가리킬 것이라 오해할 수 있음.
		// temp가 가리키는 곳에 동적할당하는것이 아닌,
		// 동적할당된 주소가 temp에 들어가게 되는 것.
		break;
	case HERO:
		temp = new Hero();
		break;
	case ENEMY:
		temp = new Enemy();
		break;
	}
	
	ObjList.push_back(temp);
	temp->Create(sFile, _pos);
}

void CObjectManager::AddObject(CGameObject* _temp)
{
	ObjList.push_back(_temp);
}

void CObjectManager::RemoveObject()
{
	itor = ObjList.end();
	delete *itor;
	ObjList.erase(itor);
}

void CObjectManager::RemoveObject(CGameObject *_temp)
{
	
	for (itor = ObjList.begin(); itor != ObjList.end(); itor++)
	{
		if (*itor == _temp)
		{

			delete *itor;

			ObjList.erase(itor);
			break;
		}
	}
}


void CObjectManager::RenderAllObject(/*CSprite* _sprite*/)
{
	
	for (itor = ObjList.begin(); itor != ObjList.end(); itor++)
	{
		(*itor)->Draw(/*_sprite*/);
	}
}

void CObjectManager::FrameMoveAllObject(CInput* _pInput, float _dTime)
{
	
	for (itor = ObjList.begin(); itor != ObjList.end(); itor++)
	{
		(*itor)->Update(_pInput, _dTime);
	}
}

void CObjectManager::SetTargetPosition(int _TargetKey, D3DXVECTOR2 _pos)
{
	// 키값이 일치하는 오브젝트 탐색.
	list<CGameObject*>::iterator TempItor;
	for (TempItor = ObjList.begin(); TempItor != ObjList.end(); TempItor++)
	{
		if ((*TempItor)->ObjectKey == _TargetKey)
		{
			//(*TempItor)->Update(_pInput, _dTime);
			(*TempItor)->SetPosition(_pos);
			return;
		}
	}
}

void CObjectManager::RemoveAllObject()
{
	for (itor = ObjList.begin(); itor != ObjList.end();)
	{
		delete *itor;
		ObjList.erase(itor++);
		//ObjList.erase(itor) 하는 경우 반복자가 다음위치를 잃어버리게 된다
		//위의 방법 혹은 itor=ObjList.erase(itor) 해야한다.
	}
}

CGameObject * CObjectManager::Collision(CGameObject * pObject)
{
	for (itor = ObjList.begin(); itor != ObjList.end(); itor++)
	{
		if (Collision(pObject, *itor))
			return *itor;
	}
	return nullptr;
}

BOOL CObjectManager::Collision(CGameObject * obj1, CGameObject * obj2)
{
	RECT range = obj1->GetRange();

	D3DXVECTOR3 point[2] = { 
		{(float)range.left, (float)range.top, 0}, 
		{ (float)range.right, (float)range.bottom, 0} };

	for (int i = 0; i < 2; i++)
	{
		if (obj2->IsIn(point[i]))
			return TRUE;
	}

	return FALSE;
}

void CollisionManager::RemoveObject(CGameObject * _temp)
{
	for (itor = ObjList.begin(); itor != ObjList.end(); itor++)
	{
		if (*itor == _temp)
		{
			ObjList.erase(itor);
			break;
		}
	}
}
