#include <DxLib.h>
#include <math.h>
#include "Player.h"
#include "Weapon.h"
#include "Effect.h"
#include "StageMng.h"
#include "InfoCtrl.h"
#include "MapCtrl.h"
#include "ImageMng.h"
#include "BaseScene.h"

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

	param = { -100,
			   PL_LIFE_MAX,
			  -(state.Power - 1),
			  -state.Guard,
			  -state.Inv
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
		VECTOR2(0, hitRad.y * 2),
		VECTOR2(-hitRad.x * 2, 0),
		VECTOR2(hitRad.x * 2, 0),
		VECTOR2(0, -hitRad.y * 2)
	};

	this->plNum = plNum;

	Init("image/playerAll.png", VECTOR2(1040 / 13, 840 / 7), VECTOR2(13, 7), setUpPos);

	startPos = pos;
	score = 0;
	oldScore = score;

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
	AddAnim("���S", 12, 0, 7, 7, false);
	return true;
}

void Player::PlInit(void)
{
	speed = PL_DEF_SPEED;
	life = PL_LIFE_MAX;
	state = { 1,0,0 };
	upTime = { 0,0 };
	invTime = 0;
	bonus = 0;
	additionTime = 8;
	randomBonus = GetRand(4);

	damageFlag = false;
	damageCnt = 0;
	deathInv = 0;
	reStartCnt = 0U;
	visible = true;

	afterKeyFlag = false;

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
		GetItem(objList);
	}
	invTime = state.Inv;

	auto &chipSize = lpStageMng.GetChipSize().x;

	(this->*_updater)(controller, objList);

	// ���Ԍo�߂ɂ��X�e�[�^�X�ύX
	// �U��
	if (state.Power >= 2)
	{
		upTime[0]++;
	}
	if (upTime[0] > 600)
	{
		SetData(DATA_POWER, -1);
		upTime[0] -= 600;
	}
	// �h��
	if (state.Guard >= 1)
	{
		upTime[1]++;
	}
	if (upTime[1] > 600)
	{
		SetData(DATA_GUARD, - state.Guard);
		upTime[1] -= 600;
	}
	// ���G
	if (invTime > 0)
	{
		SetData(DATA_INV, -1);
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

void Player::GetItem(weakListObj objList)
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
			SetData(DATA_POWER, 1); 
			AddObjList()(objList,std::make_unique<Effect>("image/aura_RED6.efk", pos + VECTOR2(0, 40), 600, scrollOffset, drawOffset + VECTOR2(0, -20)));
			break;
		case MAP_ID::POTION_2:	// ��
			paramUP(NotFlag, num);
			SetData(DATA_GUARD, 1);
			break;
		case MAP_ID::POTION_3:	// ��
			paramUP(NotFlag, num);
			SetData(DATA_LIFE, 2);
			break;
		case MAP_ID::POTION_4:	// ��
			paramUP(NotFlag, num);
			SetData(DATA_INV, 180);
			break;
		case MAP_ID::COIN_1:	// ��
			paramUP(NotFlag, num);
			SetData(DATA_SCORE, 2);
			break;
		case MAP_ID::COIN_2:	// ��
			paramUP(NotFlag, num);
			SetData(DATA_SCORE, 3);
			break;
		case MAP_ID::COIN_3:	// ��
			paramUP(NotFlag, num);
			SetData(DATA_SCORE, 4);
			break;
		case MAP_ID::COIN_4:	// ��
			paramUP(NotFlag, num);
			SetData(DATA_SCORE, 5);
			break;
		case MAP_ID::KEY_1:
			paramUP(NotFlag, num);
			break;
		case MAP_ID::KEY_2:
			paramUP(NotFlag, num);
			break;
		case MAP_ID::MEAT:
			paramUP(NotFlag, num);
			SetData(DATA_LIFE, 4);
			break;
		case MAP_ID::SWORD:
			paramUP(NotFlag, num);
			SetData(DATA_SCORE, 2);
			if (randomBonus == 0)
			{
				SetData(DATA_BONUS, 1);
			}
			break;
		case MAP_ID::SHIELD:
			paramUP(NotFlag, num);
			SetData(DATA_SCORE, 2);
			if (randomBonus == 1)
			{
				SetData(DATA_BONUS, 1);
			}
			break;
		case MAP_ID::BOOK:
			paramUP(NotFlag, num);
			SetData(DATA_SCORE, 2);
			if (randomBonus == 2)
			{
				SetData(DATA_BONUS, 1);
			}
			break;
		case MAP_ID::GOLD:
			paramUP(NotFlag, num);
			SetData(DATA_SCORE, 2);
			if (randomBonus == 3)
			{
				SetData(DATA_BONUS, 1);
			}
			break;
		case MAP_ID::DIA:
			paramUP(NotFlag, num);
			SetData(DATA_SCORE, 2);
			if (randomBonus == 4)
			{
				SetData(DATA_BONUS, 1);
			}
			break;
	default:
		break;
	}
}

void Player::SetData(SCORE_DATA data, int val)
{
	switch (data)
	{
	case DATA_SCORE:
		score += val;
		if (score < 0)
		{
			score = 0;
		}
		if (score >= 10000)
		{
			score = 10000;
		}
		break;
	case DATA_LIFE:
		life = (life + val >= PL_LIFE_MAX ? PL_LIFE_MAX : life + val);
		break;
	case DATA_POWER:
		state.Power += val;
		if (state.Power > 3)
		{
			state.Power = 3;
		}
		break;
	case DATA_GUARD:
		state.Guard += val;
		if (state.Guard > 3)
		{
			state.Guard = 3;
		}
		break;
	case DATA_INV:
		state.Inv += val;
		break;
	case DATA_BONUS:
		bonus += val;
		break;
	}
	lpInfoCtrl.SetScore(score, static_cast<int>(plNum));
	lpInfoCtrl.SetBonus(bonus, static_cast<int>(plNum));
}

