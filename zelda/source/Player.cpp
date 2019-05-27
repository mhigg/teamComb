#include <DxLib.h>
#include <math.h>
#include "Player.h"
#include "StageMng.h"
#include "InfoCtrl.h"
#include "MapCtrl.h"


Player::Player(PL_NUMBER plNum, VECTOR2 setUpPos, VECTOR2 drawOffset):Obj(drawOffset)
{
	hitRad = VECTOR2(20, 20);
	actOff = VECTOR2(40, 100);
	keyIdTbl = { XINPUT_DOWN,	// ��
				 XINPUT_LEFT,	// ��
				 XINPUT_RIGHT,	// �E
				 XINPUT_UP		// ��
				};

	PosTbl = {  &pos.y,&pos.x,	// ��
				&pos.x,&pos.y,	// ��
				&pos.x,&pos.y,	// �E
				&pos.y,&pos.x	// ��
			 };
	
	SpeedTbl = { PL_DEF_SPEED,  PL_DASH_SPEED,	// ��
				-PL_DEF_SPEED, -PL_DASH_SPEED,	// ��
				 PL_DEF_SPEED,  PL_DASH_SPEED,	// �E
				-PL_DEF_SPEED, -PL_DASH_SPEED	// ��
			   };

	//			MAIN		REV		OPP1	  OPP2
	DirTbl = { DIR_DOWN ,DIR_UP   ,DIR_LEFT ,DIR_RIGHT,	// ��(REV:��)(���E�E)
			   DIR_LEFT ,DIR_RIGHT,DIR_DOWN ,DIR_UP,	// ��(REV:�E)(��E��)
			   DIR_RIGHT,DIR_LEFT ,DIR_DOWN ,DIR_UP,	// �E(REV:��)(��E��)
			   DIR_UP   ,DIR_DOWN ,DIR_LEFT ,DIR_RIGHT	// ��(REV:��)(���E�E)
			  };
	param =
	{
		 -100
		,PL_LIFE_MAX
		,-(state.Power - 1)
		, -state.Guard
		, -state.Inv
	};
	mapMoveTbl = {
					true,		// NONE
					false,		// WALL1
					false,		// WALL2
					false,		// WALL3
					false,		// WALL4
					false,		// WALL5
					false,		// WALL6
					false,		// WALL7
					false,		// WALL8
					false,		// WALL9
					true,		// WALL10
					true,		// WALL11
					false,		// WALL12
					false,		// WALL13
					false,		// WALL14
					false,		// WALL15
					false,		// WALL16
					false,		// WALL17
					false,		// WALL18
					false,		// WALL19		// GetMapData�̌Œ�ID
					false,		// WALL20
					false,		// WALL21				
					false,		// WALL22
					false,		// WALL23
					false,		// WALL24
					false,		// WALL25
					false,		// WALL26
					false,		// WALL27
					false,		// WALL28
					false,		// WALL29
					false,		// WALL30
					false,		// WALL31
					false,		// WALL32
					false,		// WALL33
					false,		// WALL34
					false,		// WALL35
					false,		// WALL36
					false,		// WALL37	
					false,		// WALL38	
					true,		// WALL39	
					false,		// DOOR1
					false,		// DOOR2
					false,		// DOOR3
					false,		// DOOR4
					true,		// POTION_1
					true,		// POTION_2
					true,		// POTION_3
					true,		// POTION_4
					true,		// COIN_1
					true,		// COIN_2
					true,		// COIN_3
					true,		// COIN_4
					true,		// KEY_1
					true,		// KEY_2
					true,		// MEAT
					true,		// PLAYER
					true,		// ENEMY
					true,		// SWORD
					true,		// SHIELD
					true,		// BOOK
					true,		// GOLD
					true,		// DIA
					false,		// BOX_1		// ��
					false,		// BOX_2		// �󂢂Ă����
					true,		// MOTH_1		// ���
					false,		// MOTH_2		// ��ꂽ���
					true,		// MOTH_3		// �M
					false,		// MOTH_4		// ��ꂽ�M
					false,		// TREE_1		// ��
					false,		// TREE_2
					false,		// TREE_3
					false,		// TREE_4
					false,		// HOLL_1		// ���
					false,		// HOLL_2
					false,		// HOLL_3
					false,		// HOLL_4
					false,		// STONE_1	// ��
					false,		// STONE_2
					false,		// STONE_3
					false,		// STONE_4				
	};
	actAdd = {
		VECTOR2(0					,	hitRad.y * 2	),
		VECTOR2(-hitRad.x * 2	,	0					),		
		VECTOR2(hitRad.x * 2	,	0					),
		VECTOR2(0					,	-hitRad.y * 2	)
	};

	this->plNum = plNum;

	Init("image/playerAll.png", VECTOR2(1040 / 13, 840 / 7), VECTOR2(13, 7), setUpPos);
	startPos = pos;

	InitScroll(static_cast<int>(plNum));
	initAnim();
	PlInit();
}

