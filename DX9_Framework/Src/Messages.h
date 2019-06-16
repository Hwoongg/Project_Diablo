#pragma once

//
// 서버와 클라이언트 간 공유되는 통신 메시지
//

#define BUFSIZE     256                    // 전송 메시지 전체 크기
#define MSGSIZE     (BUFSIZE-sizeof(int))  // 채팅 메시지 최대 길이. 버퍼 사이즈 - 타입변수 크기

#define PLAYERKEY 1000
#define MEMLIST 1001
#define ADDMEMBER 1002
#define MOVING 1003


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

// 멤버 리스트 요청 메시지.
struct ReqMemList_MSG
{
	int type;
	char dummy[BUFSIZE - 4];
};

// 현재 필드 상황 자료구조. 메시지로도 활용
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