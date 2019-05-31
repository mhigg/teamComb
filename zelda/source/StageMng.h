// ��޼ު�Ă̲ݽ�ݽ�Eϯ�߂�۰�ނȂǁAMapCtrl�����Ƃ�ϯ�ߏ����Ǘ��E���p����

#pragma once
#include <memory>
#include <array>
#include "VECTOR2.h"

enum VALUE_TYPE {
	VALUE_UPPER_L,	// �J�n�_
	VALUE_LOWER_R,	// �I���_
	VALUE_AREA,		// ��۰͈ٔ�
	VALUE_MAX
};

#define lpStageMng StageMng::GetInstance()

constexpr int GAME_AREA_SIZE_X = 3200;		// ϯ�ߑS�̻̂���
constexpr int GAME_AREA_SIZE_Y = 1920;

//constexpr int SCROLL_AREA_X = 320/*800*/;		// ��۰يJ�n�_X
//constexpr int SCROLL_AREA_Y = 200/*480*/;		// ��۰يJ�n�_Y
//constexpr int SCROLL_END_X = GAME_AREA_SIZE_X - 480/*800*/;		// ��۰ُI���_X
//constexpr int SCROLL_END_Y = GAME_AREA_SIZE_Y - 280/*480*/;		// ��۰ُI���_Y
//constexpr int SCROLL_AREA_SIZE_X = SCROLL_END_X - SCROLL_AREA_X;		// ��۰͈ٔ�X
//constexpr int SCROLL_AREA_SIZE_Y = SCROLL_END_Y - SCROLL_AREA_Y;		// ��۰͈ٔ�Y

constexpr int CHIP_SIZE = 40;				// 1Ͻ�̒���


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
	const VECTOR2& GetScrollValue(VALUE_TYPE type, bool singleFlag);

private:
	StageMng();
	~StageMng();

	bool Init(void);

	std::array<std::array<VECTOR2, 2>, (VALUE_MAX - 1)> scrollTbl;		// ��۰يJ�n�_�ƏI���_
	VECTOR2 stageSize;		// �ð�޻���
	VECTOR2 chipSize;		// 1Ͻ�̻���
};

