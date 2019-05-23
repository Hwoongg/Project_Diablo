#include "_StdAfx.h"

AnimationInfo::AnimationInfo()
{
	ImageWidth = 0;
}

AnimationInfo::~AnimationInfo()
{
}

void AnimationInfo::Update(float dTime)
{
	aniDuration -= dTime;
	if (aniDuration < 0) // 지속시간 끝나면
	{
		aniDuration += aniDelay; // 지속시간 채워주고
		currentFrame++; // 다음 애니메이션으로 커서 이동
		if (currentFrame >= totalFrameCount) // 마지막 애니메이션 이라면
			currentFrame = 0; // 커서를 처음으로
	}
}

RECT AnimationInfo::GetSrcRect()
{
	RECT drawRt;

	drawRt.left = currentFrame*unitSizeX;
	drawRt.top = aniIndex*unitSizeY;
	drawRt.right = drawRt.left + unitSizeX;
	drawRt.bottom = drawRt.top + unitSizeY;

	return drawRt;
}
