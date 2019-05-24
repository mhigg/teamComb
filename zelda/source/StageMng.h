// ��޼ު�Ă̲ݽ�ݽ�Eϯ�߂�۰�ނȂǁAMapCtrl�����Ƃ�ϯ�ߏ����Ǘ��E���p����

#pragma once
#include <memory>
#include <vector>
#include "MapCtrl.h"
#include "MAP_ID.h"
#include "VECTOR2.h"

#define lpStageMng StageMng::GetInstance()

constexpr int GAME_AREA_SIZE_X = 3200;		// ϯ�ߑS�̻̂���
constexpr int GAME_AREA_SIZE_Y = 1920;

constexpr int SCROLL_AREA_X = 320;		// ��۰يJ�n�_X
constexpr int SCROLL_AREA_Y = 200;		// ��۰يJ�n�_Y
constexpr int SCROLL_END_X = GAME_AREA_SIZE_X - 320;		// ��۰ُI���_X
constexpr int SCROLL_END_Y = GAME_AREA_SIZE_Y - 280;		// ��۰ُI���_Y
constexpr int SCROLL_AREA_SIZE_X = SCROLL_END_X - SCROLL_AREA_X;		// ��۰͈ٔ�X
constexpr int SCROLL_AREA_SIZE_Y = SCROLL_END_Y - SCROLL_AREA_Y;		// ��۰͈ٔ�Y


class StageMng
{
public:
	static StageMng & GetInstance(void)
	{
		static StageMng s_instance;
		return s_instance;
	}

	const VECTOR2& GetChipSize(void);		// ChipSize�̎擾
	const VECTOR2& GetStageSize(void);		// StageSize�̎擾
	const VECTOR2& GetDrawOffset(void);	// drawOffset�̎擾


private:
	StageMng();
	~StageMng();

	bool Init(void);

	VECTOR2 stageSize;	// �ð�޻���
	VECTOR2 mapSize;	// Ͻ�̐�
	VECTOR2 chipSize;		// 1Ͻ�̻���
	VECTOR2 drawOffset;
};

