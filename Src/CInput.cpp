#include "_StdAfx.h"

// 휠마우스를 쓰려면 이 구문은 반드시 필요.
//#define _WIN32_WINNT 0x0400

CInput::CInput(void)
{
	m_hWnd = NULL; // for Mouse

	memset(m_KeyOld, 0, sizeof(m_KeyOld));
	memset(m_KeyCur, 0, sizeof(m_KeyCur));
	memset(m_KeyMap, 0, sizeof(m_KeyMap));

	memset(m_BtnCur, 0, sizeof(m_BtnCur));
	memset(m_BtnOld, 0, sizeof(m_BtnOld));
	memset(m_BtnMap, 0, sizeof(m_BtnMap));

	m_vcCur = D3DXVECTOR3(0, 0, 0);
	m_vcOld = D3DXVECTOR3(0, 0, 0);
	m_vcEps = D3DXVECTOR3(0, 0, 0);


	m_dTimeDC = 0;
	memset(m_dBtnBgn, 0, sizeof(m_dBtnBgn));
	memset(m_dBtnCnt, 0, sizeof(m_dBtnCnt));

	SetKeyboardState(m_KeyCur);
}


CInput::~CInput(void)
{
}

INT	CInput::Create(HWND hWnd)
{
	m_hWnd = hWnd;

	memset(m_KeyOld, 0, sizeof(m_KeyOld));
	memset(m_KeyCur, 0, sizeof(m_KeyCur));
	memset(m_KeyMap, 0, sizeof(m_KeyMap));

	memset(m_BtnCur, 0, sizeof(m_BtnCur));
	memset(m_BtnOld, 0, sizeof(m_BtnOld));
	memset(m_BtnMap, 0, sizeof(m_BtnMap));

	m_vcCur = D3DXVECTOR3(0, 0, 0);
	m_vcOld = D3DXVECTOR3(0, 0, 0);
	m_vcEps = D3DXVECTOR3(0, 0, 0);


	m_dTimeDC = GetDoubleClickTime();

	memset(m_dBtnBgn, 0, sizeof(m_dBtnBgn));
	memset(m_dBtnCnt, 0, sizeof(m_dBtnCnt));

	m_dBtnBgn[0] = GetTickCount();

	for (int i = 1; i<MAX_INPUT_BTN; ++i)
	{
		m_dBtnBgn[i] = m_dBtnBgn[0];
	}

	memset(m_dBtnCnt, 0, sizeof(m_dBtnCnt));

	//UINT ucNumLines=3;  // 3 is the default
	UINT ucNumLines = 0;  // 3 is the default
	SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &ucNumLines, 0);

	return 0;
}