Player::Player()
{
}


Player::~Player()
{
}

bool Player::initAnim(void)
{
	AddAnim("��~", 0, 0, 1, 6, true);
	AddAnim("�ړ�", 0, 1, 6, 8, true);
	AddAnim("����", 4, 1, 6, 6, true);
	AddAnim("�U��", 8, 1, 6, 3, false);
	AddAnim("���S", 12, 0, 7, 7, false);	// false�ű�Ұ��݂�ٰ�߂����Ȃ�
	return true;
}

void Player::PlInit(void)
{
	speed = PL_DEF_SPEED;
	life = PL_LIFE_MAX;

	state.Power = 1;
	state.Guard = 0;
	state.Inv = 0;
	score = 0;
	randomBonus = GetRand(4);
	damageFlag = false;

	upTime = {
		0,0
	};
	invTime = 0;
	damaCnt = 0;
	deathInv = 0;
	reStartCnt = 0U;
	afterKeyFlag = false;
	visible = true;
	lpInfoCtrl.SetAddScroll(scrollOffset, static_cast<int>(plNum));
	lpInfoCtrl.SetPlayerPos(pos, static_cast<int>(plNum));
	_updater = &Player::Move;				// ������Ԃ�Move���
}

VECTOR2 Player::sidePos(VECTOR2 pos, DIR dir, int speed, int sideNum)
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

void Player::SetMove(const GameCtrl & controller, weakListObj objList)
{
	lpInfoCtrl.SetPlayerFlag(true, static_cast<int>(plNum));
	lpInfoCtrl.SetPlayerPos(pos,static_cast<int>(plNum));
	if (!damageFlag)
	{
		GetItem();
	}
	invTime = state.Inv;

	auto &chipSize = lpStageMng.GetChipSize().x;

	(this->*_updater)(controller);

	// ���Ԍo�߂ɂ��X�e�[�^�X�ύX
	// �U��
	if (state.Power >= 2)
	{
		upTime[0]++;
	}
	if (upTime[0] / 600 == 1)
	{
		lpScoreBoard.SetScore(DATA_POWER, -1);
		upTime[0] -= 600;
	}
	// �h��
	if (state.Guard >= 1)
	{
		upTime[1]++;
	}
	if (upTime[1] > 600)
	{
		lpScoreBoard.SetScore(DATA_GUARD, - state.Guard);
		upTime[1] -= 600;
	}
	// ���G
	if (invTime > 0)
	{
		lpScoreBoard.SetScore(DATA_INV, -1);
	}
	else
	{
		invTime = 0;
	}
}

bool Player::CheckObjType(OBJ_TYPE type)
{
	return (type == OBJ_PLAYER);
}

bool Player::DeathPrc(void)
{
	if (animEndFlag)
	{
		if (deathInv >= 80)
		{
			return true;
		}
	}
	dir = DIR_DOWN;
	SetAnim("���S");
	return false;
}

