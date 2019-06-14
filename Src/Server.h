#pragma once

//extern CD3DApp* g_pApp;
//extern Scene* g_pNowOpened;


#define SERVERIPV4  "127.0.0.1"
#define SERVERPORT  9000
#define BUFSIZE     256                    // ���� �޽��� ��ü ũ��
#define MSGSIZE     (BUFSIZE-sizeof(int))  // ä�� �޽��� �ִ� ����

#define PLAYERKEY 1000
#define MOVING 1001

// ���� �޽��� ����
// sizeof(COMM_MSG) == 256
struct COMM_MSG
{
	int  type;
	char dummy[MSGSIZE];
};

// ���� �� �÷��̾� Ű �߱�
struct PLAYERKEY_MSG
{
	int type;
	int playerKey;
	char dummy[BUFSIZE - 8];
};

// �̵� �޽���
struct MOVE_MSG
{
	int  type;
	float xPos, yPos;
	char dummy[BUFSIZE - 12];
};


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