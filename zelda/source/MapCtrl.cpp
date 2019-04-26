#include <DxLib.h>
#include <memory>
#include "MapCtrl.h"
#include "Player.h"
#include "StageMng.h"
#include "ClassObj.h"


MapCtrl::MapCtrl()
{
}


MapCtrl::~MapCtrl()
{
}

bool MapCtrl::SetUp(VECTOR2 stageSize, VECTOR2 chipSize, VECTOR2 drawOffset)
{
	this->stageSize = stageSize;
	this->chipSize = chipSize;
	this->drawOffset = drawOffset;

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

//	mapData_Base = lpStageMng.GetMap();
	lineColor = RGB(255, 255, 255);

	return true;
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
		// EditMode‚È‚ç‚±‚Ìæ‚Íˆ—‚µ‚È‚¢
	}
	// GameMode‚È‚ç‚±‚±‚©‚çæ‚Ö

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
				// ÌßÚ²Ô°‚ð²Ý½ÀÝ½
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
