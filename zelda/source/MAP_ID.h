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
	RESERVE,	// ñ≥ñ≥ñ≥
	DOOR1,
	DOOR2,
	DOOR3,
	DOOR4,
	KEY,
	PANEL,
	LADDER,
	FLAG,
	FIRE1,
	FIRE2,
	RAMP1,
	RAMP2,
	POTION1,
	POTION2,
	BARREL1,
	BARREL2,
	BONE1,
	BONE2,
	BONE3,
	PLAYER,	// Ãﬂ⁄≤‘∞
	MAX
};

MAP_ID operator++(MAP_ID id);