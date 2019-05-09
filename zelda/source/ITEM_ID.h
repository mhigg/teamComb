#pragma once
// Žæ“¾‚Å‚«‚é±²ÃÑ

enum class ITEM_ID
{
	NONE,		// ‚È‚µ

	// ‹¤’Ê

	POTION_1,	// Îß°¼®Ý
	POTION_2,
	POTION_3,
	POTION_4,
	COIN_1,		// º²Ý
	COIN_2,
	COIN_3,
	COIN_4,
	KEY_1,		// Œ®
	KEY_2,
	MEAT,		// “÷
	NON_1,		// —\”õ
	NON_2,
	NON_3,

	// ½Ã°¼Þ•Ê

	SWORD,
	SHIELD,
	BOOK,
	GOLD,
	DIA,

};

ITEM_ID operator++(ITEM_ID id);