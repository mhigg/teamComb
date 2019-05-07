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



void StageMng::MapSave(void)
{

}

void StageMng::MapLoad(sharedListObj objList, bool editFlag)
{
	// Ï¯ÌßÃÞ°À‚ÌÛ°ÄÞ

	lpMapCtrl.SetUpGameObj(objList, editFlag);
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
//	stageSize = { GAME_SCREEN_SIZE_X / 2 , GAME_SCREEN_SIZE_Y / 2 };
	return true;
}
