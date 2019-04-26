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

		// mapData��mapData_Base�̘A��
		for (int x = 0; x < front.size(); x++)
		{
			// mapSize.x��������ʂ�����
			front[x] = &base[stageSize.x * x];
		}
		// �A���Ə�����
		for (int j = 0; j < base.size(); j++)
		{
			// �S�̂�NON���邢��0(���)������
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
