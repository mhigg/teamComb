#pragma once
// œØÃﬂèÓïÒ

enum class MAP_ID
{
	NONE,	// âΩÇ‡Ç»Çµ
	// œØÃﬂóp
	WALL1,		// ï«
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
	WALL13,
	WALL14,
	WALL15,
	WALL16,
	WALL17,
	WALL18,
	WALL19,
	WALL20,
	DOOR1,		// î‡
	DOOR2,
	DOOR3,
	DOOR4,
	// ±≤√—
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
	SWORD,		
	SHIELD,
	BOOK,
	GOLD,
	DIA,
	NON_5,
	PLAYER,		// Ãﬂ⁄≤‘∞
	ENEMY,
	MAX
};

MAP_ID operator++(MAP_ID id);