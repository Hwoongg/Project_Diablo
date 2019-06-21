#include "_StdAfx.h"
#include "Messages.h"

u_short       g_port; // ���� ��Ʈ ��ȣ
SOCKET        g_sock; // Ŭ���̾�Ʈ ����
HANDLE        g_hClientThread; // ������ �ڵ�
volatile BOOL g_bStart; // ��� ���� ����

COMM_MSG g_commMsg; // ��ȸ�� �޽��� ���ſ�.
COMM_MSG g_fieldState;
MOVE_MSG g_moveMsg;

extern CD3DApp* g_pApp;
extern Scene* g_pNowOpened;

extern int g_MyPlayerKey;

DWORD WINAPI ClientMain(LPVOID arg)
{
	int retval;


	// socket()
	g_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (g_sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIPV4);
	serveraddr.sin_port = htons(g_port);
	retval = connect(g_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");


	MessageBox(NULL, L"������ �����߽��ϴ�.", L"����!", MB_ICONINFORMATION);

	// �б� & ���� ������ ����
	HANDLE hThread[2];
	hThread[0] = CreateThread(NULL, 0, ReadThread, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, WriteThread, NULL, 0, NULL);
	if (hThread[0] == NULL || hThread[1] == NULL) {
		MessageBox(NULL, L"�����带 ������ �� �����ϴ�."
			"\r\n���α׷��� �����մϴ�.",
			L"����!", MB_ICONERROR);
		exit(1);
	}

	g_bStart = TRUE;

	// ������ ���� ���
	retval = WaitForMultipleObjects(2, hThread, FALSE, INFINITE);
	retval -= WAIT_OBJECT_0;
	if (retval == 0)
		TerminateThread(hThread[1], 1);
	else
		TerminateThread(hThread[0], 1);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	g_bStart = FALSE;

	MessageBox(NULL, L"������ ������ �������ϴ�", L"�˸�", MB_ICONINFORMATION);

	closesocket(g_sock);
	return 0;
}

// ���� �Լ� ���� ��� �� ����
void err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCWSTR)msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// ���� �Լ� ���� ���
void err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// ������ ���� ������
DWORD WINAPI ReadThread(LPVOID arg)
{
	int retval;

	COMM_MSG comm_msg;
	MOVE_MSG *move_msg;
	PLAYERKEY_MSG *playerkey_msg;
	ADDMEMBER_MSG* addmem_Msg;

	while (true)
	{
		retval = recvn(g_sock, (char *)&comm_msg, BUFSIZE, 0);
		if (retval == 0 || retval == SOCKET_ERROR) {
			break;
		}

		if (comm_msg.type == MEMLIST) // ��� ����Ʈ�� �޾��� ���
		{
			// ��� ����Ʈ�� �����.
			g_fieldState = comm_msg;
		}
		else if (comm_msg.type == MOVING) // Move �޽����� �޾Ҵٸ�
		{
			move_msg = (MOVE_MSG *)&comm_msg;

			// ĳ���� �ĺ���, ��ǥ���� ���� �̵�ó��
			// Ŭ���̾�Ʈ�� ��� ĳ���� ��ǥ�� �����Ѵ�.

			D3DXVECTOR2 newPos;
			newPos.x = move_msg->MoveObj.xPos;
			newPos.y = move_msg->MoveObj.yPos;
			g_pNowOpened->SetTargetPosition(move_msg->MoveObj.Key, newPos);
		}
		else if (comm_msg.type == PLAYERKEY) // �÷��̾� Ű�� �߱޹޾��� ���
		{
			playerkey_msg = (PLAYERKEY_MSG*)&comm_msg;

			// Ŭ���̾�Ʈ�� �߱޹��� Ű�� ���!
			g_MyPlayerKey = playerkey_msg->playerKey;
		}
		else if (comm_msg.type == ADDMEMBER) // ��� �߰� �޽����� �޾Ҵٸ� 
		{
			addmem_Msg = (ADDMEMBER_MSG*)&comm_msg;

			// ��ǥ�� �а�...
			D3DXVECTOR2 tempPos;
			tempPos.x = addmem_Msg->AddObj.xPos;
			tempPos.y = addmem_Msg->AddObj.yPos;

			// ��Ŷ�� ���Ե� �÷��̾� Ű�� �о� ��� ����!
			g_pNowOpened->AddObject(new Hero(L"Texture/zerg.png", tempPos
				,g_MyPlayerKey, addmem_Msg->AddObj.Key));
		}

	}
	return 0;
}

// ������ �߽� ������
DWORD WINAPI WriteThread(LPVOID arg)
{
	int retval;

	// ������ ������ ���
	while (1)
	{
		// ���� �޽����� �� �����Ӹ��� �Ѹ��� ���� ���ϴ°� ���� ��.
		/*retval = send(g_sock, (char *)&g_moveMsg, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			break;
		}*/
	}

	return 0;
}

// ����� ���� ������ ���� �Լ�
int recvn(SOCKET s, char *buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
}

void SendMoveMSG(int _Key, D3DXVECTOR2 _pos)
{
	MOVE_MSG move_msg;

	move_msg.type = MOVING;
	move_msg.MoveObj.Key = _Key;
	move_msg.MoveObj.xPos = _pos.x;
	move_msg.MoveObj.yPos = _pos.y;

	int retval;
	retval = send(g_sock, (char*)&move_msg, BUFSIZE, 0);
}