#pragma once
enum class MAP_ID
{
	NONE,	// ‰½‚à‚È‚µ
	PLAYER,	// ÌßÚ²Ô°
	MAX
};

MAP_ID operator++(MAP_ID id);