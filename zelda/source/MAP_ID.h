#pragma once
// ϯ�ߏ��

enum class MAP_ID
{
	NONE,	// �����Ȃ�
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
	PLAYER,	// ��ڲ԰
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
	NON_4,
	// �ð�ޕ�
	// �ð��1
	SWORD,		
	SHIELD,
	BOOK,
	GOLD,
	DIA,
	// �ð��2

	MAX
};

MAP_ID operator++(MAP_ID id);