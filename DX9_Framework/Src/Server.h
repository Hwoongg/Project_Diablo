#pragma once

//extern CD3DApp* g_pApp;
//extern Scene* g_pNowOpened;


#define SERVERIPV4  "127.0.0.1"
#define SERVERPORT  9000


//static u_short       g_port; // ���� ��Ʈ ��ȣ
//static SOCKET        g_sock; // Ŭ���̾�Ʈ ����
//static HANDLE        g_hClientThread; // ������ �ڵ�
//static volatile BOOL g_bStart; // ��� ���� ����
//static MOVE_MSG g_moveMsg;

DWORD WINAPI ClientMain(LPVOID arg);
DWORD WINAPI ReadThread(LPVOID arg);
DWORD WINAPI WriteThread(LPVOID arg);

void err_quit(char *msg);
void err_display(char *msg);
int recvn(SOCKET s, char *buf, int len, int flags);