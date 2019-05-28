#include <algorithm>
#include <DxLib.h>
#include <stdlib.h>
#include "Enemy.h"
#include "StageMng.h"
#include "GameCtrl.h"
#include "InfoCtrl.h"

Enemy::Enemy()
{
}

Enemy::Enemy(int enemyNum, VECTOR2 setUpPos, VECTOR2 drawOffset,int  enCnt) :Obj(drawOffset)
{
	Enemy::enCnt = enCnt;
	keyIdTbl = {
		XINPUT_DOWN,			// ��
		XINPUT_LEFT,			// ��
		XINPUT_RIGHT,			// �E
		XINPUT_UP				// ��
	};
	PosTbl = {
		&pos.y,&pos.x,			// ��
		&pos.x,&pos.y,			// ��
		&pos.x,&pos.y,			// �E
		&pos.y,&pos.x			// ��
	};
	SpeedTbl = {
		//			�ʏ�						�ޯ��
		ENEMY_SPEED	,  ENEMY_DASH_SPEED,		// ��
		-ENEMY_SPEED	, -ENEMY_DASH_SPEED,		// ��
		 ENEMY_SPEED	,  ENEMY_DASH_SPEED,		// �E
		-ENEMY_SPEED	, -ENEMY_DASH_SPEED		// ��
	};
	dirOpp = {
		DIR_DOWN	,DIR_LEFT		,DIR_RIGHT,
		DIR_LEFT		,DIR_DOWN	,DIR_UP,
		DIR_RIGHT	,DIR_DOWN	,DIR_UP,
		DIR_UP			,DIR_RIGHT	,DIR_LEFT
	};
	mapMoveTbl = {
					true,			// NONE
					false,			// WALL1
					false,			// WALL2
					false,			// WALL3
					false,			// WALL4
					false,			// WALL5
					false,			// WALL6
					false,			// WALL7
					false,			// WALL8
					false,			// WALL9
					true,			// WALL10
					true,			// WALL11
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
	actOff = VECTOR2(30, 40);
	hitRad = VECTOR2(30, 30);
	behaviorCnt = 0;
	name = static_cast<ENEMY>(enemyNum);
	action = ENEM_ACT::MOVE;
	Init("image/enemy.png", VECTOR2(480 / 8,400 / 5),VECTOR2(8,5), setUpPos);
	comPos.resize(12);
	initAnim();
	EnInit();
	CheckFree();
}

void Enemy::EnInit(void)
{
	speed = ENEMY_SPEED;
	// ���Čn
	deathCnt = 60;
	timeCnt = 0;
	actCnt = 60;
	faintCnt = 0;
	addCnt = { 0,0 };
	oppFlag = false;
}

void Enemy::CheckFree(void)
{
	nearP = 0;
	movePos = 0;
	int actRoot = 0;
	for (int i = 0; i < 4; i++)
	{
		plPos[i] = lpInfoCtrl.GetPlayerPos(i);
		enPos[i] = -1;
		for (int m = 0; m < 3; m++)
		{
			actNum[m] = 0;
			passFlag[i + m * 4] = false;
			checkPos[i + m * 4] = VECTOR2(0, 0);
			comPos[i + m * 4] = 10000;
		}
	}
}

Enemy::~Enemy()
{
}

VECTOR2 Enemy::sidePos(VECTOR2 pos, DIR dir, int speed, int sideNum)
{
	VECTOR2 side;
	switch (dir)
	{
	case DIR_DOWN:
		side = { sideNum,(hitRad.y) + speed - 2 };
		break;
	case DIR_LEFT:
		side = { speed - (hitRad.x),sideNum };
		break;
	case DIR_RIGHT:
		side = { (hitRad.x) + speed - 2,sideNum };
		break;
	case DIR_UP:
		side = { sideNum,speed - (hitRad.y) };
		break;
	default:
		break;
	}
	return pos + side;
}

VECTOR2 Enemy::Distance(DIR tmpDir,VECTOR2 pos)
{
	while (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmpDir, SpeedTbl[tmpDir][0], -hitRad.x)))]
		&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmpDir, SpeedTbl[tmpDir][0], hitRad.x - 1)))]
		&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmpDir, SpeedTbl[tmpDir][0], 0)))])
	{
		if (tmpDir == DIR_DOWN || tmpDir == DIR_UP)
		{
			pos.y += SpeedTbl[tmpDir][0];
			if ((*PosTbl[tmpDir][TBL_MAIN]) == plPos[nearP].x)
			{
				return pos;
			}
		}
		else
		{
			pos.x += SpeedTbl[tmpDir][0];
			if ((*PosTbl[tmpDir][TBL_MAIN]) == plPos[nearP].y)
			{
				return pos;
			}
		}
		
	}
	return pos;
}

