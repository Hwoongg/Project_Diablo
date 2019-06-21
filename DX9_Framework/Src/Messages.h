#pragma once

//
// ������ Ŭ���̾�Ʈ �� �����Ǵ� ��� �޽���
//

#define BUFSIZE     256                    // ���� �޽��� ��ü ũ��
#define MSGSIZE     (BUFSIZE-sizeof(int))  // ���� ������ - Ÿ�Ժ��� ũ��. Ÿ���� ������ �ִ� ����.

#define ADDMEMBER 1000
#define PLAYERKEY 1001
#define MEMLIST 1002
#define MOVING 1004
#define LIST_OK 1005


// ���� �޽��� ����
// sizeof(COMM_MSG) == 256
struct COMM_MSG
{
	int  type;
	char dummy[MSGSIZE];
};

struct FieldObject // 12byte
{
	int Key;
	float xPos;
	float yPos;
};

// ���� �ʵ� ��Ȳ �ڷᱸ��.
// Type�� �߰��Ͽ� �޽����ε� Ȱ����
struct FieldState
{
	int type; // Message Type...
	int ObjAmount;
	FieldObject fieldObjects[20]; // �� ������ �ѹ��� 20���� ���� �� �ִ�.
	char dummy[8]; // 8byte ������.
};

struct ADDMEMBER_MSG
{
	int type; // = ADDMEMBER
	FieldObject AddObj;
	char dummy[BUFSIZE - 16];
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
	FieldObject MoveObj;
	char dummy[BUFSIZE - 16];
};
