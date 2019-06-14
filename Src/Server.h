#pragma once

//extern CD3DApp* g_pApp;
//extern Scene* g_pNowOpened;


#define SERVERIPV4  "127.0.0.1"
#define SERVERPORT  9000
#define BUFSIZE     256                    // 전송 메시지 전체 크기
#define MSGSIZE     (BUFSIZE-sizeof(int))  // 채팅 메시지 최대 길이

#define PLAYERKEY 1000
#define MOVING 1001

// 공통 메시지 형식
// sizeof(COMM_MSG) == 256
struct COMM_MSG
{
	int  type;
	char dummy[MSGSIZE];
};

// 접속 시 플레이어 키 발급
struct PLAYERKEY_MSG
{
	int type;
	int playerKey;
	char dummy[BUFSIZE - 8];
};

// 이동 메시지
struct MOVE_MSG
{
	int  type;
	float xPos, yPos;
	char dummy[BUFSIZE - 12];
};


//static u_short       g_port; // 서버 포트 번호
//static SOCKET        g_sock; // 클라이언트 소켓
//static HANDLE        g_hClientThread; // 스레드 핸들
//static volatile BOOL g_bStart; // 통신 시작 여부
//static MOVE_MSG g_moveMsg;

DWORD WINAPI ClientMain(LPVOID arg);
DWORD WINAPI ReadThread(LPVOID arg);
DWORD WINAPI WriteThread(LPVOID arg);

void err_quit(char *msg);
void err_display(char *msg);
int recvn(SOCKET s, char *buf, int len, int flags);