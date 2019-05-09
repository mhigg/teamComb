#pragma once
// œØÃﬂèÓïÒ

enum class MAP_ID
{
	NONE,	// âΩÇ‡Ç»Çµ
	WALL1,
	WALL2,
	WALL3,
	WALL4,
	WALL5,
	WALL6,
	WALL7,
	WALL8,
	WALL9,
	WALL10,
	WALL11,
	WALL12,
	PLAYER,	// Ãﬂ⁄≤‘∞
	DOOR1,
	DOOR2,
	DOOR3,
	DOOR4,
	WALL13,
	WALL14,
	WALL15,
	WALL16,
	WALL17,
	WALL18,
	MAX
};

MAP_ID operator++(MAP_ID id);