#include "_StdAfx.h"

extern CD3DApp* g_pApp;

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


void CGameObject::Create(/*CTexture* pTex*/LPCWSTR sFile, D3DXVECTOR2 _pos)
{
	m_Pos = _pos; // ���� ����?

	//m_pObjTex = pTex; // �ؽ��� ������ ����
	m_pObjTex = g_pApp->GetrManager()->GetTexture(sFile);

	// �ؽ��� �����ͷκ��� �ؽ��� �̹����� ũ�⸦ TexRt�� �޾ƿ���. ��¿� ������ ���
	m_pObjTex->GetImageRect(&m_TexRt);

	// Scale�� ���� ���� ũ�� ���� ����
	m_ObjRt.right = m_TexRt.right*m_Scale.x;
	m_ObjRt.left = m_TexRt.left*m_Scale.x;
	m_ObjRt.top = m_TexRt.top*m_Scale.y;
	m_ObjRt.bottom = m_TexRt.bottom*m_Scale.y;


	///////////////////////////////////////////////////
	// ��� ���ð���...
	// scale
	//m_Scale = { .5f,.5f };
	// rotate
	//D3DXVECTOR2 Center = { xpos,ypos };
	//FLOAT angle = 0;

	// Translate dx dy position
	//D3DXVECTOR2 position = {};

	m_Color = D3DXCOLOR(1, 1, 1, 1.0f);
}

// �밢�� �ڵ� �̵� ������ ������ ����
void CGameObject::Update(CInput* pInput, float _dTime)
{
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

}

void CGameObject::Draw(/*CSprite * pCSpr*/)
{
	//pCSpr->Draw(m_pObjTex->GetTexture(), &m_TexRt, &m_Scale, NULL, NULL, &m_Pos, m_Color);

	//g_pApp->GetSprite()->Draw(m_pObjTex->GetTexture(), &m_TexRt, &m_Scale, NULL, NULL, &m_Pos, m_Color);

	// �������� �׸� ��ġ�� m_TexRt(�ؽ��� ��ü ũ��) �� �ƴ� 
	// �׷��� �Ϻκ��� AniInfo�� ���� �� �׸���
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

