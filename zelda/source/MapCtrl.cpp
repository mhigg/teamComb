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

const VECTOR2 & MapCtrl::GetChipSize(void)
{
	return chipSize;
}