void Player::GetItem(void)
{
	auto ItemID = [=] {
		auto id = lpMapCtrl.GetItemData(pos);
		return (id == MAP_ID::MAX ? static_cast<MAP_ID>(ITEM_ID_START): id);
	};

	auto paramUP = [=](auto& paramFlag, auto limNum) {
		paramFlag += (paramFlag < limNum);
		lpMapCtrl.SetItemData(pos, MAP_ID::NONE);
	};

	unsigned int num = 1;
	
	switch (ItemID())
	{
		case MAP_ID::POTION_1:	// ��
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_POWER, 1);
			break;
		case MAP_ID::POTION_2:	// ��
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_GUARD, 1);
			break;
		case MAP_ID::POTION_3:	// ��
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_LIFE, 2);
			break;
		case MAP_ID::POTION_4:	// ��
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_INV, 180);
			break;
		case MAP_ID::COIN_1:	// ��
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_SCORE, 2);
			break;
		case MAP_ID::COIN_2:	// ��
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_SCORE, 3);
			break;
		case MAP_ID::COIN_3:	// ��
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_SCORE, 4);
			break;
		case MAP_ID::COIN_4:	// ��
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_SCORE, 5);
			break;
		case MAP_ID::KEY_1:
			paramUP(NotFlag, num);
			break;
		case MAP_ID::KEY_2:
			paramUP(NotFlag, num);
			break;
		case MAP_ID::MEAT:
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_LIFE, 4);
			break;
		case MAP_ID::SWORD:
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_SCORE, 2);
			if (randomBonus == 0)
			{
				lpScoreBoard.SetScore(DATA_BONUS, 1);
			}
			break;
		case MAP_ID::SHIELD:
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_SCORE, 2);
			if (randomBonus == 1)
			{
				lpScoreBoard.SetScore(DATA_BONUS, 1);
			}
			break;
		case MAP_ID::BOOK:
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_SCORE, 2);
			if (randomBonus == 2)
			{
				lpScoreBoard.SetScore(DATA_BONUS, 1);
			}
			break;
		case MAP_ID::GOLD:
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_SCORE, 2);
			if (randomBonus == 3)
			{
				lpScoreBoard.SetScore(DATA_BONUS, 1);
			}
			break;
		case MAP_ID::DIA:
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_SCORE, 2);
			if (randomBonus == 4)
			{
				lpScoreBoard.SetScore(DATA_BONUS, 1);
			}
			break;
	default:
		break;
	}

	state.Power = lpScoreBoard.GetScore(DATA_POWER);
	state.Guard = lpScoreBoard.GetScore(DATA_GUARD);
	state.Inv = lpScoreBoard.GetScore(DATA_INV);
}

void Player::Stop(const GameCtrl & controller)
{
	auto &inputTbl = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputTblOld = controller.GetInputState(KEY_TYPE_OLD);

	_updater = &Player::Move;

	// ��ڲ԰����Ұ�ގ�(���ޯ�ޗp)
	if (inputTbl[plNum][XINPUT_MAP] & (!inputTblOld[plNum][XINPUT_MAP]))
	{
		SetAnim("��~");
		_updater = &Player::Damage;
	}

	if (inputTbl[plNum][XINPUT_ATT] & (!inputTblOld[plNum][XINPUT_ATT]))
	{
		SetAnim("�U��");
		_updater = &Player::Attack;
	}
}

