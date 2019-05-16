#include "InfoCtrl.h"

bool InfoCtrl::SetPlayerPos(const VECTOR2 & pos)
{
	return true;
}

bool InfoCtrl::SetEnemyPos(const VECTOR2 & pos)
{
	return true;
}

VECTOR2 InfoCtrl::GetPlayerPos(void)
{
	return playerPos[0];
}

VECTOR2 InfoCtrl::GetEnemyPos(void)
{
	return enemyPos[0];
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
	enemyPos.resize(ENEMY_MAX);
	playerPos.resize(4);
}
