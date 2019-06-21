#pragma once

//
// 서버와 클라이언트 간 공유되는 통신 메시지
//

#define BUFSIZE     256                    // 전송 메시지 전체 크기
#define MSGSIZE     (BUFSIZE-sizeof(int))  // 버퍼 사이즈 - 타입변수 크기. 타입을 제외한 최대 길이.

#define ADDMEMBER 1000
#define PLAYERKEY 1001
#define MEMLIST 1002
#define MOVING 1004
#define LIST_OK 1005


// 공통 메시지 형식
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

// 현재 필드 상황 자료구조.
// Type을 추가하여 메시지로도 활용중
struct FieldState
{
	int type; // Message Type...
	int ObjAmount;
	FieldObject fieldObjects[20]; // 현 구조상 한번에 20개를 보낼 수 있다.
	char dummy[8]; // 8byte 남았음.
};

struct ADDMEMBER_MSG
{
	int type; // = ADDMEMBER
	FieldObject AddObj;
	char dummy[BUFSIZE - 16];
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
	FieldObject MoveObj;
	char dummy[BUFSIZE - 16];
};
