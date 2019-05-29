#include <DxLib.h>
#include "StageMng.h"


StageMng::StageMng()
{
	Init();
}


StageMng::~StageMng()
{
}

const VECTOR2 & StageMng::GetChipSize(void)
{
	return chipSize;
}

const VECTOR2 & StageMng::GetStageSize(void)
{
	return stageSize;
}

bool StageMng::Init(void)
{
	stageSize = VECTOR2(GAME_AREA_SIZE_X, GAME_AREA_SIZE_Y);
	chipSize = VECTOR2(CHIP_SIZE, CHIP_SIZE);
	return true;
}
