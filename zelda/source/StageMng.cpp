#include <memory>
#include <DxLib.h>
#include "StageMng.h"
#include "BaseScene.h"

StageMng::StageMng()
{
	Init();
}


StageMng::~StageMng()
{
}

void StageMng::MapSave(void)
{

}

void StageMng::MapLoad(void)
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

std::vector<MAP_ID> StageMng::GetMap(void)
{
	return mapData;
}

bool StageMng::Init(void)
{
	stageSize = { GAME_SCREEN_SIZE_X / 2 , GAME_SCREEN_SIZE_Y / 2 };
	return true;
}
