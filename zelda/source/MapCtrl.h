// Ï¯ÌßIDŠÖ˜A‚ÅAÏ¯Ìßã‚Ìî•ñ‚ğ‘€ì‚·‚é¸×½

#pragma once
#include "VECTOR2.h"
#include "MAP_ID.h"

class MapCtrl
{
public:
	MapCtrl();
	~MapCtrl();

	bool SetUp(VECTOR2 stageSize, VECTOR2 chipSize);
	bool SetMapData(VECTOR2 mapPos, MAP_ID id);
};
