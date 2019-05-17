#include <algorithm>
#include <DxLib.h>
#include <memory>
#include "ImageMng.h"
#include "InfoCtrl.h"
#include "MapCtrl.h"
//#include "Player.h"
#include "Enemy.h"
#include "SceneMng.h"
#include "StageMng.h"
#include "ScoreBoard.h"
#include "ClassObj.h"

struct DataHeader
{
	char fileID[15];		// ﾌｧｲﾙのID情報
	char verID;			// ﾊﾞｰｼﾞｮﾝ番号
	char reserve1[2];	// 予約領域
	int sizeX;				// ﾏｯﾌﾟのﾏｽﾒ数X
	int sizeY;				// ﾏｯﾌﾟのﾏｽﾒ数Y
	char reserve2[1];	// 予約領域
	char sum;				// ｻﾑ値
};

#define ZELDA_VER_ID 0x02						// ﾌｧｲﾙﾊﾞｰｼﾞｮﾝ番号
#define ZELDA_FILE_ID "ZELDA_MAP_DATA"			// ﾌｧｲﾙのID情報	


MapCtrl::MapCtrl()
{
	lineColor = RGB(255, 255, 255);
	chipSize = lpStageMng.GetChipSize();
	stageSize = lpStageMng.GetStageSize() / chipSize;
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
	lpImageMng.GetID("image/mapImage.png", VECTOR2(40, 40), VECTOR2(8, 10));

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
	CreateMap(itemData_Base, itemData, MAP_ID::NONE);
	
	VECTOR2 plScrSize = lpSceneMng.GetPlayScreen();

	plScrTbl = {
		VECTOR2(0,0),
		VECTOR2(plScrSize.x, 0),
		VECTOR2(0, plScrSize.y),
		plScrSize
	};

	scrollTbl.resize(1);

	return true;
}

bool MapCtrl::SetMapData(const VECTOR2 & pos, MAP_ID id)
{
	return SetData(mapData, pos, id);
}

bool MapCtrl::SetItemData(const VECTOR2 & pos, MAP_ID id)
{
	return SetData(itemData, pos, id);
}

MAP_ID MapCtrl::GetMapData(const VECTOR2& pos)
{
	return GetData(mapData, pos, MAP_ID::WALL2);
}

MAP_ID MapCtrl::GetItemData(const VECTOR2 & pos)
{
	return GetData(itemData, pos, MAP_ID::NONE);
}

template<typename mapType, typename idType>
bool MapCtrl::SetData(mapType maps, const VECTOR2 & pos, idType id)
{
	VECTOR2 selPos(pos / chipSize);
	if (!CheckSize()(selPos, stageSize))
	{
		return false;
	}
	maps[selPos.y][selPos.x] = id;
	return true;
}