INT CInput::FrameMove()	// Mouse
{
	INT i = 0;

	// 1. current 값을 old에 복사, 이전 상태를 저장한다.
	memcpy(m_KeyOld, m_KeyCur, sizeof(m_KeyOld));
	memcpy(m_BtnOld, m_BtnCur, sizeof(m_BtnOld));		// Mouse


	// 2. Current 와 Map의 값을 0으로 초기화
	memset(m_KeyCur, 0, sizeof(m_KeyCur));
	memset(m_KeyMap, 0, sizeof(m_KeyMap));

	memset(m_BtnCur, 0, sizeof(m_BtnCur));				// Mouse
	memset(m_BtnMap, 0, sizeof(m_BtnMap));


	//3. current 이벤트 를 가져옴
	GetKeyboardState(m_KeyCur);


	// Keyboard
	for (i = 0; i<MAX_INPUT_KEY; ++i)
	{
		BYTE	vKey = m_KeyCur[i] & 0x80;		// 현재의 키보드 상태를 읽어온다.
		m_KeyCur[i] = (vKey) ? 1 : 0;				// 키보드 상태를 0과 1로 정한다.

		INT nOld = m_KeyOld[i];
		INT nCur = m_KeyCur[i];

		if (0 == nOld && 1 == nCur) m_KeyMap[i] = EINPUT_DOWN;	// Down
		else if (1 == nOld && 0 == nCur) m_KeyMap[i] = EINPUT_UP;	// UP
		else if (1 == nOld && 1 == nCur) m_KeyMap[i] = EINPUT_PRESS;	// PRESS
		else							m_KeyMap[i] = EINPUT_NONE;	// NONE
	}


	// Mouse button
	m_BtnCur[0] = m_KeyCur[VK_LBUTTON];	// Left Button
	m_BtnCur[1] = m_KeyCur[VK_RBUTTON];	// Right Button
	m_BtnCur[2] = m_KeyCur[VK_MBUTTON];	// Middle Button


	for (i = 0; i<MAX_INPUT_BTN; ++i)
	{
		INT nOld = m_BtnOld[i];
		INT nCur = m_BtnCur[i];

		if (0 == nOld && 1 == nCur) m_BtnMap[i] = EINPUT_DOWN;	// Down
		else if (1 == nOld && 0 == nCur) m_BtnMap[i] = EINPUT_UP;	// UP
		else if (1 == nOld && 1 == nCur) m_BtnMap[i] = EINPUT_PRESS;	// PRESS
		else							m_BtnMap[i] = EINPUT_NONE;	// NONE
	}



	// 4. Update Mouse Position
	POINT pt;
	::GetCursorPos(&pt);
	::ScreenToClient(m_hWnd, &pt);

	m_vcCur.x = FLOAT(pt.x);
	m_vcCur.y = FLOAT(pt.y);

	m_vcEps = m_vcCur - m_vcOld;

	m_vcOld = m_vcCur;



	//5. Double Check
	DWORD dBtnCur = GetTickCount();

	for (i = 0; i<MAX_INPUT_BTN; ++i)
	{
		if (EINPUT_DOWN == m_BtnMap[i])
		{
			if (1 == m_dBtnCnt[i])
			{
				if ((dBtnCur - m_dBtnBgn[i]) >= m_dTimeDC)
				{
					m_dBtnCnt[i] = 0;
				}
			}


			++m_dBtnCnt[i];

			if (1 == m_dBtnCnt[i])
			{
				m_dBtnBgn[i] = dBtnCur;
			}
		}


		if (EINPUT_UP == m_BtnMap[i])
		{
			if (1 == m_dBtnCnt[i])
			{
				if ((dBtnCur - m_dBtnBgn[i]) >= m_dTimeDC)
				{
					m_dBtnCnt[i] = 0;
				}
			}

			else if (2 == m_dBtnCnt[i])
			{
				if ((dBtnCur - m_dBtnBgn[i]) <= m_dTimeDC)
				{
					m_BtnMap[i] = EINPUT_DBCLC;
				}

				m_dBtnCnt[i] = 0;
			}
		}

	}

	//
	//	mouse_event(MOUSEEVENTF_MOVE, -1, 0, 0,0);

	return 0;
}
BOOL CInput::KeyDown(INT nKey)
{
	return m_KeyMap[nKey] == EINPUT_DOWN;
}

BOOL CInput::KeyUp(INT nKey)
{
	return m_KeyMap[nKey] == EINPUT_UP;
}

BOOL CInput::KeyPress(INT nKey)
{
	return m_KeyMap[nKey] == EINPUT_PRESS;
}

INT CInput::KeyState(INT nKey)
{
	return m_KeyMap[nKey];
}

// Mouse

BOOL CInput::BtnDown(INT nBtn)
{
	return m_BtnMap[nBtn] == EINPUT_DOWN;
}

BOOL CInput::BtnUp(INT nBtn)
{
	return m_BtnMap[nBtn] == EINPUT_UP;
}

BOOL CInput::BtnPress(INT nBtn)
{
	return m_BtnMap[nBtn] == EINPUT_PRESS;
}

INT CInput::BtnState(INT nBtn)
{
	return m_BtnMap[nBtn];
}

D3DXVECTOR3 CInput::GetMousePos()
{
	return m_vcCur;
}


D3DXVECTOR3 CInput::GetMouseEps()
{
	return m_vcEps;
}

LRESULT CInput::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_MOUSEWHEEL:
	{
		INT c = HIWORD(wParam);
		INT d = LOWORD(wParam);

		c = short(c);
		m_vcCur.z += FLOAT(c);
		break;
	}
	}

	return 0;
}
