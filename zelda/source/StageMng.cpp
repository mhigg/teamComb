#include <memory>
#include <DxLib.h>
#include "StageMng.h"
#include "BaseScene.h"
#include "MapCtrl.h"

struct DataHeader
{
	char fileID[15];	// Ãß≤ŸÇÃIDèÓïÒ
	char verID;			//  ﬁ∞ºﬁÆ›î‘çÜ
	char reserve1[2];	// ó\ñÒóÃàÊ
	int sizeX;			// œØÃﬂÇÃœΩ“êîX
	int sizeY;			// œØÃﬂÇÃœΩ“êîY
	char reserve2[1];	// ó\ñÒóÃàÊ
	char sum;			// ª—íl
};

#define ZELDA_VER_ID 0x01						// Ãß≤Ÿ ﬁ∞ºﬁÆ›î‘çÜ
#define ZELDA_FILE_ID "ZELDA_MAP_DATA"			// Ãß≤ŸÇÃIDèÓïÒ	

StageMng::StageMng()
{
	Init();
}


StageMng::~StageMng()
{
}



bool StageMng::MapSave(void)
{
	DataHeader expData = {
		ZELDA_FILE_ID,
		ZELDA_VER_ID,
		{ 0,0 },
		mapSize.x,
		mapSize.y,
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

bool StageMng::MapLoad(sharedListObj objList, bool editFlag)
{
	// œØÃﬂ√ﬁ∞¿ÇÃ€∞ƒﬁ
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

const VECTOR2 & StageMng::GetChipSize(void)
{
	return chipSize;
}

const VECTOR2 & StageMng::GetStageSize(void)
{
	return stageSize;
}

const VECTOR2 & StageMng::GetDrawOffset(void)
{
	return drawOffset;
}

bool StageMng::Init(void)
{
	stageSize = VECTOR2(GAME_AREA_SIZE_X, GAME_AREA_SIZE_Y);
	chipSize = VECTOR2(CHIP_SIZE,CHIP_SIZE);
	mapSize = stageSize / chipSize;
	return true;
}