void Player::Move(const GameCtrl & controller)
{
	auto &inputTbl = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputTblOld = controller.GetInputState(KEY_TYPE_OLD);

	reStartCnt -= (reStartCnt > 0);		// �^�̏ꍇ��1���Ă��猸�炷
	visible = true;
	if ((reStartCnt / 3) % 2)
	{
		visible = false;
	}

	// ��ڲ԰����Ұ�ގ�(���ޯ�ޗp)
	if (inputTbl[plNum][XINPUT_MAP] & (!inputTblOld[plNum][XINPUT_MAP]))
	{
		damageFlag = true;
		SetAnim("��~");
		return;
	}

	if (inputTbl[plNum][XINPUT_ATT] & (!inputTblOld[plNum][XINPUT_ATT]))
	{
		SetAnim("�U��");
		_updater = &Player::Attack;
		return;
	}

//--------- �G�ɓ����������̏��� ----------
	if (state.Inv == 0)
	{
		for (int i = 0; (i < ENEMY_MAX) && (damageFlag == false); i++)
		{
			VECTOR2 ePos = lpInfoCtrl.GetEnemyPos(i);
			if (ePos != VECTOR2(-1, -1))
			{
				VECTOR2 tmp = { ePos - pos };
				if (tmp.x * tmp.x + tmp.y * tmp.y <= 2500)
				{
					// �������Ă�Ƃ�
					damageFlag = true;
				}
			}
		}
	}

	if (damageFlag)
	{
		if (!reStartCnt)
		{
			SetAnim("��~");
			_updater = &Player::Damage;
		}
		damageFlag = false;
		return;
	}
// ----------------------------------------

	auto Move = [&, dir = Player::dir](DIR_TBL_ID id){
		if (inputTbl[plNum][keyIdTbl[DirTbl[dir][id]]])
		{
			Player::dir = DirTbl[dir][id];		// �����̾��

			if (!mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Player::dir, SpeedTbl[Player::dir][inputTbl[plNum][XINPUT_RUN_RB]], -hitRad.x)))]
				|| !mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Player::dir, SpeedTbl[Player::dir][inputTbl[plNum][XINPUT_RUN_RB]], hitRad.x - 1)))])
			{
				Player::dir = DirTbl[dir][id];
				// �ړ��s�̃I�u�W�F�N�g���ׂɂ������ꍇ
				return false;
			}

			// �ړ�����-----------------------------
			// �ύX���������W�̕ϐ��A�h���X += �ړ���
			(*PosTbl[Player::dir][TBL_MAIN]) += SpeedTbl[Player::dir][inputTbl[plNum][XINPUT_RUN_RB]];

			if ((pos.x >= SCROLL_AREA_X) && (pos.x <= (SCROLL_END_X)))
			{
				scrollOffset.x = pos.x - SCROLL_AREA_X;
				lpMapCtrl.AddScroll(scrollOffset, static_cast<int>(plNum));
			}
			if ((pos.y >= SCROLL_AREA_Y) && (pos.y <= (SCROLL_END_Y)))
			{
				scrollOffset.y = pos.y - SCROLL_AREA_Y;
				lpMapCtrl.AddScroll(scrollOffset, static_cast<int>(plNum));
			}
			lpInfoCtrl.SetAddScroll(scrollOffset, static_cast<int>(plNum));
			return true;
		}
		return false;
	};

	// ��key����------------------------------------
	if (!(Move(static_cast<DIR_TBL_ID>(DIR_TBL_OPP1 - (afterKeyFlag << 1)))		// OPP1,OPP2�Ɉړ����Ȃ������ꍇ
		|| Move(static_cast<DIR_TBL_ID>(DIR_TBL_OPP2 - (afterKeyFlag << 1)))))	// (key���͂��Ȃ������ꍇ)
	{
		afterKeyFlag = false;
		if (!(Move(static_cast<DIR_TBL_ID>(DIR_TBL_MAIN + (afterKeyFlag << 1)))	// MAIN,REV�Ɉړ����Ȃ������ꍇ
			|| Move(static_cast<DIR_TBL_ID>(DIR_TBL_REV + (afterKeyFlag << 1)))))// (key���͂��Ȃ������ꍇ)
		{
			SetAnim("��~");
			return;
		}
	}
	else
	{
		// OPP1��������OPP2��key���͂��������ꍇ�̏��
		afterKeyFlag = static_cast<bool>(inputTbl[plNum][keyIdTbl[DirTbl[dir][DIR_TBL_OPP1]]]);
		afterKeyFlag |= static_cast<bool>(inputTbl[plNum][keyIdTbl[DirTbl[dir][DIR_TBL_OPP2]]]);
		afterKeyFlag ^= static_cast<int>(GetAnim() == "��~");
	}
	// ��ڲ԰�������Ă���Ƃ��͎�����Ұ��݂ɂ���
	if (inputTbl[plNum][XINPUT_RUN_RB])
	{
		SetAnim("����");
		return;
	}
	SetAnim("�ړ�");
}

