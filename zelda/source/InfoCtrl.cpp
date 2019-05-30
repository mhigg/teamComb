#include "InfoCtrl.h"

bool InfoCtrl::SetPlayerPos(const VECTOR2 & pos, int num)
{
	if (num > 4)
	{
		return false;
	}
	plPos[num] = pos;
	return true;
}

bool InfoCtrl::SetPlayerFlag(bool flag, int num)
{
	if (num > 4)
	{
		return false;
	}
	plFlag[num] = flag;
	return true;
}

bool InfoCtrl::SetEnemyPos(const VECTOR2 & pos, int num)
{
	if (num > ENEMY_MAX)
	{
		return false;
	}
	enPos[num]	= pos;
	return true;
}

bool InfoCtrl::SetEnemyFlag(bool flag, int num)
{
	enFlag[num] = flag;
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

bool InfoCtrl::SetScore(int val, int num)
{
	if (num > 4)
	{
		return false;
	}
	plScore[num] = val;
	return true;
}

bool InfoCtrl::SetBonus(int val, int num)
{
	if (num > 4)
	{
		return false;
	}
	plBonus[num] = val;
	return true;
}

bool InfoCtrl::SetSelectChara(CHARA_TYPE val, int num)
{
	if (num > 4)
	{
		return false;
	}
	selectChara[num] = val;
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
	if (!enFlag[num])
	{
		return enPos[num];
	}
	return VECTOR2(-1, -1);
}
bool InfoCtrl::GetPlayerFlag(int num)
{
	return plFlag[num];
}
bool InfoCtrl::GetEnemyFlag(int num)
{
	return enFlag[num];
}
VECTOR2 InfoCtrl::GetAddScroll(int num)
{
	return scrNum[num];
}

int InfoCtrl::GetScore(int num)
{
	return plScore[num];
}

int InfoCtrl::GetBonus(int num)
{
	return plBonus[num];
}

CHARA_TYPE InfoCtrl::GetSelectChara(int num)
{
	return selectChara[num];
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

	// �S�̂�NON���邢��0(���)������
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
		plScore[j] = 0;
		plBonus[j] = 0;
		selectChara[j] = CHARA_MAX;
	}
}
