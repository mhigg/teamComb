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

Enemy::Enemy(int enemyNum, VECTOR2 setUpPos, VECTOR2 drawOffsetint,int  enCnt) :Obj(drawOffset)
{
	Enemy::enCnt = enCnt;
	keyIdTbl = {
		XINPUT_DOWN,			// â∫
		XINPUT_LEFT,			// ç∂
		XINPUT_RIGHT,			// âE
		XINPUT_UP				// è„
	};
	PosTbl = {
		&pos.y,&pos.x,			// â∫
		&pos.x,&pos.y,			// ç∂
		&pos.x,&pos.y,			// âE
		&pos.y,&pos.x			// è„
	};
	SpeedTbl = {
		//			í èÌ						¿ﬁØº≠
		ENEMY_SPEED	,  ENEMY_DASH_SPEED,		// â∫
		-ENEMY_SPEED	, -ENEMY_DASH_SPEED,		// ç∂
		 ENEMY_SPEED	,  ENEMY_DASH_SPEED,		// âE
		-ENEMY_SPEED	, -ENEMY_DASH_SPEED		// è„
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
	actOff = VECTOR2(30, 40);
	hitRad = VECTOR2(30, 30);
	name = static_cast<ENEMY>(enemyNum);
	Init("image/enemy.png", VECTOR2(480 / 8,320 / 4),VECTOR2(8,4), setUpPos);
	comPos.resize(12);
	initAnim();
	EnInit();
}

void Enemy::EnInit(void)
{
	speed = ENEMY_SPEED;
	// ∂≥›ƒån
	timeCnt = 0;
	behaviorCnt = 0;
	faintCnt = 0;
	addCnt = { 0,0 };
	oppFlag = false;
	_updater = &Enemy::Track;
	action = ENEM_ACT::SERCH;
}

void Enemy::CheckFree(void)
{
	actNum = 0;
	nearP = 0;
	movePos = 0;
	for (int i = 0; i < 4; i++)
	{
		plPos[i] = lpInfoCtrl.GetPlayerPos(i);
		enPos[i] = -1;
		for (int m = 0; m < 3; m++)
		{
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

VECTOR2 Enemy::Serch(DIR tmpDir,VECTOR2 pos)
{
	while (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmpDir, SpeedTbl[tmpDir][0], -hitRad.x)))]
		&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmpDir, SpeedTbl[tmpDir][0], hitRad.x - 1)))]
		&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmpDir, SpeedTbl[tmpDir][0], 0)))])
	{
		if (tmpDir == DIR_DOWN || tmpDir == DIR_UP)
		{
			pos.y += SpeedTbl[tmpDir][0];
		}
		else
		{
			pos.x += SpeedTbl[tmpDir][0];
		}
	}
	return pos;
}

void Enemy::SetMove(const GameCtrl & controller, weakListObj objList)
{
	deathFlag = lpInfoCtrl.GetEnemyFlag(Enemy::enCnt);
	if (!deathFlag)
	{
		visible = false;
		return;
	}
	scrollOffset = lpInfoCtrl.GetAddScroll(0);
	lpInfoCtrl.SetEnemyPos(pos, enCnt);
	if (!behaviorCnt)
	{
		SetAnim("ãxåe1");
	}
	(this->*_updater)(controller);
	timeCnt++;
	behaviorCnt++;
}

bool Enemy::initAnim(void)
{
	int num = static_cast<int>(name) * 2;
	AddAnim("ãxåe1", num, 0, 3, 10, true);
	AddAnim("ãxåe2", num + 1, 0, 3, 10, true);
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
		if (!mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Enemy::dir, SpeedTbl[Enemy::dir][0], -hitRad.x)))]
			|| !mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Enemy::dir, SpeedTbl[Enemy::dir][0], hitRad.x - 1)))])
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