int Enemy::SerchPlayer(void)
{
	VECTOR2 tmpPos = Enemy::pos;
	for (int i = 0; i < 4; i++)
	{
		plPos[i] = lpInfoCtrl.GetPlayerPos(i);
		if (plPos[i] != VECTOR2(-1, -1))
		{		
			VECTOR2 tmp = tmpPos - plPos[i];
			enPos[i] = static_cast<int>(sqrt(tmp.x * tmp.x) + sqrt(tmp.y * tmp.y));
		}
	}
	int plNum = 0;
	for (int i = 1; i < 4; i++)
	{	
		if (enPos[i] < enPos[plNum] && enPos[i] != -1)
		{
			plNum = i;
		}	
	}
	return plNum;
}

void Enemy::SetMove(const GameCtrl & controller, weakListObj objList)
{
	scrollOffset = lpInfoCtrl.GetAddScroll(0);

	// ����ł邩�ǂ���
	if (lpInfoCtrl.GetEnemyFlag(Enemy::enCnt))
	{
		// �_�ł̏���
		if (deathCnt % 5 == 0)
		{
			visible = !visible;
		}
		deathCnt--;
		if (deathCnt == 0)
		{
			lpInfoCtrl.SetEnemyPos(VECTOR2(-1, -1), enCnt);
			deathFlag = lpInfoCtrl.GetEnemyFlag(Enemy::enCnt);
		}
		return;
	}
	// �ł��߂���ڲ԰�̌���
	nearP = SerchPlayer();
	// ��ڲ԰�Ƃ̋�������ʓ��Ȃ珈�����s��
	switch (action)
	{
	case ENEM_ACT::SERCH:
		_updater = &Enemy::Serch;
		break;
	case ENEM_ACT::MOVE:
		_updater = &Enemy::Move;
		break;
	case ENEM_ACT::TRA:
		_updater = &Enemy::Track;
		break;
	default:
		_updater = &Enemy::Serch;
		break;
	}
	(this->*_updater)(controller);
	switch (action)
	{
	case ENEM_ACT::SERCH:
		switch (dir)
		{
		case DIR_RIGHT:
			SetAnim("�E����");
			break;
		case DIR_LEFT:
			SetAnim("������");
			break;
		default:
			break;
		}
		break;
	case ENEM_ACT::MOVE:
		switch (dir)
		{
		case DIR_RIGHT:
			SetAnim("�E�ҋ@");
			break;
		case DIR_LEFT:
			SetAnim("���ҋ@");
			break;
		default:
			break;
		}
		break;
	case ENEM_ACT::TRA:
		switch (dir)
		{
		case DIR_RIGHT:
			SetAnim("�E�T��");
			break;
		case DIR_LEFT:
			SetAnim("���T��");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	if (behaviorCnt == 0)
	{
		SetAnim("���ҋ@");
	}
	
	lpInfoCtrl.SetEnemyPos(pos, enCnt);
	timeCnt++;
	behaviorCnt++;
}

bool Enemy::initAnim(void)
{
	int num = static_cast<int>(name) * 2;
	AddAnim("�E�ҋ@", num, 0, 2, 10, true);				// �E
	AddAnim("���ҋ@", num + 1, 0, 2, 10, true);		// ��
	AddAnim("�E�T��", num, 2, 2, 10, true);
	AddAnim("���T��", num + 1, 2, 2, 10, true);
	AddAnim("�E����", num, 4, 1, 30, false);
	AddAnim("������", num + 1, 4, 1, 30, false);
	return true;
}

void Enemy::Move(const GameCtrl & controller)
{
	auto &chipSize = lpStageMng.GetChipSize().x;

	int num = GetRand(10) + 20;
	if (!(timeCnt % num))
	{
		switch (GetRand(4))
		{
		case 0:
			Enemy::dir = DIR_DOWN;
			break;
		case 1:
			Enemy::dir = DIR_LEFT;
			break;
		case 2:
			Enemy::dir = DIR_RIGHT;
			break;
		case 3:
			Enemy::dir = DIR_UP;
			break;
		case 4:
			action = ENEM_ACT::SERCH;
		default:
			break;
		}
		timeCnt = 0;
	}	
	if (action == ENEM_ACT::SERCH)
	{
		return;
	}
	if (!mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Enemy::dir, SpeedTbl[Enemy::dir][0], -hitRad.x)))]
		|| !mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Enemy::dir, SpeedTbl[Enemy::dir][0], hitRad.x - 1)))]
		|| !mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Enemy::dir, SpeedTbl[Enemy::dir][0], 0)))])
	{
		// �ړ��s�̃I�u�W�F�N�g���ׂɂ������ꍇ
		Enemy::dir = dir;
		return;
	}
	// �ړ�����-----------------------------
	(*PosTbl[Enemy::dir][TBL_MAIN]) += SpeedTbl[Enemy::dir][0];
	return;
}

