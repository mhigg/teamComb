#include "Enemy.h"



Enemy::Enemy()
{
	Init("image/ghost.png", VECTOR2(40, 40), VECTOR2(1, 1), { 0,0 });
}

Enemy::Enemy(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt, int Enum, VECTOR2 setUpPos, VECTOR2 drawOffset)
{
	this->objType = OBJ_ENEMY;
	data.name = static_cast<ENEMY>(Enum);
	Init(fileName, VECTOR2(40, 40), VECTOR2(1, 1), setUpPos);
}

Enemy::~Enemy()
{
}

void Enemy::SetMove(const GameCtrl & controller, weakListObj objList)
{
	CheckDeath();
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
