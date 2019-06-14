#pragma once

//
// 애니메이션 속도, 스프라이트 크기,
// 현재 보여지는 스프라이트, 스프라이트 개수 등의 정보들 담는 클래스
//

class AnimationInfo
{
public:
	int ImageWidth; // 전체 이미지 파일의 가로 사이즈
	int ImageHeight; // 전체 이미지 파일의 세로 사이즈

	int unitSizeX; // 한번에 출력될 유닛 크기. 이미지 파일에서의 사이즈
	int unitSizeY;

	int currentFrame; // 가로 몇번째 이미지인지 좌표
	int totalFrameCount; // 가로 이미지의 총 개수. 열 개수

	int aniIndex; // 세로 몇번째 이미지인지 좌표
	int totalAniCount; // 세로 이미지의 총 개수. 행 개수

	float aniDuration; // 재생되고있을시간표시. 다음 애니메이션 까지 남은 시간이 됨
	float aniDelay; // 다음 애니메이션 까지의 지연시간. 재생시간 떨어지면 채워주게 됨


public:
	AnimationInfo();
	virtual ~AnimationInfo();

	// 프레임 갱신. 움직임이 있는 텍스쳐를 사용중일때만 쓰는편이 좋을것
	void Update(float dTime);

	// 이미지 내 출력될 범위 Rect 반환
	RECT GetSrcRect();
};