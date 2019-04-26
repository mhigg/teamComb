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

bool StageMng::SetUp(VECTOR2 chipSize, VECTOR2 drawOffset)
{
	this->chipSize = chipSize;

	auto CreateMap = [=](auto& base, auto& front, auto initNum) {
		base.resize(stageSize.x * stageSize.y);
		front.resize(stageSize.y);

		// mapData‚ÆmapData_Base‚Ì˜AŒ‹
		for (int x = 0; x < front.size(); x++)
		{
			// mapSize.x•ª‚ª‰½‰ñ’Ê‚Á‚½‚©
			front[x] = &base[stageSize.x * x];
		}
		// ˜AŒ‹‚Æ‰Šú‰»
		for (int j = 0; j < base.size(); j++)
		{
			// ‘S‘Ì‚ÉNON‚ ‚é‚¢‚Í0(¾ÞÛ)‚ð“ü‚ê‚é
			base[j] = initNum;
		}
	};

	CreateMap(mapData_Base, mapData, MAP_ID::NONE);

	return true;
}


void StageMng::MapSave(void)
{

}

void StageMng::MapLoad(sharedListObj objList, bool editFlag)
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
//	stageSize = { GAME_SCREEN_SIZE_X / 2 , GAME_SCREEN_SIZE_Y / 2 };
	return true;
}