void Enemy::Track(const GameCtrl & controller)
{
	auto &chipSize = lpStageMng.GetChipSize().x;
	//-----------�ړ�-------------

	int tmpAct = actRoot % 4;
	movePos = 0;
	switch (tmpAct)
	{
	case 0:
	case 3:
		if ((*PosTbl[tmpAct][TBL_MAIN]) != checkPos[actRoot].y)
		{
			if (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, static_cast<DIR>(tmpAct), SpeedTbl[static_cast<DIR>(tmpAct)][0], -hitRad.x)))]
				&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, static_cast<DIR>(tmpAct), SpeedTbl[static_cast<DIR>(tmpAct)][0], hitRad.x - 1)))]
				&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, static_cast<DIR>(tmpAct), SpeedTbl[static_cast<DIR>(tmpAct)][0], 0)))])
			{
				dir = static_cast<DIR>(tmpAct);
				(*PosTbl[tmpAct][TBL_MAIN]) += SpeedTbl[tmpAct][0];
				movePos += SpeedTbl[tmpAct][0];
			}
		}
		else
		{
			if (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, dirOpp[tmpAct][actRoot / 4], SpeedTbl[dirOpp[tmpAct][actRoot / 4]][0], -hitRad.x)))]
				&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, dirOpp[tmpAct][actRoot / 4], SpeedTbl[dirOpp[tmpAct][actRoot / 4]][0], hitRad.x - 1)))]
				&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, dirOpp[tmpAct][actRoot / 4], SpeedTbl[dirOpp[tmpAct][actRoot / 4]][0], 0)))])
			{
				dir = dirOpp[tmpAct][actRoot / 4];
				(*PosTbl[tmpAct][TBL_OPP]) += SpeedTbl[dirOpp[tmpAct][actRoot / 4]][0];
				movePos += SpeedTbl[dirOpp[tmpAct][actRoot / 4]][0];
			}
			if ((*PosTbl[tmpAct][TBL_OPP]) == checkPos[actRoot].x)
			{
				action = ENEM_ACT::SERCH;
				return;
			}
		}
		break;
	case 1:
	case 2:
		if ((*PosTbl[tmpAct][TBL_MAIN]) != plPos[nearP].x)
		{
			if (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, static_cast<DIR>(tmpAct), SpeedTbl[static_cast<DIR>(tmpAct)][0], -hitRad.x)))]
				&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, static_cast<DIR>(tmpAct), SpeedTbl[static_cast<DIR>(tmpAct)][0], hitRad.x - 1)))]
				&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, static_cast<DIR>(tmpAct), SpeedTbl[static_cast<DIR>(tmpAct)][0], 0)))])
			{
				dir = static_cast<DIR>(tmpAct);
				(*PosTbl[tmpAct][TBL_MAIN]) += SpeedTbl[tmpAct][0];
				movePos += SpeedTbl[tmpAct][0];
			}
			else
			{
				movePos += 0;
			}
		}
		else
		{
			if (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, dirOpp[tmpAct][actRoot / 4], SpeedTbl[dirOpp[tmpAct][actRoot / 4]][0], -hitRad.x)))]
				&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, dirOpp[tmpAct][actRoot / 4], SpeedTbl[dirOpp[tmpAct][actRoot / 4]][0], hitRad.x - 1)))]
				&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, dirOpp[tmpAct][actRoot / 4], SpeedTbl[dirOpp[tmpAct][actRoot / 4]][0], 0)))])
			{
				dir = dirOpp[tmpAct][actRoot / 4];
				(*PosTbl[tmpAct][TBL_OPP]) += SpeedTbl[dirOpp[tmpAct][actRoot / 4]][0];
				movePos += SpeedTbl[dirOpp[tmpAct][actRoot / 4]][0];
			}
			if ((*PosTbl[tmpAct][TBL_OPP]) == plPos[nearP].y)
			{
				action = ENEM_ACT::SERCH;
				return;
			}
		}
		break;
	}
	//---------�ړ������Ă��Ȃ������ꍇ�ēx���������߂�-------------
	if (movePos == 0)
	{
		action = ENEM_ACT::MOVE;	
		return;
	}
}

