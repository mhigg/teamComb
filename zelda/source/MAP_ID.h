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
	// ã§í 
	POTION_1,	// Œﬂ∞ºÆ›
	POTION_2,
	POTION_3,
	POTION_4,
	COIN_1,		// ∫≤›
	COIN_2,
	COIN_3,
	COIN_4,
	KEY_1,		// åÆ
	KEY_2,
	MEAT,		// ì˜
	NON_1,		// ó\îı
	NON_2,
	NON_3,
	NON_4,
	// Ω√∞ºﬁï 
	// Ω√∞ºﬁ1
	SWORD,		
	SHIELD,
	BOOK,
	GOLD,
	DIA,
	// Ω√∞ºﬁ2

	MAX
};

MAP_ID operator++(MAP_ID id);