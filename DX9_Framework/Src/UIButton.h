#pragma once

//////////////////////////////////////////
// ��ư UI ������Ʈ�� ���� Ŭ����
// ��ư ������ ���� �޼ҵ尡 �ʿ�
//
class UIButton : public CGameObject
{
public:
	Scene* m_pMediator; // �ڽ��� ���� �� ����
	BOOL m_IsPushed;

public:
	// ��ư�� ������ �� �Ҽ� ���� �˷����� �� ��
	UIButton();
	UIButton(Scene* _mediator, LPCWSTR sFile, D3DXVECTOR2 _pos);
	virtual ~UIButton();

	// �ڽ��� ������ �� Pushed ������ Ȱ��ȭ �ϰ� �� ��
	void Update(CInput*, float _dTime);

	// Vector3 ������ ���콺 ��ǥ�� �޾Ƽ� ���콺 ��ǥ�� UI���� ������ üũ�Ѵ�
	//BOOL IsIn(D3DXVECTOR3 mousePos);
};

