#include "InfoCtrl.h"

bool InfoCtrl::SetPlayerPos(const VECTOR2 & pos, int num, bool flag)
{
	if (num > 4)
	{
		return false;
	}
	plPos[num] = pos;
	plFlag[num] = flag;
	return true;
}

bool InfoCtrl::SetEnemyPos(const VECTOR2 & pos, int num, bool flag)
{
	if (num > ENEMY_MAX)
	{
		return false;
	}
	enPos[num]	= pos;
	enFlag[num]	=flag;
	return true;
}

bool InfoCtrl::SetAddScroll(const VECTOR2 & offset, int num)
{
	if (num > 4)
	{
		return false;
	}
	scrNum[num] = offset;
	return true;
}

VECTOR2 InfoCtrl::GetPlayerPos(int num)
{
	if (plFlag[num])
	{
		return plPos[num];
	}
	return VECTOR2(-1, -1);
}

VECTOR2 InfoCtrl::GetEnemyPos(int num)
{
	if (enFlag[num])
	{
		return enPos[num];
	}
	return VECTOR2(-1, -1);
}
VECTOR2 InfoCtrl::GetAddScroll(int num)
{
	return scrNum[num];
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
	plPos.resize(4);
	plFlag.resize(4);
	scrNum.resize(4);
	enPos.resize(ENEMY_MAX);
	enFlag.resize(ENEMY_MAX);	

	// ‘S‘Ì‚ÉNON‚ ‚é‚¢‚Í0(¾ÞÛ)‚ð“ü‚ê‚é
	for (int j = 0; j < ENEMY_MAX; j++)
	{	
		enPos[j]		= { 0,0 };
		enFlag[j]	= false;
		
	}
	for (int j = 0; j < 4; j++)
	{
		plPos[j]		= { 0,0 };
		plFlag[j]	= false;
		scrNum[j]	= { 0,0 };
	}
}
