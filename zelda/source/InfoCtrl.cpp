#include "InfoCtrl.h"

bool InfoCtrl::SetPlayerPos(const VECTOR2 & pos, int num, bool flag)
{
	if (num > sizeof(player))
	{
		return false;
	}
	SetData(player,pos,num,flag);
	return true;
}

bool InfoCtrl::SetEnemyPos(const VECTOR2 & pos, int num, bool flag)
{
	if (num > sizeof(enemy))
	{
		return false;
	}
	SetData(enemy, pos, num,flag);
	return true;
}

bool InfoCtrl::SetAddScroll(const VECTOR2 & offset, int num)
{
	if (num > sizeof(player))
	{
		return false;
	}
	scrNum[num] = offset;
	return true;
}

template<typename objType>
bool InfoCtrl::SetData(objType type, const VECTOR2 & pos,int num,bool flag)
{
	/*if (!CheckSize()(selPos, stageSize))
	{
		return false;
	}*/
	type.pos[num] = pos;
	type.flag[num] = flag;
	return true;
}

VECTOR2 InfoCtrl::GetPlayerPos(int num)
{
	return GetData(player,num);
}

VECTOR2 InfoCtrl::GetEnemyPos(int num)
{
	return GetData(enemy,num);
}
VECTOR2 InfoCtrl::GetAddScroll(int num)
{
	return scrNum[num];
}
template<typename objType>
VECTOR2 InfoCtrl::GetData(objType type, int num)
{
	if (type.flag[num])
	{
		return type.pos[num];
	}
}

InfoCtrl::InfoCtrl()
{
	Init();
}


InfoCtrl::~InfoCtrl()
{
}

void InfoCtrl::Init(void)
{
	player.pos.resize(4);
	player.flag.resize(4);
	scrNum.resize(4);
	enemy.pos.resize(ENEMY_MAX);
	enemy.flag.resize(ENEMY_MAX);	

	// ‘S‘Ì‚ÉNON‚ ‚é‚¢‚Í0(¾ÞÛ)‚ð“ü‚ê‚é
	for (int j = 0; j < enemy.pos.size(); j++)
	{	
		enemy.pos[j]		= { 0,0 };
		enemy.flag[j]		= false;
		
	}
	for (int j = 0; j < player.pos.size(); j++)
	{
		player.pos[j] = { 0,0 };
		player.flag[j] = false;
		scrNum[j]			= { 0,0 };
	}
}
