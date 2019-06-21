#include "_StdAfx.h"
#include "Messages.h"

u_short       g_port; // 서버 포트 번호
SOCKET        g_sock; // 클라이언트 소켓
HANDLE        g_hClientThread; // 스레드 핸들
volatile BOOL g_bStart; // 통신 시작 여부

COMM_MSG g_commMsg; // 일회성 메시지 수신용.
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


	MessageBox(NULL, L"서버에 접속했습니다.", L"성공!", MB_ICONINFORMATION);

	// 읽기 & 쓰기 스레드 생성
	HANDLE hThread[2];
	hThread[0] = CreateThread(NULL, 0, ReadThread, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, WriteThread, NULL, 0, NULL);
	if (hThread[0] == NULL || hThread[1] == NULL) {
		MessageBox(NULL, L"스레드를 시작할 수 없습니다."
			"\r\n프로그램을 종료합니다.",
			L"실패!", MB_ICONERROR);
		exit(1);
	}

	g_bStart = TRUE;

	// 스레드 종료 대기
	retval = WaitForMultipleObjects(2, hThread, FALSE, INFINITE);
	retval -= WAIT_OBJECT_0;
	if (retval == 0)
		TerminateThread(hThread[1], 1);
	else
		TerminateThread(hThread[0], 1);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	g_bStart = FALSE;

	MessageBox(NULL, L"서버가 접속을 끊었습니다", L"알림", MB_ICONINFORMATION);

	closesocket(g_sock);
	return 0;
}

// 소켓 함수 오류 출력 후 종료
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

// 소켓 함수 오류 출력
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

// 데이터 수신 스레드
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

		if (comm_msg.type == MEMLIST) // 멤버 리스트를 받았을 경우
		{
			// 멤버 리스트를 덮어쓴다.
			g_fieldState = comm_msg;
		}
		else if (comm_msg.type == MOVING) // Move 메시지를 받았다면
		{
			move_msg = (MOVE_MSG *)&comm_msg;

			// 캐릭터 식별자, 좌표값을 통해 이동처리
			// 클라이언트의 모든 캐릭터 좌표를 갱신한다.

			D3DXVECTOR2 newPos;
			newPos.x = move_msg->MoveObj.xPos;
			newPos.y = move_msg->MoveObj.yPos;
			g_pNowOpened->SetTargetPosition(move_msg->MoveObj.Key, newPos);
		}
		else if (comm_msg.type == PLAYERKEY) // 플레이어 키를 발급받았을 경우
		{
			playerkey_msg = (PLAYERKEY_MSG*)&comm_msg;

			// 클라이언트에 발급받은 키를 등록!
			g_MyPlayerKey = playerkey_msg->playerKey;
		}
		else if (comm_msg.type == ADDMEMBER) // 멤버 추가 메시지를 받았다면 
		{
			addmem_Msg = (ADDMEMBER_MSG*)&comm_msg;

			// 좌표를 읽고...
			D3DXVECTOR2 tempPos;
			tempPos.x = addmem_Msg->AddObj.xPos;
			tempPos.y = addmem_Msg->AddObj.yPos;

			// 패킷에 포함된 플레이어 키를 읽어 멤버 생성!
			g_pNowOpened->AddObject(new Hero(L"Texture/zerg.png", tempPos
				,g_MyPlayerKey, addmem_Msg->AddObj.Key));
		}

	}
	return 0;
}

// 데이터 발신 스레드
DWORD WINAPI WriteThread(LPVOID arg)
{
	int retval;

	// 서버와 데이터 통신
	while (1)
	{
		// 무브 메시지를 매 프레임마다 뿌리는 것은 피하는게 좋을 듯.
		/*retval = send(g_sock, (char *)&g_moveMsg, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			break;
		}*/
	}

	return 0;
}

// 사용자 정의 데이터 수신 함수
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