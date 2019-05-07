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
	stageSize = lpStageMng.GetStageSize();
	chipSize = lpStageMng.GetChipSize();
	drawOffset = lpSceneMng.GetDrawOffset();
}


MapCtrl::~MapCtrl()
{
}

bool MapCtrl::SetUp(VECTOR2 chipSize, VECTOR2 drawOffset)
{
	MapCtrl::chipSize = chipSize;
	MapCtrl::drawOffset = drawOffset;

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

struct CheckSize
{
	// �͈�����
	bool operator()(const VECTOR2 &mapPos, const VECTOR2 &mapSize) {
		if ((mapPos.x < 0) || (mapPos.y < 0)
			|| (mapPos.x >= mapSize.x) || (mapPos.y >= mapSize.y))
		{
			return false;
		}
		return true;
	}
};

bool MapCtrl::SetMapData(VECTOR2 pos, MAP_ID id)
{
	VECTOR2 mapPos(pos / chipSize);		// �������g
	if (!CheckSize()(mapPos, stageSize))
	{
		return false;
	}

	mapData[mapPos.x][mapPos.y] = id;
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
		// EditMode�Ȃ炱�̐�͏������Ȃ�
	}
	// GameMode�Ȃ炱��������

	bool makePlayerFlag = false;
	for (int y = 0; y < stageSize.y; y++)
	{
		for (int x = 0; x < stageSize.x; x++)
		{
			MAP_ID id = mapData[y][x];
			switch (id)
			{
			case MAP_ID::PLAYER:
				if (makePlayerFlag)
				{
					break;
				}
				// ��ڲ԰��ݽ�ݽ
				{
					auto obj = AddObjList()(objList, std::make_unique<Player>(chipSize * VECTOR2(x, y), drawOffset + VECTOR2(0, -20)));
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

void MapCtrl::Draw(bool flag)
{
	if (!flag)
	{
		return;
	}
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
}
