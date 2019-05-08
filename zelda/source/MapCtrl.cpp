#include <DxLib.h>
#include <memory>
#include "ImageMng.h"
#include "MapCtrl.h"
#include "Player.h"
#include "SceneMng.h"
#include "StageMng.h"
#include "ClassObj.h"

struct DataHeader
{
	char fileID[15];	// ﾌｧｲﾙのID情報
	char verID;			// ﾊﾞｰｼﾞｮﾝ番号
	char reserve1[2];	// 予約領域
	int sizeX;			// ﾏｯﾌﾟのﾏｽﾒ数X
	int sizeY;			// ﾏｯﾌﾟのﾏｽﾒ数Y
	char reserve2[1];	// 予約領域
	char sum;			// ｻﾑ値
};

#define ZELDA_VER_ID 0x01						// ﾌｧｲﾙﾊﾞｰｼﾞｮﾝ番号
#define ZELDA_FILE_ID "ZELDA_MAP_DATA"			// ﾌｧｲﾙのID情報	


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

		// mapDataとmapData_Baseの連結
		for (int x = 0; x < front.size(); x++)
		{
			// mapSize.x分が何回通ったか
			front[x] = &base[stageSize.x * x];
		}
		// 連結と初期化
		for (int j = 0; j < base.size(); j++)
		{
			// 全体にNONあるいは0(ｾﾞﾛ)を入れる
			base[j] = initNum;
		}
	};

	CreateMap(mapData_Base, mapData, MAP_ID::NONE);

	return true;
}

bool MapCtrl::SetMapData(VECTOR2 pos, MAP_ID id)
{
	VECTOR2 mapPos(pos / chipSize);		// 自分自身
	if (!CheckSize()(mapPos, stageSize))
	{
		return false;
	}
	mapData[mapPos.y][mapPos.x] = id;
	return true;
}

MAP_ID MapCtrl::GetMapData(VECTOR2 pos, MAP_ID defID)
{
	VECTOR2 selPos(pos / chipSize);
	if (!CheckSize()(selPos, stageSize))
	{
		// 範囲外の時は固定のIDを返す
		return defID;
	}
	return mapData[selPos.y][selPos.x];
}

bool MapCtrl::MapSave(void)
{
	DataHeader expData = {
		ZELDA_FILE_ID,
		ZELDA_VER_ID,
		{ 0,0 },
		stageSize.x,
		stageSize.y,
		{ 0 },
		(char)0xff
	};
	int sum = 0;
	for (auto data : mapData_Base)
	{
		sum += (int)data;
	}
	expData.sum = (char)sum;

	FILE *file;
	fopen_s(&file, "data/mapdata.map", "wb");
	fwrite(&expData, sizeof(expData), 1, file);
	fwrite(mapData_Base.data(), sizeof(MAP_ID) * mapData_Base.size(), 1, file);
	fclose(file);
	return false;
}

bool MapCtrl::MapLoad(sharedListObj objList, bool editFlag)
{
	// ﾏｯﾌﾟﾃﾞｰﾀのﾛｰﾄﾞ
	FILE *file;
	DataHeader expData;
	fopen_s(&file, "data/mapdata.map", "rb");
	fread(&expData, sizeof(expData), 1, file);
	mapData_Base.resize(expData.sizeX * expData.sizeY);
	fread(mapData_Base.data(), sizeof(MAP_ID) * mapData_Base.size(), 1, file);
	fclose(file);
	bool flag = true;
	if ((std::string)expData.fileID != ZELDA_FILE_ID)
	{
		flag = false;
	}
	if (expData.verID != ZELDA_VER_ID)
	{
		flag = false;
	}
	int sum = 0;
	for (auto data : mapData_Base)
	{
		sum += static_cast<int>(data);
	}
	if ((char)sum != expData.sum)
	{
		flag = false;
	}
	if (!flag)
	{
		for (auto &data : mapData_Base)
		{
			data = MAP_ID::NONE;
		}
	}
	if (flag)
	{
		lpMapCtrl.SetUpGameObj(objList, editFlag);
	}
	return flag;

}


bool MapCtrl::SetUpGameObj(sharedListObj objList, bool modeFlag)
{
	if (modeFlag)
	{
		return false;
		// EditModeならこの先は処理しない
	}
	// GameModeならここから先へ

	int playerNum = GetJoypadNum();		// 接続してるﾌﾟﾚｲﾔｰの数
	int plCnt = 0;	// ｲﾝｽﾀﾝｽしたﾌﾟﾚｲﾔｰの数
	for (int y = 0; y < stageSize.y / chipSize.y; y++)
	{
		for (int x = 0; x < stageSize.x / chipSize.x; x++)
		{
			MAP_ID id = mapData[y][x];

			ListObj_itr obj;
			switch (id)
			{
			case MAP_ID::PLAYER:
				if ((plCnt >= playerNum) || (playerNum >= 4))
				{
					break;
				}
				// ﾌﾟﾚｲﾔｰをｲﾝｽﾀﾝｽ
				else
				{
					auto obj = AddObjList()(objList, 
						std::make_unique<Player>(static_cast<PL_NUMBER>(plCnt), chipSize * VECTOR2(x, y), drawOffset + VECTOR2(0, -20)));
					plCnt++;
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
	// ﾏｯﾌﾟ描画
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
				// ｴﾗｰ表示
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
