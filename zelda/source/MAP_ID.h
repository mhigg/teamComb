#pragma once
// ϯ�ߏ��

enum class MAP_ID
{
	NONE,			// �����Ȃ�
	// ϯ�ߗp
	WALL1,			// ��
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
	WALL21,
	WALL22,			
	WALL23,
	WALL24,
	WALL25,
	WALL26,
	WALL27,
	WALL28,
	WALL29,	// ��
	WALL30,	// ��
	WALL31,	// ��
	DOOR1,			// ��
	DOOR2,
	DOOR3,
	DOOR4,
	// ����
	POTION_1,	// �߰���
	POTION_2,
	POTION_3,
	POTION_4,
	COIN_1,		// ���
	COIN_2,
	COIN_3,
	COIN_4,
	KEY_1,			// ��
	KEY_2,
	MEAT,			// ��
	// ���I��޼ު
	PLAYER,				// ��ڲ԰
	ENEMY,				// ��а
	// �ð�ޕ�
	SWORD,		
	SHIELD,
	BOOK,
	GOLD,
	DIA,
	BOX_1,
	BOX_2,
	MOTH_1,
	MOTH_2,
	MOTH_3,
	MOTH_4,
	// ��^��޼ު
	TREE_1,			// ��
	TREE_2,
	TREE_3,
	TREE_4,
	HOLL_1,			// ���
	HOLL_2,
	HOLL_3,
	HOLL_4,
	STONE_1,			// ��
	STONE_2,
	STONE_3,
	STONE_4,
	MAX
};

#define ITEM_ID_START MAP_ID::POTION_1
#define ITEM_MAX (static_cast<int>(MAP_ID::MAX) - static_cast<int>(ITEM_ID_START))

MAP_ID operator++(MAP_ID id);