void Player::Attack(const GameCtrl & controller)
{
	if (!animEndFlag)
	{
		// �U������
		VECTOR2 actPos = pos + actAdd[Player::dir];
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			VECTOR2 ePos = lpInfoCtrl.GetEnemyPos(i);
			if (ePos != VECTOR2(-1, -1))
			{
				VECTOR2 tmp = { ePos - actPos };
				if (sqrt(tmp.x * tmp.x) + sqrt(tmp.y * tmp.y) <= 40)
				{
					// �������Ă�Ƃ�
					lpInfoCtrl.SetEnemyFlag(false, i);
				}
			}
		}
		return;
	}
	// ��Ұ��݂��I������猳�ɖ߂�
	_updater = &Player::Move;
}

void Player::Damage(const GameCtrl & controller)
{
	auto &inputTbl = controller.GetInputState(KEY_TYPE_NOW);

	if (reStartCnt)
	{
		_updater = &Player::Move;
	}

	// ���S����
	if (lpScoreBoard.GetScore(DATA_LIFE) < 1)
	{
		if (DeathPrc())
		{
			// ؽ�߰ݏ���
			pos = startPos;
			lpScoreBoard.SetScore(DATA_LIFE, PL_LIFE_MAX);
			lpScoreBoard.SetScore(DATA_SCORE, - 1);
			lpScoreBoard.SetScore(DATA_POWER, - (state.Power - 1));
			lpScoreBoard.SetScore(DATA_GUARD, -(state.Guard - 1));
			InitScroll(static_cast<int>(plNum));
			PlInit();
			reStartCnt = PL_RESTART_CNT;
		}
		deathInv++;
		return;
	}

	if (damaCnt)
	{
		if (damaCnt % 5 == 0)
		{
			DIR tmp = static_cast < DIR>(3 - Player::dir);
			if (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmp, SpeedTbl[tmp][inputTbl[plNum][0]] / 2 * 6, hitRad.x - 2)))]
				&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmp, SpeedTbl[tmp][inputTbl[plNum][0]] / 2 * 6, -hitRad.x + 2)))])
			{
				// �ړ��s�̃I�u�W�F�N�g���ׂɂȂ��ꍇ
				(*PosTbl[Player::dir][TBL_MAIN]) -= SpeedTbl[Player::dir][inputTbl[plNum][0]] / 2 * 6;
				if ((pos.x >= SCROLL_AREA_X) && (pos.x <= (SCROLL_END_X)))
				{
					scrollOffset.x = pos.x - SCROLL_AREA_X;
					lpMapCtrl.AddScroll(scrollOffset, static_cast<int>(plNum));
				}
				if ((pos.y >= SCROLL_AREA_Y) && (pos.y <= (SCROLL_END_Y)))
				{
					scrollOffset.y = pos.y - SCROLL_AREA_Y;
					lpMapCtrl.AddScroll(scrollOffset, static_cast<int>(plNum));
				}
				lpInfoCtrl.SetAddScroll(scrollOffset, static_cast<int>(plNum));
			}
			if (damaCnt / 10 % 2 == 0)
			{
				visible = false;
			}
			if(damaCnt / 10% 2)
			{
				visible = true;
			}
		}
		if (damaCnt >= 60)
		{
			damaCnt = 0;
			
			// ��Ұ�ޱ�Ұ��݂��I�������J��(�\��)
			damageFlag = false;
			_updater = &Player::Move;
			visible = true;
			return;
		}
		damaCnt++;
		return;
	}
	else
	{
		lpScoreBoard.SetScore(DATA_LIFE, -1);
		damaCnt++;
		return;
	}
}