void Player::Draw(void)
{
	Obj::Draw();
	StateDraw();
}

void Player::StateDraw(void)
{
	additionTime--;
	if (oldScore < score)
	{
		if (additionTime <= 0)
		{
			oldScore++;
			additionTime = 8;
		}
	}
	/*DrawBox(640, 0, 800, 300, GetColor(255, 255, 0), true);
	DrawFormatString(650, 0, GetColor(0, 0, 0), "SCORE");*/
	DrawGraph(645, 20, IMAGE_ID("image/score.png")[0], true);
	DrawFormatString(650, 150, GetColor(255, 255, 0), "LIFE  : %d", life);
	DrawFormatString(650, 200, GetColor(255, 255, 0), "POWER  : %d", state.Power);
	DrawFormatString(650, 220, GetColor(255, 255, 0), "GUARD  : %d", state.Guard);
	DrawFormatString(650, 240, GetColor(255, 255, 0), "INV  : %d", state.Inv);
	DrawFormatString(650, 260, GetColor(255, 255, 0), "BONUS  : %d", bonus);

	digit = 0;
	numTemp = (oldScore * 10);
	if (numTemp == 0)
	{
		DrawGraph((GAME_SCREEN_SIZE_X / 2 - 30) * (plNum % 2 + 1) - 22, 60, lpImageMng.GetID("image/number.png", VECTOR2(40, 30), VECTOR2(10, 1))[0], true);
	}
	while (numTemp > 0)
	{
		DrawGraph((GAME_SCREEN_SIZE_X / 2 - 30) * (plNum % 2 + 1) - (digit + 1) * 22, 60, lpImageMng.GetID("image/number.png", VECTOR2(40, 30), VECTOR2(10, 1))[numTemp % 10], true);
		numTemp /= 10;
		digit++;
	}
}

void Player::Stop(const GameCtrl & controller, weakListObj objList)
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
//		AddObjList()(objList, std::make_unique<Weapon>(WEP_KNIFE, dir, pos, scrollOffset, drawOffset));
		AddObjList()(objList, std::make_unique<Effect>("image/�a��_1.efk", pos + VECTOR2(0, 40), 33, scrollOffset, drawOffset + VECTOR2(0, -20)));
		_updater = &Player::Attack;
	}
}

void Player::Move(const GameCtrl & controller, weakListObj objList)
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
//		AddObjList()(objList, std::make_unique<Weapon>(WEP_KNIFE, dir, pos, scrollOffset, drawOffset - VECTOR2()));
		AddObjList()(objList, std::make_unique<Effect>("image/�a��_1.efk", pos + VECTOR2(0, 40), 33, scrollOffset, drawOffset + VECTOR2(0, -20)));
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

			if (!mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Player::dir, SpeedTbl[Player::dir][inputTbl[plNum][XINPUT_RUN_RB]], -hitRad.x + 2)))]
			 || !mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Player::dir, SpeedTbl[Player::dir][inputTbl[plNum][XINPUT_RUN_RB]],  hitRad.x - 3 /*(��:- 1 - 2)*/)))])
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

void Player::Attack(const GameCtrl & controller, weakListObj objList)
{
	reStartCnt -= (reStartCnt > 0);		// �^�̏ꍇ��1���Ă��猸�炷
	visible = true;
	if ((reStartCnt / 3) % 2)
	{
		visible = false;
	}

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
					lpInfoCtrl.SetEnemyFlag(true, i);
				}
			}
		}
		return;
	}
	// ��Ұ��݂��I������猳�ɖ߂�
	_updater = &Player::Move;
}

void Player::Damage(const GameCtrl & controller, weakListObj objList)
{
	auto &inputTbl = controller.GetInputState(KEY_TYPE_NOW);

	auto DeathPrc = [this]()
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
	};

	if (reStartCnt)
	{
		_updater = &Player::Move;
	}

	// ���S����
	if (life  < 1)
	{
		if (DeathPrc())
		{
			// ؽ�߰ݏ���
			pos = startPos;
			SetData(DATA_SCORE, - 1);
			oldScore = score;
			InitScroll(static_cast<int>(plNum));
			PlInit();
			reStartCnt = PL_RESTART_CNT;
		}
		deathInv++;
		return;
	}

	if (damageCnt)
	{
		if (damageCnt % 4 == 0)
		{
			DIR tmp = DirTbl[dir][DIR_TBL_REV];
			int speed = SpeedTbl[tmp][inputTbl[plNum][0]] / 2 * -3 * (10 - damageCnt / 4);
			if (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmp, -speed,  -hitRad.x + 1)))]
			&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmp, -speed, hitRad.x - 2)))])
			{
				// �ړ��s�̃I�u�W�F�N�g�����ɂȂ��ꍇ
				(*PosTbl[tmp][TBL_MAIN]) += -speed;
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
			if (damageCnt / 8 % 2 == 0)
			{
				visible = false;
			}
			if(damageCnt / 8 % 2)
			{
				visible = true;
			}
		}
		if (damageCnt >= 40)
		{
			damageCnt = 0;
			
			// ��Ұ�ޱ�Ұ��݂��I�������J��(�\��)
			damageFlag = false;
			_updater = &Player::Move;
			visible = true;
			state.Inv = 120;
			return;
		}
		damageCnt++;
		return;
	}
	else
	{
		SetData(DATA_LIFE, -1);
		damageCnt++;
		return;
	}
}