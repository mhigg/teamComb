#pragma once
// �擾�ł��鱲��

enum class ITEM_ID
{
	NONE,		// �Ȃ�

	// ����

	POTION_1,	// �߰���
	POTION_2,
	POTION_3,
	POTION_4,
	COIN_1,		// ���
	COIN_2,
	COIN_3,
	COIN_4,
	KEY_1,		// ��
	KEY_2,
	MEAT,		// ��
	NON_1,		// �\��
	NON_2,
	NON_3,

	// �ð�ޕ�

	SWORD,
	SHIELD,
	BOOK,
	GOLD,
	DIA,

};

ITEM_ID operator++(ITEM_ID id);