void Enemy::Track(const GameCtrl & controller)
{
	auto &chipSize = lpStageMng.GetChipSize().x;

	//------------- ﬂΩíTçı(à⁄ìÆ ﬂΩÇ™Ç»Ç¢éûÇÃÇ›)-----------
	if (action == ENEM_ACT::SERCH)
	{
		CheckFree();
		//---------------ëÊàÍï™äÚì_ÇÃê›íË----------------
		for (DIR tmp = DIR_DOWN; tmp < DIR::DIR_MAX; tmp = static_cast<DIR>(tmp + 1))
		{
			if (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmp, SpeedTbl[Enemy::dir][0], -hitRad.x)))]
				&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmp, SpeedTbl[Enemy::dir][0], hitRad.x - 1)))]
				&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmp, SpeedTbl[Enemy::dir][0], 0)))])
			{
				VECTOR2 tmpPos = pos;
				checkPos[static_cast<int>(tmp)] = Serch(tmp, tmpPos);
				passFlag[static_cast<int>(tmp)] = true;
				//------------ëÊìÒï™äÚì_ÇÃê›íË---------------
				for (int opp = 1; opp < 3; opp++)
				{
					DIR setDir = static_cast<DIR>(tmp + opp * 4);
					checkPos[static_cast<int>(setDir)] = Serch(dirOpp[tmp][opp], checkPos[static_cast<int>(tmp)]);
					passFlag[static_cast<int>(setDir)] = true;
				}
			}
		}
		//-------------ãﬂÇ¢Ãﬂ⁄≤‘∞Çåüçı------------------
		VECTOR2 tmpPos = Enemy::pos;
		for (int i = 0; i < 4; i++)
		{
			if (plPos[i] != VECTOR2(-1, -1))
			{
				VECTOR2 tmp = tmpPos - plPos[i];
				enPos[i] = static_cast<int>(sqrt(tmp.x * tmp.x) + sqrt(tmp.y * tmp.y));
			}
		}
		//---------óDêÊìxÇê›íË-------------
		for (int i = 1; i < 4; i++)
		{
			if (enPos[nearP] != -1)
			{
				if (enPos[i] < enPos[nearP] && enPos[i] != -1)
				{
					nearP = i;
				}
			}
		}
		for (int e = 0; e < 12; e++)
		{
			if (passFlag[e])
			{
				VECTOR2 exPos = { plPos[nearP].x - checkPos[e].x ,plPos[nearP].y - checkPos[e].y };
				comPos[e] = static_cast<int>(sqrt(exPos.x*exPos.x) + sqrt(exPos.y * exPos.y));
			}
		}
		// ëÊàÍÅAëÊìÒï™äÚì_Ç‹Ç≈ÇÃDIRÇåàíË
		for (int e = 1; e < 12; e++)
		{
			if (comPos[e] < comPos[actNum])
			{
				actNum = e;
			}
		}
		action = ENEM_ACT::TRA;
		return;
	}
	//-----------à⁄ìÆ-------------
	if (action == ENEM_ACT::TRA)
	{
		int tmpAct = actNum % 4;
		movePos = 0;
		switch (tmpAct)
		{
		case 0:
		case 3:
			if ((*PosTbl[tmpAct][TBL_MAIN]) != checkPos[actNum].y)
			{
				if (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, static_cast<DIR>(tmpAct), SpeedTbl[Enemy::dir][0], -hitRad.x)))]
					&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, static_cast<DIR>(tmpAct), SpeedTbl[Enemy::dir][0], hitRad.x - 1)))]
					&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, static_cast<DIR>(tmpAct), SpeedTbl[Enemy::dir][0], 0)))])
				{
					(*PosTbl[tmpAct][TBL_MAIN]) += SpeedTbl[tmpAct][0];
					movePos += SpeedTbl[tmpAct][0];
				}
			}
			else
			{
				if (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, dirOpp[tmpAct][actNum / 4], SpeedTbl[Enemy::dir][0], -hitRad.x)))]
					&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, dirOpp[tmpAct][actNum / 4], SpeedTbl[Enemy::dir][0], hitRad.x - 1)))]
					&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, dirOpp[tmpAct][actNum / 4], SpeedTbl[Enemy::dir][0], 0)))])
				{
					(*PosTbl[tmpAct][TBL_OPP]) += SpeedTbl[dirOpp[tmpAct][actNum / 4]][0];
					movePos += SpeedTbl[dirOpp[tmpAct][actNum / 4]][0];
				}
				if ((*PosTbl[tmpAct][TBL_OPP]) == checkPos[actNum].x)
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
				if (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, static_cast<DIR>(tmpAct), SpeedTbl[Enemy::dir][0], -hitRad.x)))]
					&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, static_cast<DIR>(tmpAct), SpeedTbl[Enemy::dir][0], hitRad.x - 1)))]
					&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, static_cast<DIR>(tmpAct), SpeedTbl[Enemy::dir][0], 0)))])
				{
					(*PosTbl[tmpAct][TBL_MAIN]) += SpeedTbl[tmpAct][0];
					movePos += SpeedTbl[tmpAct][0];
				}
			}
			else
			{
				if (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, dirOpp[tmpAct][actNum / 4], SpeedTbl[Enemy::dir][0], -hitRad.x)))]
					&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, dirOpp[tmpAct][actNum / 4], SpeedTbl[Enemy::dir][0], hitRad.x - 1)))]
					&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, dirOpp[tmpAct][actNum / 4], SpeedTbl[Enemy::dir][0], 0)))])
				{
					(*PosTbl[tmpAct][TBL_OPP]) += SpeedTbl[dirOpp[tmpAct][actNum / 4]][0];
					movePos += SpeedTbl[dirOpp[tmpAct][actNum / 4]][0];
				}
				if ((*PosTbl[tmpAct][TBL_OPP]) == plPos[nearP].y)
				{
					action = ENEM_ACT::SERCH;
					return;
				}
			}
			break;
		default :
			break;
		}
	}
	//---------à⁄ìÆÇÇµÇƒÇ¢Ç»Ç©Ç¡ÇΩèÍçáçƒìxï˚å¸ÇåàÇﬂÇÈ-------------
	if (movePos == 0)
	{
		action = ENEM_ACT::SERCH;
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

void Enemy::SpMove(const GameCtrl & controller)
{
	auto &chipSize = lpStageMng.GetChipSize().x;

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
		if (!mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Enemy::dir, SpeedTbl[Enemy::dir][0], -hitRad.x)))]
			|| !mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Enemy::dir, SpeedTbl[Enemy::dir][0], hitRad.x - 1)))])
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

void Enemy::Escape(const GameCtrl & controller)
{
	auto &chipSize = lpStageMng.GetChipSize().x;

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
		if (!mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Enemy::dir, SpeedTbl[Enemy::dir][0], -hitRad.x)))]
			|| !mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Enemy::dir, SpeedTbl[Enemy::dir][0], hitRad.x - 1)))])
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

void Enemy::Teleport(const GameCtrl & controller)
{
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
