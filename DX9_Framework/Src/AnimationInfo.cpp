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
	if (aniDuration < 0) // ���ӽð� ������
	{
		aniDuration += aniDelay; // ���ӽð� ä���ְ�
		currentFrame++; // ���� �ִϸ��̼����� Ŀ�� �̵�
		if (currentFrame >= totalFrameCount) // ������ �ִϸ��̼� �̶��
			currentFrame = 0; // Ŀ���� ó������
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
