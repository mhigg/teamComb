#include <DxLib.h>
#include "MapCtrl.h"
#include "StageMng.h"



MapCtrl::MapCtrl()
{
	lineColor = RGB(255, 255, 255);
}


MapCtrl::~MapCtrl()
{
}

bool MapCtrl::SetUp(VECTOR2 stageSize, VECTOR2 chipSize)
{
	lpStageMng.GetStageSize();
	return false;
}

bool MapCtrl::SetMapData(VECTOR2 mapPos, MAP_ID id)
{
	return false;
}

MAP_ID MapCtrl::GetMapData(VECTOR2 mapPos)
{
	return MAP_ID::NONE/*stageMap[mapPos.x][mapPos.y]*/;
}

void MapCtrl::MapDraw(void)
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
