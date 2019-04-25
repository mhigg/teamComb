#include <memory>
#include <DxLib.h>
#include "StageMng.h"
#include "MapCtrl.h"
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

void StageMng::MapDraw(void)
{
	ClsDrawScreen();
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			DrawLine(
				i * stageSize.x, 
				j * stageSize.y, 
				i * stageSize.x, 
				j * stageSize.y, 
				lineColor, true);
		}
	}
	ScreenFlip();
}

bool StageMng::Init(void)
{
	mapCtrl = std::make_unique<MapCtrl>();
	lineColor = RGB(255, 255, 255);
	stageSize = { GAME_SCREEN_SIZE_X / 2 , GAME_SCREEN_SIZE_Y / 2 };
	return true;
}
