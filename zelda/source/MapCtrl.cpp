#include <DxLib.h>
#include <memory>
#include "ImageMng.h"
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

struct CheckSize
{
	bool operator()(const VECTOR2 &selPos, const VECTOR2 &mapSize) {
		if ((selPos.x < 0 || selPos.y < 0)
			|| (mapSize.x <= selPos.x)
			|| (mapSize.y <= selPos.y))
		{
			return false;
		}
		return true;
	}
};


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

bool MapCtrl::SetMapData(VECTOR2 pos, MAP_ID id)
{
	VECTOR2 mapPos(pos / chipSize);		// �������g
	if (!CheckSize()(mapPos, stageSize))
	{
		return false;
	}
	mapData[mapPos.y][mapPos.x] = id;
	return true;
}

MAP_ID MapCtrl::GetMapData(VECTOR2 pos,MAP_ID defID)
{
	VECTOR2 selPos(pos / chipSize);
	if (!CheckSize()(selPos, stageSize))
	{
		// �͈͊O�̎��͌Œ��ID��Ԃ�
		return defID;
	}
	return mapData[selPos.y][selPos.x];
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
	for (int y = 0; y < stageSize.y / chipSize.y; y++)
	{
		for (int x = 0; x < stageSize.x / chipSize.x; x++)
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
				// ��ڲ԰��ݽ�ݽ
				{
					auto obj = AddObjList()(objList, 
						std::make_unique<Player>(chipSize * VECTOR2(x, y), drawOffset + VECTOR2(0, -20)));
					makePlayerFlag = true;
				}
				break;
			case MAP_ID::NONE:
			case MAP_ID::WALL1:
			case MAP_ID::WALL2:
			case MAP_ID::WALL3:
			case MAP_ID::WALL4:
			case MAP_ID::WALL5:
			case MAP_ID::WALL6:
			case MAP_ID::WALL7:
			case MAP_ID::WALL8:
			case MAP_ID::WALL9:
			case MAP_ID::DOOR1:
			case MAP_ID::DOOR2:
			case MAP_ID::DOOR3:
			case MAP_ID::DOOR4:
			case MAP_ID::KEY:
			case MAP_ID::PANEL:
			case MAP_ID::LADDER:
			case MAP_ID::FLAG:
			case MAP_ID::FIRE1:
			case MAP_ID::FIRE2:
			case MAP_ID::RAMP1:
			case MAP_ID::RAMP2:
			case MAP_ID::POTION1:
			case MAP_ID::POTION2:
			case MAP_ID::BARREL1:
			case MAP_ID::BARREL2:
			case MAP_ID::BONE1:
			case MAP_ID::BONE2:
			case MAP_ID::BONE3:
				SetMapData(VECTOR2(x * chipSize.x, y * chipSize.y),id);
			default:
				break;
			}
		}
	}
	return true;
}

void MapCtrl::Draw(bool flag)
{
	// ϯ�ߕ`��
	MAP_ID mapID;
	VECTOR2 offset(lpSceneMng.GetDrawOffset());
	VECTOR2 tmpPos;
	for (int y = 0; y < stageSize.y; y++)
	{
		for (int x = 0; x < stageSize.x; x++)
		{
			MAP_ID id = mapData[y][x];

			tmpPos = { (x * chipSize.x),(y * chipSize.y) };
			switch (id)
			{
			case MAP_ID::NONE:
				break;
			case MAP_ID::PLAYER:
				if (!flag)
				{
					break;
				}
			case MAP_ID::WALL1:
			case MAP_ID::WALL2:
			case MAP_ID::WALL3:
			case MAP_ID::WALL4:
			case MAP_ID::WALL5:
			case MAP_ID::WALL6:
			case MAP_ID::WALL7:
			case MAP_ID::WALL8:
			case MAP_ID::WALL9:
			case MAP_ID::DOOR1:
			case MAP_ID::DOOR2:
			case MAP_ID::DOOR3:
			case MAP_ID::DOOR4:
			case MAP_ID::KEY:
			case MAP_ID::PANEL:
			case MAP_ID::LADDER:
			case MAP_ID::FLAG:
			case MAP_ID::FIRE1:
			case MAP_ID::FIRE2:
			case MAP_ID::RAMP1:
			case MAP_ID::RAMP2:
			case MAP_ID::POTION1:
			case MAP_ID::POTION2:
			case MAP_ID::BARREL1:
			case MAP_ID::BARREL2:
			case MAP_ID::BONE1:
			case MAP_ID::BONE2:
			case MAP_ID::BONE3:
				DrawGraph(
					tmpPos.x + offset.x,
					tmpPos.y + offset.y,
					IMAGE_ID("image/mapImage.png")[static_cast<const unsigned int>(id)],
					true);
				break;
			default:
			case MAP_ID::FLOOR1:
			case MAP_ID::FLOOR2:
#ifdef _DEBUG
				// �װ�\��
				DrawGraph(
					tmpPos.x + offset.x,
					tmpPos.y + offset.y,
					IMAGE_ID("image/mapImage.png")[static_cast<int>(MAP_ID::NONE)],
					true);
#endif
				break;
			}
		}
	}
}
