#include <algorithm>
#include <DxLib.h>
#include <stdlib.h>
#include "Enemy.h"
#include "StageMng.h"
#include "GameCtrl.h"

Enemy::Enemy()
{
}

Enemy::Enemy(int enemyNum, VECTOR2 setUpPos, VECTOR2 drawOffset)
{
	speed = ENEMY_SPEED;
	keyIdTbl = {
		XINPUT_DOWN,		// â∫
		XINPUT_LEFT,			// ç∂
		XINPUT_RIGHT,		// âE
		XINPUT_UP				// è„
	};
	PosTbl = {
		&pos.y,&pos.x,	// â∫
		&pos.x,&pos.y,	// ç∂
		&pos.x,&pos.y,	// âE
		&pos.y,&pos.x		// è„
	};
	SpeedTbl = {
		//			í èÌ								¿ﬁØº≠
		ENEMY_SPEED		,  ENEMY_DASH_SPEED,		// â∫
		-ENEMY_SPEED	, -ENEMY_DASH_SPEED,	// ç∂
		 ENEMY_SPEED	,  ENEMY_DASH_SPEED,		// âE
		-ENEMY_SPEED	, -ENEMY_DASH_SPEED		// è„
	};
	mapMoveTbl = {
					true,		// NONE
					false,	// WALL1
					false,	// WALL2
					false,	// WALL3
					false,	// WALL4
					false,	// WALL5
					false,	// WALL6
					false,	// WALL7
					false,	// WALL8
					false,	// WALL9
					true,		// WALL10
					true,		// WALL11
					false,	// WALL12
					false,	// WALL13
					false,	// WALL14
					false,	// WALL15
					false,	// WALL16
					false,	// WALL17
					false,	// WALL18
					false,	// WALL19	// GetMapDataÇÃå≈íËID
					false,	// WALL20
					false,	// WALL21				
					false,	// WALL22
					false,	// WALL23
					false,	// WALL24
					false,	// WALL25
					false,	// WALL26
					false,	// WALL27
					false,	// WALL28
					false,	// WALL29
					false,	// WALL30
					false,	// WALL31
					false,	// WALL32
					false,  // WALL33
					false,  // WALL34
					false,  // WALL35
					false,  // WALL36
					false,	// WALL37	
					false,	// WALL38	
					true,		// WALL39	
					false,	// DOOR1
					false,	// DOOR2
					false,	// DOOR3
					false,	// DOOR4
					true,		// POTION_1
					true,		// POTION_2
					true,		// POTION_3
					true,		// POTION_4
					true,		// COIN_1
					true,	// COIN_2
					true,	// COIN_3
					true,	// COIN_4
					true,	// KEY_1
					true,	// KEY_2
					true,	// MEAT
					true,	// PLAYER
					true,	// ENEMY
					true,	// SWORD
					true,	// SHIELD
					true,	// BOOK
					true,	// GOLD
					true,	// DIA
					false,	// BOX_1	// ïÛî†
					false,	// BOX_2	// ãÛÇ¢ÇƒÇ¢ÇÈïÛî†
					true,	// MOTH_1	// ¬Œﬁ
					false,	// MOTH_2	// âÛÇÍÇΩ¬Œﬁ
					true,	// MOTH_3	// íM
					false,	// MOTH_4	// âÛÇÍÇΩíM
					false,	// TREE_1	// ñÿ
					false,	// TREE_2
					false,	// TREE_3
					false,	// TREE_4
					false,	// HOLL_1	// à‰åÀ
					false,	// HOLL_2
					false,	// HOLL_3
					false,	// HOLL_4
					false,	// STONE_1	// ä‚
					false,	// STONE_2
					false,	// STONE_3
					false,	// STONE_4					
	};
	this->objType = OBJ_ENEMY;
	name = static_cast<ENEMY>(enemyNum);
	Init("image/enemy.png", VECTOR2(480 / 8,320 / 4),VECTOR2(8,4), setUpPos);

	// ∂≥›ƒån
	timeCnt			= 0;
	behaviorCnt		= 0;
	faintCnt			= 0;
	addCnt				= { 0,0 };
	oppFlag			= false;
	initAnim();

	action = ENEM_ACT::DO_NOTHING;
}

