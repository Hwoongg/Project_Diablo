#pragma once

//
// ������ Ŭ���̾�Ʈ �� �����Ǵ� ��� �޽���
//

#define BUFSIZE     256                    // ���� �޽��� ��ü ũ��
#define MSGSIZE     (BUFSIZE-sizeof(int))  // ä�� �޽��� �ִ� ����. ���� ������ - Ÿ�Ժ��� ũ��

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