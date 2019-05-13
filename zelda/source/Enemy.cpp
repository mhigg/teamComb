#include <algorithm>
#include <DxLib.h>
#include "Enemy.h"
#include "StageMng.h"
#include "GameCtrl.h"

Enemy::Enemy()
{
}

Enemy::Enemy(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt, int Enum, VECTOR2 setUpPos, VECTOR2 drawOffset)
{
	speed = ENEMY_SPEED;
	keyIdTbl = {
		XINPUT_DOWN,		// ��
		XINPUT_LEFT,		// ��
		XINPUT_RIGHT,		// �E
		XINPUT_UP			// ��
	};
	PosTbl = {
		&pos.y,&pos.x,	// ��
		&pos.x,&pos.y,	// ��
		&pos.x,&pos.y,	// �E
		&pos.y,&pos.x	// ��
	};
	SpeedTbl = {
		//		�ʏ�						�ޯ��
		ENEMY_SPEED	,  ENEMY_DASH_SPEED,		// ��
		-ENEMY_SPEED	, -ENEMY_DASH_SPEED,		// ��
		 ENEMY_SPEED	,  ENEMY_DASH_SPEED,		// �E
		-ENEMY_SPEED	, -ENEMY_DASH_SPEED		// ��
	};
	DirTbl = {
		//	MAIN				REV				OPP1				 OPP2
		DIR_DOWN	,DIR_UP		,DIR_LEFT		,DIR_RIGHT,		// ��(REV:��)(���E�E)
		DIR_LEFT		,DIR_RIGHT	,DIR_DOWN	,DIR_UP,			// ��(REV:�E)(��E��)
		DIR_RIGHT	,DIR_LEFT		,DIR_DOWN	,DIR_UP,			// �E(REV:��)(��E��)
		DIR_UP			,DIR_DOWN	,DIR_LEFT		,DIR_RIGHT		// ��(REV:��)(���E�E)
	};
	mapMoveTbl = {
					true,	// NONE
					false,	// WALL1
					false,	// WALL2
					false,	// WALL3
					false,	// WALL4
					false,	// WALL5
					false,	// WALL6
					false,	// WALL7
					false,	// WALL8
					false,	// WALL9
					true,	// WALL10
					true,	// WALL11
					false,	// WALL12
					false,	// WALL13
					false,	// WALL14
					false,	// WALL15
					false,	// WALL16
					false,	// WALL17
					false,	// WALL18
					false,	// WALL19	// GetMapData�̌Œ�ID
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
					false,  // WALL31
					false,  // WALL32
					false,  // WALL33
					false,  // WALL34
					false,  // WALL35
					false,  // WALL36
					false,	// WALL37	
					false,	// WALL38	
					true,	// WALL39	
					false,	// DOOR1
					false,	// DOOR2
					false,	// DOOR3
					false,	// DOOR4
					true,	// POTION_1
					true,	// POTION_2
					true,	// POTION_3
					true,	// POTION_4
					true,	// COIN_1
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
					false,	// BOX_1	// ��
					false,	// BOX_2	// �󂢂Ă����
					true,	// MOTH_1	// ���
					false,	// MOTH_2	// ��ꂽ���
					true,	// MOTH_3	// �M
					false,	// MOTH_4	// ��ꂽ�M
					false,	// TREE_1	// ��
					false,	// TREE_2
					false,	// TREE_3
					false,	// TREE_4
					false,	// HOLL_1	// ���
					false,	// HOLL_2
					false,	// HOLL_3
					false,	// HOLL_4
					false,	// STONE_1	// ��
					false,	// STONE_2
					false,	// STONE_3
					false,	// STONE_4					
	};
	this->objType = OBJ_ENEMY;
	data.name = static_cast<ENEMY>(Enum);
	Init(fileName, VECTOR2(40, 40), VECTOR2(1, 1), setUpPos);

	// ���Čn
	timeCnt = 0;
	behaviorCnt = 0;
	faintCnt = 0;
	oppFlag = false;

	action = ENEM_ACT::DO_NOTHING;
}

Enemy::~Enemy()
{
}

void Enemy::SetMove(const GameCtrl & controller, weakListObj objList)
{
	timeCnt++;
	auto &chipSize = lpStageMng.GetChipSize().x;
	auto sidePos = [&](VECTOR2 pos, DIR dir, int speed, SIDE_CHECK sideFlag) {
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

	auto &inputTbl = controller.GetInputState(KEY_TYPE_NOW);

	if (!(timeCnt % 10))
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
	}
	if (!(action == ENEM_ACT::DO_NOTHING))
	{
		if (!mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Enemy::dir, SpeedTbl[Enemy::dir][inputTbl[0][XINPUT_RUN_RB]], IN_SIDE), MAP_ID::NONE))])
		{
			// �ړ��s�̃I�u�W�F�N�g���ׂɂ������ꍇ
			Enemy::dir = dir;
			return;
		}
		// �ړ�����-----------------------------
		// �ύX���������W�̕ϐ��A�h���X += �ړ���
		(*PosTbl[Enemy::dir][TBL_MAIN]) += SpeedTbl[Enemy::dir][inputTbl[0][XINPUT_RUN_RB]];
		return;
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
