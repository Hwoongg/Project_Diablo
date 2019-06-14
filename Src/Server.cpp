#include "_StdAfx.h"

u_short       g_port; // 서버 포트 번호
SOCKET        g_sock; // 클라이언트 소켓
HANDLE        g_hClientThread; // 스레드 핸들
volatile BOOL g_bStart; // 통신 시작 여부
MOVE_MSG g_moveMsg;

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

	while (true)
	{
		retval = recvn(g_sock, (char *)&comm_msg, BUFSIZE, 0);
		if (retval == 0 || retval == SOCKET_ERROR) {
			break;
		}

		if (comm_msg.type == MOVING) {
			move_msg = (MOVE_MSG *)&comm_msg;

			// 캐릭터 식별자, 좌표값을 통해 이동처리
			// 클라이언트의 모든 캐릭터 좌표를 갱신한다.
			// ...

		}
		else if (comm_msg.type == PLAYERKEY)
		{
			playerkey_msg = (PLAYERKEY_MSG*)&comm_msg;

			// 플레이어 식별자 입력
			// ...
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
		// 무브 메시지 통신에는 적합하지 않다.
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
