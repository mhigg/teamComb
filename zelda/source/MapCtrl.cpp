#include "MapCtrl.h"



MapCtrl::MapCtrl()
{
}


MapCtrl::~MapCtrl()
{
}

bool MapCtrl::SetUp(VECTOR2 stageSize, VECTOR2 chipSize)
{
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

const VECTOR2 & MapCtrl::GetChipSize(void)
{
	return chipSize;
}