template <typename mapType, typename idType>
idType MapCtrl::GetData(mapType maps, const VECTOR2 & pos, idType defID)
{
	VECTOR2 selPos(pos / chipSize);
	if (!CheckSize()(selPos, stageSize))
	{
		// 範囲外の時は固定のIDを返す
		return defID;
	}
	return maps[selPos.y][selPos.x];
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
	scrollTbl.resize(playerNum);
	int plCnt = 0;	// ｲﾝｽﾀﾝｽしたﾌﾟﾚｲﾔｰの数
	for (int y = 0; y < stageSize.y; y++)
	{
		for (int x = 0; x < stageSize.x; x++)
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
						std::make_unique<Player>
						(static_cast<PL_NUMBER>(plCnt), chipSize * VECTOR2(x, y), drawOffset + plScrTbl[plCnt] + VECTOR2(-20, -90)));
					plCnt++;
				}
				SetData(mapData, VECTOR2(x * chipSize.x, y * chipSize.y), MAP_ID::WALL39);
				break;
			case MAP_ID::ENEMY:
				if (1)
				{
					int num = GetRand(static_cast<int>(ENEMY::ENEMY_MAX) - 1);
				// ｴﾈﾐｰのｲﾝｽﾀﾝｽ
				/* ﾃｽﾄ*/	auto obj = AddObjList()(objList,
						std::make_unique<Enemy>
						(num, chipSize * VECTOR2(x, y) - VECTOR2(20,20), drawOffset + VECTOR2(-20,-90)));
				}
				SetData(mapData, VECTOR2(x * chipSize.x, y * chipSize.y), MAP_ID::WALL39);
				break;
			case MAP_ID::POTION_1:
			case MAP_ID::POTION_2:
			case MAP_ID::POTION_3:
			case MAP_ID::POTION_4:
			case MAP_ID::COIN_1:
			case MAP_ID::COIN_2:
			case MAP_ID::COIN_3:
			case MAP_ID::COIN_4:
			case MAP_ID::KEY_1:
			case MAP_ID::KEY_2:
			case MAP_ID::MEAT:
			case MAP_ID::SWORD:
			case MAP_ID::SHIELD:
			case MAP_ID::BOOK:
			case MAP_ID::GOLD:
			case MAP_ID::DIA:
				SetData(itemData, VECTOR2(x * chipSize.x, y * chipSize.y), id);
				SetData(mapData, VECTOR2(x * chipSize.x, y * chipSize.y), MAP_ID::WALL39);
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
			case MAP_ID::WALL10:
			case MAP_ID::WALL11:
			case MAP_ID::WALL12:
			case MAP_ID::WALL13:
			case MAP_ID::WALL14:
			case MAP_ID::WALL15:
			case MAP_ID::WALL16:
			case MAP_ID::WALL17:
			case MAP_ID::WALL18:
			case MAP_ID::WALL19:
			case MAP_ID::WALL20:
			case MAP_ID::WALL21:
			case MAP_ID::WALL22:
			case MAP_ID::WALL23:
			case MAP_ID::WALL24:
			case MAP_ID::WALL25:
			case MAP_ID::WALL26:
			case MAP_ID::WALL27:
			case MAP_ID::WALL28:
			case MAP_ID::WALL29:
			case MAP_ID::WALL30:
			case MAP_ID::WALL31:
			case MAP_ID::WALL32:
			case MAP_ID::WALL33:
			case MAP_ID::WALL34:
			case MAP_ID::WALL35:
			case MAP_ID::WALL36:
			case MAP_ID::WALL37:
			case MAP_ID::WALL38:
			case MAP_ID::WALL39:
			case MAP_ID::DOOR1:
			case MAP_ID::DOOR2:
			case MAP_ID::DOOR3:
			case MAP_ID::DOOR4:
			case MAP_ID::BOX_1:
			case MAP_ID::BOX_2:
			case MAP_ID::MOTH_1:
			case MAP_ID::MOTH_2:
			case MAP_ID::MOTH_3:
			case MAP_ID::MOTH_4:
			case MAP_ID::TREE_1:
			case MAP_ID::TREE_2:
			case MAP_ID::TREE_3:
			case MAP_ID::TREE_4:
			case MAP_ID::HOLL_1:
			case MAP_ID::HOLL_2:
			case MAP_ID::HOLL_3:
			case MAP_ID::HOLL_4:
			case MAP_ID::STONE_1:
			case MAP_ID::STONE_2:
			case MAP_ID::STONE_3:
			case MAP_ID::STONE_4:
				SetData(itemData, VECTOR2(x * chipSize.x, y * chipSize.y), MAP_ID::NONE);
				break;
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
	VECTOR2 plScrSize(lpSceneMng.GetPlayScreen() / chipSize);		// 分割1画面のｻｲｽﾞ
	VECTOR2 tmpPos;

	if (flag)
	{
		plScrSize = stageSize;
	}

	// ↓描画処理の重さの軽減のため
	// x,yの初期値を各分割画面の左上にする
	// ﾌﾟﾚｲﾔｰの座標 - VECTOR2(320, 200)
	// for第二引数は、plScrSize未満の間

	for (int pIdx = 0; pIdx < scrollTbl.size(); pIdx++)
	{
		VECTOR2 XYoffset = scrollTbl[pIdx] / chipSize;

		if (flag)
		{
			XYoffset = { 0,0 };
		}

		for (int y = XYoffset.y; y < XYoffset.y + plScrSize.y; y++)
		{
			for (int x = XYoffset.x; x < XYoffset.x + plScrSize.x; x++)
			{
				MAP_ID id = mapData[y][x];

				tmpPos = { (x * chipSize.x),(y * chipSize.y) };
				switch (id)
				{
				case MAP_ID::NONE:
					break;
				case MAP_ID::PLAYER:
				case MAP_ID::ENEMY:
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
				case MAP_ID::WALL10:
				case MAP_ID::WALL11:
				case MAP_ID::WALL12:
				case MAP_ID::WALL13:
				case MAP_ID::WALL14:
				case MAP_ID::WALL15:
				case MAP_ID::WALL16:
				case MAP_ID::WALL17:
				case MAP_ID::WALL18:
				case MAP_ID::WALL19:
				case MAP_ID::WALL20:
				case MAP_ID::WALL21:
				case MAP_ID::WALL22:
				case MAP_ID::WALL23:
				case MAP_ID::WALL24:
				case MAP_ID::WALL25:
				case MAP_ID::WALL26:
				case MAP_ID::WALL27:
				case MAP_ID::WALL28:
				case MAP_ID::WALL29:
				case MAP_ID::WALL30:
				case MAP_ID::WALL31:
				case MAP_ID::WALL32:
				case MAP_ID::WALL33:
				case MAP_ID::WALL34:
				case MAP_ID::WALL35:
				case MAP_ID::WALL36:
				case MAP_ID::WALL37:
				case MAP_ID::WALL38:
				case MAP_ID::WALL39:
				case MAP_ID::DOOR1:
				case MAP_ID::DOOR2:
				case MAP_ID::DOOR3:
				case MAP_ID::DOOR4:
				case MAP_ID::BOX_1:
				case MAP_ID::BOX_2:
				case MAP_ID::MOTH_1:
				case MAP_ID::MOTH_2:
				case MAP_ID::MOTH_3:
				case MAP_ID::MOTH_4:
				case MAP_ID::TREE_1:
				case MAP_ID::TREE_2:
				case MAP_ID::TREE_3:
				case MAP_ID::TREE_4:
				case MAP_ID::HOLL_1:
				case MAP_ID::HOLL_2:
				case MAP_ID::HOLL_3:
				case MAP_ID::HOLL_4:
				case MAP_ID::STONE_1:
				case MAP_ID::STONE_2:
				case MAP_ID::STONE_3:
				case MAP_ID::STONE_4:
				case MAP_ID::POTION_1:
				case MAP_ID::POTION_2:
				case MAP_ID::POTION_3:
				case MAP_ID::POTION_4:
				case MAP_ID::COIN_1:
				case MAP_ID::COIN_2:
				case MAP_ID::COIN_3:
				case MAP_ID::COIN_4:
				case MAP_ID::KEY_1:
				case MAP_ID::KEY_2:
				case MAP_ID::MEAT:
				case MAP_ID::SWORD:
				case MAP_ID::SHIELD:
				case MAP_ID::BOOK:
				case MAP_ID::GOLD:
				case MAP_ID::DIA:
					DrawGraph(
						tmpPos.x + offset.x + plScrTbl[pIdx].x - scrollTbl[pIdx].x,
						tmpPos.y + offset.y + plScrTbl[pIdx].y - scrollTbl[pIdx].y,
						IMAGE_ID("image/mapImage.png")[static_cast<const unsigned int>(id)],
						true);
					break;
				default:
#ifdef _DEBUG
					// ｴﾗｰ表示
					DrawGraph(
						tmpPos.x + offset.x + plScrTbl[pIdx].x - scrollTbl[pIdx].x,
						tmpPos.y + offset.y + plScrTbl[pIdx].y - scrollTbl[pIdx].y,
						IMAGE_ID("image/mapImage.png")[static_cast<int>(MAP_ID::NONE)],
						true);
#endif
					break;
				}
			}
		}
	}
	ItemDraw(offset);
}

