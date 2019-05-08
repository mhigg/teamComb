#include <memory>
#include <DxLib.h>
#include "StageMng.h"
#include "BaseScene.h"
#include "MapCtrl.h"


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

const VECTOR2 & StageMng::GetDrawOffset(void)
{
	return drawOffset;
}

bool StageMng::Init(void)
{
	stageSize = VECTOR2(GAME_AREA_SIZE_X, GAME_AREA_SIZE_Y);
	chipSize = VECTOR2(CHIP_SIZE,CHIP_SIZE);
	mapSize = stageSize / chipSize;
	return true;
}
