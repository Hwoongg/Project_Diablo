#pragma once

//////////////////////////////////////////
// 버튼 UI 오브젝트에 대한 클래스
// 버튼 영역을 얻어올 메소드가 필요
//
class UIButton : public CGameObject
{
public:
	Scene* m_pMediator; // 자신이 속한 씬 정보
	BOOL m_IsPushed;

public:
	// 버튼이 생성될 때 소속 씬이 알려져야 할 것
	UIButton();
	UIButton(Scene* _mediator, LPCWSTR sFile, D3DXVECTOR2 _pos);
	virtual ~UIButton();

	// 자신이 눌렸을 때 Pushed 변수를 활성화 하게 될 것
	void Update(CInput*, float _dTime);

	// Vector3 형식의 마우스 좌표를 받아서 마우스 좌표가 UI범위 내인지 체크한다
	//BOOL IsIn(D3DXVECTOR3 mousePos);
};

