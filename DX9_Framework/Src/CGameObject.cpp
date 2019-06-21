#include "_StdAfx.h"

extern CD3DApp* g_pApp;

extern SOCKET g_sock;

CGameObject::CGameObject()
{
	m_Stat = UNKNOWN;
	m_Pos.x = 0;
	m_Pos.y = 0;

	m_Scale = { 1,1 };
	m_pObjTex = NULL;

	dx = 0;
	dy = 0;
}

CGameObject::CGameObject(LPCWSTR sFile, D3DXVECTOR2 _pos)
{
	m_Scale = { 1,1 };

	dx = 0;
	dy = 0;

	//Create(sFile, _pos);
}

CGameObject::~CGameObject()
{

}


void CGameObject::Create(/*CTexture* pTex*/LPCWSTR sFile, D3DXVECTOR2 _pos, int _objKey)
{
	ObjectKey = _objKey;
	m_Pos = _pos; // 복사 가능?

	//m_pObjTex = pTex; // 텍스쳐 포인터 연결
	m_pObjTex = g_pApp->GetrManager()->GetTexture(sFile);

	// 텍스쳐 포인터로부터 텍스쳐 이미지의 크기를 TexRt에 받아왔음. 출력용 변수로 사용
	m_pObjTex->GetImageRect(&m_TexRt);

	// Scale된 최종 실제 크기 정보 생성
	m_ObjRt.right = m_TexRt.right*m_Scale.x;
	m_ObjRt.left = m_TexRt.left*m_Scale.x;
	m_ObjRt.top = m_TexRt.top*m_Scale.y;
	m_ObjRt.bottom = m_TexRt.bottom*m_Scale.y;


	///////////////////////////////////////////////////
	// 행렬 세팅값들...
	// scale
	//m_Scale = { .5f,.5f };
	// rotate
	//D3DXVECTOR2 Center = { xpos,ypos };
	//FLOAT angle = 0;

	// Translate dx dy position
	//D3DXVECTOR2 position = {};

	m_Color = D3DXCOLOR(1, 1, 1, 1.0f);
}


void CGameObject::Update(CInput* pInput, float _dTime)
{
	D3DXVECTOR2 oldPos = m_Pos;

	if (pInput->KeyPress(VK_LEFT))
		m_Pos.x -= dx*_dTime;
	else if (pInput->KeyPress(VK_RIGHT))
		m_Pos.x += dx * _dTime;
	if (pInput->KeyPress(VK_UP))
		m_Pos.y -= dy * _dTime;
	else if (pInput->KeyPress(VK_DOWN))
		m_Pos.y += dy * _dTime;

	if (m_Pos.x + m_ObjRt.right / 2 > 800)
	{
		m_Pos.x = 800 - m_ObjRt.right / 2;
	}
	if (m_Pos.x + m_ObjRt.right / 2 < 0)
	{
		m_Pos.x = 0 - m_ObjRt.right / 2;
	}
	if (m_Pos.y + m_ObjRt.bottom / 2 > 600)
	{
		m_Pos.y = 600 - m_ObjRt.bottom / 2;
	}
	if (m_Pos.y + m_ObjRt.bottom / 2 <0)
	{
		m_Pos.y = 0 - m_ObjRt.bottom / 2;
	}

	// 좌표 변동이 있다면
	if (m_Pos != oldPos)
	{
		// 서버에 알린다.
		SendMoveMSG(ObjectKey, m_Pos);
	}

}

void CGameObject::Draw(/*CSprite * pCSpr*/)
{
	// 이제부턴 그릴 위치가 m_TexRt(텍스쳐 전체 크기) 가 아닌 
	// 그려질 일부분을 AniInfo로 부터 얻어서 그릴것
	RECT drawRt = m_aniInfo.GetSrcRect();
	g_pApp->GetSprite()->Draw(m_pObjTex->GetTexture(), &drawRt, &m_Scale, NULL, NULL, &m_Pos, m_Color);
}

RECT CGameObject::GetRange()
{
	RECT range;

	range.left = m_Pos.x;
	range.top = m_Pos.y;
	range.right = m_Pos.x + m_ObjRt.right;
	range.bottom = m_Pos.y + m_ObjRt.bottom;

	return range;
}

BOOL CGameObject::IsIn(D3DXVECTOR3 mousePos)
{
	RECT range = GetRange();
	if (
		((mousePos.x > range.left) && (mousePos.x < range.right))
		&& ((mousePos.y > range.top) && (mousePos.y < range.bottom))
		)
	{
		return TRUE;
	}


	return FALSE;
}

void CGameObject::SetPosition(D3DXVECTOR2 _pos)
{
	m_Pos = _pos;
}