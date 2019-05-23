#pragma once

//
// �ִϸ��̼� �ӵ�, ��������Ʈ ũ��,
// ���� �������� ��������Ʈ, ��������Ʈ ���� ���� ������ ��� Ŭ����
//

class AnimationInfo
{
public:
	int ImageWidth; // ��ü �̹��� ������ ���� ������
	int ImageHeight; // ��ü �̹��� ������ ���� ������

	int unitSizeX; // �ѹ��� ��µ� ���� ũ��. �̹��� ���Ͽ����� ������
	int unitSizeY;

	int currentFrame; // ���� ���° �̹������� ��ǥ
	int totalFrameCount; // ���� �̹����� �� ����. �� ����

	int aniIndex; // ���� ���° �̹������� ��ǥ
	int totalAniCount; // ���� �̹����� �� ����. �� ����

	float aniDuration; // ����ǰ������ð�ǥ��. ���� �ִϸ��̼� ���� ���� �ð��� ��
	float aniDelay; // ���� �ִϸ��̼� ������ �����ð�. ����ð� �������� ä���ְ� ��


public:
	AnimationInfo();
	virtual ~AnimationInfo();

	// ������ ����. �������� �ִ� �ؽ��ĸ� ������϶��� �������� ������
	void Update(float dTime);

	// �̹��� �� ��µ� ���� Rect ��ȯ
	RECT GetSrcRect();
};