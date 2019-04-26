#include <DxLib.h>
#include <memory>
#include "MapCtrl.h"
#include "Player.h"
#include "SceneMng.h"
#include "StageMng.h"
#include "ClassObj.h"


MapCtrl::MapCtrl()
{
	lineColor = RGB(255, 255, 255);
}

MapCtrl::MapCtrl(VECTOR2 stageSize, VECTOR2 chipSize, VECTOR2 drawOffset):drawOffset(drawOffset)
{
	lineColor = RGB(255, 255, 255);
}

MapCtrl::~MapCtrl()
{
}


bool MapCtrl::SetMapData(VECTOR2 mapPos, MAP_ID id)
{
	return true;
}

MAP_ID MapCtrl::GetMapData(VECTOR2 mapPos)
{
	return mapData[mapPos.x][mapPos.y];
}

bool MapCtrl::SetUpGameObj(sharedListObj objList, bool modeFlag)
{
	if (modeFlag)
	{
		return false;
		// EditModeÇ»ÇÁÇ±ÇÃêÊÇÕèàóùÇµÇ»Ç¢
	}
	// GameModeÇ»ÇÁÇ±Ç±Ç©ÇÁêÊÇ÷

	bool makePlayerFlag = false;
	for (int y = 0; y < stageSize.y; y++)
	{
		for (int x = 0; x < stageSize.x; x++)
		{
			MAP_ID id = mapData[y][x];
			ListObj_itr obj;
			switch (id)
			{
			case MAP_ID::PLAYER:
				if (makePlayerFlag)
				{
					break;
				}
				// Ãﬂ⁄≤‘∞Ç≤›Ω¿›Ω
				{
					obj = AddObjList()(objList, std::make_unique<Player>(chipSize * VECTOR2(x, y), drawOffset + VECTOR2(0, -20)));
					makePlayerFlag = true;
				}
				break;
			case MAP_ID::NONE:

			default:
				break;
			}
		}
	}

	return true;
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
