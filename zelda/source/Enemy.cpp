#include "Enemy.h"



Enemy::Enemy()
{
}

Enemy::Enemy(EnemyData data, VECTOR2 setUpPos, VECTOR2 drawOffset)
{
	this->objType = OBJ_ENEMY;
}


Enemy::~Enemy()
{
}

bool Enemy::CheckDeath(void)
{
	return deathFlag;
}

bool Enemy::CheckObjType(OBJ_TYPE type)
{
	return (type == objType);
}

const OBJ_TYPE & Enemy::GetObjType(void) const
{
	return objType;
}

void Enemy::SetDeathFlag(bool deathFlag)
{
	this->deathFlag = deathFlag;
}