Enemy::~Enemy()
{
}

void Enemy::SetMove(const GameCtrl & controller, weakListObj objList)
{
	if (!behaviorCnt)
	{
		SetAnim("ãxåe1");
	}
	timeCnt++;
	behaviorCnt++;
	auto &chipSize = lpStageMng.GetChipSize().x;
	auto sidePos = [&chipSize = chipSize](VECTOR2 pos, DIR dir, int speed, SIDE_CHECK sideFlag) {
		VECTOR2 side;
		switch (dir)
		{
		case DIR_DOWN:
			side = { 0,(chipSize - sideFlag) + speed };
			break;
		case DIR_LEFT:
			side = { speed - (sideFlag ^ 1),0 };
			break;
		case DIR_RIGHT:
			side = { (chipSize - sideFlag) + speed,0 };
			break;
		case DIR_UP:
			side = { 0,speed - (sideFlag ^ 1) };
			break;
		default:
			break;
		}
		return pos + side;
	};

	int num = GetRand(10) + 20;
	if (!(timeCnt % num))
	{
		switch (GetRand(4))
		{
		case 0:
			Enemy::dir = DIR_DOWN;
			action = ENEM_ACT::MOVE;
			break;
		case 1:
			Enemy::dir = DIR_LEFT;
			action = ENEM_ACT::MOVE;
			break;
		case 2:
			Enemy::dir = DIR_RIGHT;
			action = ENEM_ACT::MOVE;
			break;
		case 3:
			Enemy::dir = DIR_UP;
			action = ENEM_ACT::MOVE;
			break;
		case 4:
			action = ENEM_ACT::DO_NOTHING;
		default:
			break;
		}
		timeCnt = 0;
	}
	if (behaviorCnt % 4)
	{
		switch (dir)
		{
		case DIR_RIGHT:
			SetAnim("ãxåe1");
			break;
		case DIR_LEFT:
			SetAnim("ãxåe2");
			break;
		default:
			break;
		}
		return;
	}
	if (!(action == ENEM_ACT::DO_NOTHING))
	{
		if (!mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Enemy::dir, SpeedTbl[Enemy::dir][0], IN_SIDE)))])
		{
			// à⁄ìÆïsâ¬ÇÃÉIÉuÉWÉFÉNÉgÇ™ó◊Ç…Ç†Ç¡ÇΩèÍçá
			Enemy::dir = dir;
			switch (dir)
			{
			case DIR_RIGHT:
				SetAnim("ãxåe1");
				break;
			case DIR_LEFT:
				SetAnim("ãxåe2");
				break;
			default:
				break;
			}
			return;
		}
		// à⁄ìÆèàóù-----------------------------
		if (dir == 0 || dir == 3)
		{
			addCnt.y += SpeedTbl[Enemy::dir][0];
		}
		else
		{
			addCnt.x += SpeedTbl[Enemy::dir][0];
		}
		// ïœçXÇµÇΩÇ¢ç¿ïWÇÃïœêîÉAÉhÉåÉX += à⁄ìÆó 
		if ((abs(addCnt.x) > ENEMY_LIM) || (abs(addCnt.y) > ENEMY_LIM))
		{
			return;
		}
		(*PosTbl[Enemy::dir][TBL_MAIN]) += SpeedTbl[Enemy::dir][0];
		return;
	}
	switch (dir)
	{
	case DIR_RIGHT:
		SetAnim("ãxåe1");
		break;
	case DIR_LEFT:
		SetAnim("ãxåe2");
		break;
	default:
		break;
	}
}

bool Enemy::initAnim(void)
{
	int num = static_cast<int>(name) * 2;
	AddAnim("ãxåe1", num, 0, 3, 10, true);
	AddAnim("ãxåe2", num + 1, 0, 3, 10, true);
	return true;
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
