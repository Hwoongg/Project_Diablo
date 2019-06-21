#pragma once


////////////////////////////////////////////////////////
//
// ������ ������Ʈ �Ӽ��� ���� Ŭ����.
//

enum ObjectType // �Ŵ��� Ŭ�������� �����ϰ� Ȱ���ϴ���
{
	UNKNOWN,
	HERO,
	ENEMY,
	BUTTON
};

// ���� �ؽ��� ���� ��뿡 ���� �����غ� �� ����
// �ؽ��ĸ� �Ű������� ���� �ʰ� ���¿� ���� create �� ���..
// �ε��� �ؽ��ĸ� ����ȭ ���־�� �� ���ۿ� ���� ������
class CGameObject : public IGameObject
{
public:
	ObjectType m_Stat; // �ش� ������Ʈ�� �Ӽ�
	int ObjectKey;

protected:
	CTexture* m_pObjTex; // ������Ʈ �̹��� �ؽ��� ������
	RECT m_TexRt; // �ؽ��� �̹��� ���� ������

	RECT m_ObjRt; // �浹ó�� � �ʿ��� ������ ����� ���� ������Ʈ ũ��
	float dx, dy; // �̵��ӵ�

	D3DXVECTOR2 m_Pos;
	// ��ȯ�Ӽ���

	D3DXVECTOR2 m_Scale;
	FLOAT m_Angle;
	D3DXVECTOR2 m_Center; // ȸ�� �߽�
	
	D3DCOLOR m_Color;

	// �׸��� ��� ������ ��������Ʈ Draw()�� �ִ�
	// ������Ʈ ������Ʈ �κп��� Ȱ���ϵ��� �Ѵ�
	
	AnimationInfo m_aniInfo;

public:
	CGameObject();
	// ���ϸ�, ��ǥ �޾� Create �ϴ� ������ �߰��Ѵ�.
	CGameObject(LPCWSTR sFile, D3DXVECTOR2 _pos);
	virtual ~CGameObject();

	// ���ϸ�, ��ǥ �Ű������� �ϵ���
	void Create(LPCWSTR sFile, D3DXVECTOR2 _pos, int _objKey = -1);

	// �⺻ ���Ż���. Ű �Է� ���� ��ǥ�� �̵��Ѵ�.
	void Update(CInput*, float _dTime);

	void SetPosition(D3DXVECTOR2 _pos);

	//��������Ʈ Ŭ������ ������ �޾� �׸���
	void Draw(/*CSprite* pCSpr*/);

	RECT GetRange();

	// Vector3 ������ ���콺 ��ǥ�� �޾Ƽ� ���콺 ��ǥ�� UI���� ������ üũ�Ѵ�
	BOOL IsIn(D3DXVECTOR3 mousePos);

	//virtual void Release();
};

