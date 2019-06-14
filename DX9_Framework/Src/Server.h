#pragma once

//extern CD3DApp* g_pApp;
//extern Scene* g_pNowOpened;


#define SERVERIPV4  "127.0.0.1"
#define SERVERPORT  9000


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