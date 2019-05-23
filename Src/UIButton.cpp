#include "_StdAfx.h"



UIButton::UIButton()
{
}

UIButton::UIButton(Scene * _mediator, LPCWSTR sFile, D3DXVECTOR2 _pos)
{
	m_pMediator = _mediator;
	m_Scale = { 3.f, 3.f };
	Create(sFile, _pos);

	// 애니메이션 데이터 설정...
	m_aniInfo.ImageWidth = m_TexRt.right;
	m_aniInfo.ImageHeight = m_TexRt.bottom;

	/////////////////////////////////////////////
	// 애니메이션 없는 통짜 텍스쳐
	m_aniInfo.unitSizeX = m_TexRt.right;
	m_aniInfo.unitSizeY = m_TexRt.bottom;

	m_aniInfo.currentFrame = 0;
	m_aniInfo.totalFrameCount = 0;
	m_aniInfo.aniIndex = 0;
	m_aniInfo.totalAniCount = 0;
	/////////////////////////////////////////////

	m_aniInfo.aniDelay = 0.1f;
	m_aniInfo.aniDuration = m_aniInfo.aniDelay;
	
}

void UIButton::Update(CInput *pInput, float _dTime)
{
	if (pInput)
	{
		if (pInput->BtnPress(0))
		{
			if (IsIn(pInput->GetMousePos()))
			{
				m_pMediator->Command(this);
				m_IsPushed = TRUE;
			}
		}
	}


	if (m_IsPushed)
	{
		if (IsIn(pInput->GetMousePos()))
		{
			//m_pMediator->Command(this, );
			m_IsPushed = FALSE;
		}
	}



}

//BOOL UIButton::IsIn(D3DXVECTOR3 mousePos)
//{
//	RECT range = GetRange();
//	if (
//		((mousePos.x > range.left) && (mousePos.x < range.right))
//		&& ((mousePos.y > range.top) && (mousePos.y < range.bottom))
//		)
//	{
//		return TRUE;
//	}
//
//
//	return FALSE;
//}


UIButton::~UIButton()
{
}
