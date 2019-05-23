#pragma once


////////////////////////////////////////////////////////
//
// 게임의 오브젝트 속성에 대한 클래스.
//

enum ObjStatus // 매니저 클래스에서 유용하게 활용하는중
{
	UNKNOWN,
	HERO,
	ENEMY,
	BUTTON
};

// 현재 텍스쳐 변수 운용에 관해 생각해볼 점 있음
// 텍스쳐를 매개변수로 받지 않고 상태에 맞춰 create 할 방법..
// 로딩된 텍스쳐를 전역화 해주어야 할 수밖에 없는 것인지
class CGameObject : public IGameObject
{
public:
	ObjStatus m_Stat; // 해당 오브젝트의 속성

protected:
	CTexture* m_pObjTex; // 오브젝트 이미지 텍스쳐 포인터
	RECT m_TexRt; // 텍스쳐 이미지 파일 사이즈

	RECT m_ObjRt; // 충돌처리 등에 필요할 스케일 적용된 실제 오브젝트 크기
	float dx, dy; // 이동속도

	D3DXVECTOR2 m_Pos;
	// 변환속성값

	D3DXVECTOR2 m_Scale;
	FLOAT m_Angle;
	D3DXVECTOR2 m_Center; // 회전 중심
	
	D3DCOLOR m_Color;

	// 그리기 행렬 관련은 스프라이트 Draw()에 있다
	// 오브젝트 업데이트 부분에서 활용하도록 한다
	
	AnimationInfo m_aniInfo;

public:
	CGameObject();
	// 파일명, 좌표 받아 Create 하는 생성자 추가한다.
	CGameObject(LPCWSTR sFile, D3DXVECTOR2 _pos);
	virtual ~CGameObject();

	// 파일명, 좌표 매개변수로 하도록
	void Create(LPCWSTR sFile, D3DXVECTOR2 _pos);

	// 기본 갱신상태. 키 입력 따라 좌표를 이동한다.
	void Update(CInput*, float _dTime);

	//스프라이트 클래스의 도움을 받아 그린다
	void Draw(/*CSprite* pCSpr*/);

	RECT GetRange();

	// Vector3 형식의 마우스 좌표를 받아서 마우스 좌표가 UI범위 내인지 체크한다
	BOOL IsIn(D3DXVECTOR3 mousePos);

	//virtual void Release();
};