//-------------�߽�T��(�ړ��߽���Ȃ����̂�)-----------
void Enemy::Serch(const GameCtrl & controller)
{
	auto &chipSize = lpStageMng.GetChipSize().x;
	CheckFree();
	//---------------��ꕪ��_�̐ݒ�----------------
	for (DIR tmp = DIR_DOWN; tmp < DIR::DIR_MAX; tmp = static_cast<DIR>(tmp + 1))
	{
		if (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmp, SpeedTbl[tmp][0], -hitRad.x)))]
			&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmp, SpeedTbl[tmp][0], hitRad.x - 1)))]
			&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmp, SpeedTbl[tmp][0], 0)))])
		{
			VECTOR2 tmpPos = pos;
			checkPos[static_cast<int>(tmp)] = Distance(tmp, tmpPos);
			passFlag[static_cast<int>(tmp)] = true;
			//------------��񕪊�_�̐ݒ�---------------
			for (int opp = 1; opp < 3; opp++)
			{
				DIR setDir = static_cast<DIR>(tmp + opp * 4);
				checkPos[static_cast<int>(setDir)] = Distance(dirOpp[tmp][opp], checkPos[static_cast<int>(tmp)]);
				passFlag[static_cast<int>(setDir)] = true;
			}
		}
		//---------�D��x��ݒ�-------------
		for (int e = 0; e < 12; e++)
		{
			if (passFlag[e])
			{
				VECTOR2 exPos = { plPos[nearP].x - checkPos[e].x ,plPos[nearP].y - checkPos[e].y };
				comPos[e] = static_cast<int>(sqrt(exPos.x*exPos.x) + sqrt(exPos.y * exPos.y));
			}
		}
		// ���A��񕪊�_�܂ł�DIR������
		for (int e = 1; e < 12; e++)
		{
			if (comPos[e] < comPos[actNum[2]])
			{
				actNum[2] = e;
				actRoot = e;
			}
		}
		if (actCnt <= 0)
		{
			action = ENEM_ACT::TRA;
			actCnt = 60;
			return;
		}
		actCnt--;
		return;
	}
}

void Enemy::SpMove(const GameCtrl & controller)
{
}

void Enemy::Escape(const GameCtrl & controller)
{
}

void Enemy::Wait(const GameCtrl & controller)
{
	return;
}

void Enemy::Damage(const GameCtrl & controller)
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
