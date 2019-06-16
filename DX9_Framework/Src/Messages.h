#pragma once

//
// ������ Ŭ���̾�Ʈ �� �����Ǵ� ��� �޽���
//

#define BUFSIZE     256                    // ���� �޽��� ��ü ũ��
#define MSGSIZE     (BUFSIZE-sizeof(int))  // ä�� �޽��� �ִ� ����. ���� ������ - Ÿ�Ժ��� ũ��

#define PLAYERKEY 1000
#define MEMLIST 1001
#define ADDMEMBER 1002
#define MOVING 1003


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

// ��� ����Ʈ ��û �޽���.
struct ReqMemList_MSG
{
	int type;
	char dummy[BUFSIZE - 4];
};

// ���� �ʵ� ��Ȳ �ڷᱸ��. �޽����ε� Ȱ��
struct FieldState
{
	int type;
	int Objects;
	char dummy[BUFSIZE - 8];
};

struct FieldObject
{
	int Key;
	float xPos;
	float yPos;

};