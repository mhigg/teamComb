#include <algorithm>
#include <DxLib.h>
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
	moveSpeed = ENEMY_SPEED;
}

Enemy::~Enemy()
{
}

void Enemy::SetMove(const GameCtrl & controller, weakListObj objList)
{
	switch (GetRand(6))
	{
	case 0:
		pos.x += moveSpeed;
		break;
	case 1:
		pos.x -= moveSpeed;
		break;
	case 2:
		pos.y += moveSpeed;
		break;
	case 3:pos.y -= moveSpeed;
		break;
	case 4:
	case 5:
	default:
		break;
	}
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