void MapCtrl::ItemDraw(VECTOR2 offset)
{
	VECTOR2 tmpPos;
	for (int pIdx = 0; pIdx < scrollTbl.size(); pIdx++)
	{
		for (int y = 0; y < stageSize.y; y++)
		{
			for (int x = 0; x < stageSize.x; x++)
			{
				MAP_ID id = itemData[y][x];

				tmpPos = { (x * chipSize.x),(y * chipSize.y) };
				switch (id)
				{
				case MAP_ID::POTION_1:
				case MAP_ID::POTION_2:
				case MAP_ID::POTION_3:
				case MAP_ID::POTION_4:
				case MAP_ID::COIN_1:
				case MAP_ID::COIN_2:
				case MAP_ID::COIN_3:
				case MAP_ID::COIN_4:
				case MAP_ID::KEY_1:
				case MAP_ID::KEY_2:
				case MAP_ID::MEAT:
				case MAP_ID::SWORD:
				case MAP_ID::SHIELD:
				case MAP_ID::BOOK:
				case MAP_ID::GOLD:
				case MAP_ID::DIA:
					DrawGraph(
						tmpPos.x + offset.x + plScrTbl[pIdx].x - scrollTbl[pIdx].x,
						tmpPos.y + offset.y + plScrTbl[pIdx].y - scrollTbl[pIdx].y,
						IMAGE_ID("image/mapImage.png")[static_cast<const unsigned int>(id)],
						true
					);
					//DrawGraph(
					//	tmpPos.x + offset.x - scrollOffset.x,
					//	tmpPos.y + offset.y - scrollOffset.y,
					//	IMAGE_ID("image/mapImage.png")[static_cast<const unsigned int>(id)],
					//	true
					//);
					break;
				default:
					break;
				}
			}
		}
	}
}

void MapCtrl::AddScroll(VECTOR2 scrollOffset, int plNum)
{
	this->scrollTbl[plNum] = scrollOffset;
//	this->scrollOffset = scrollOffset;
}
