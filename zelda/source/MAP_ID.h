#pragma once
enum class MAP_ID
{
	NONE,	// �����Ȃ�
	PLAYER,	// ��ڲ԰
	MAX
};

MAP_ID operator++(MAP_ID id);