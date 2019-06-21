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
		// ��ĩ temp�� ������ �ּҸ� ����ų ���̶� ������ �� ����.
		// temp�� ����Ű�� ���� �����Ҵ��ϴ°��� �ƴ�,
		// �����Ҵ�� �ּҰ� temp�� ���� �Ǵ� ��.
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
	// Ű���� ��ġ�ϴ� ������Ʈ Ž��.
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
		//ObjList.erase(itor) �ϴ� ��� �ݺ��ڰ� ������ġ�� �Ҿ������ �ȴ�
		//���� ��� Ȥ�� itor=ObjList.erase(itor) �ؾ��Ѵ�.
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
