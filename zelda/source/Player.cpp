#include <DxLib.h>
#include "Player.h"
#include "StageMng.h"
#include "MapCtrl.h"


Player::Player(PL_NUMBER plNum, VECTOR2 setUpPos, VECTOR2 drawOffset):Obj(drawOffset)
{
	pos = { 0,0 };
	speed = PL_DEF_SPEED;
	life = 5;

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
					true,	// WALL19	// GetMapData�̌Œ�ID
					true,	// WALL20
					true,	// WALL21				�Ƃ���
					false,	// WALL22
					false,	// WALL23
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
					false,	// ENEMY
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

	this->plNum = plNum;

	Init("image/ghost.png", VECTOR2(40,40), VECTOR2(1,1), setUpPos);
	Init("image/playerRun.png", VECTOR2(80, 120), VECTOR2(4, 7), setUpPos);
	startPos = pos;
	initAnim();

	afterKeyFlag = false;
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
	AddAnim("�ړ�", 0, 1, 6, 2, true);
	AddAnim("����", 0, 1, 6, 1, true);
	AddAnim("���S", 4, 0, 4, 8, false);	// false�ű�Ұ��݂�ٰ�߂����Ȃ�
	return true;
}

void Player::SetMove(const GameCtrl & controller, weakListObj objList)
{
	GetItem();

	auto &inputTbl = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputTblOld = controller.GetInputState(KEY_TYPE_OLD);
	auto &chipSize = lpStageMng.GetChipSize().x;

	// ��ڲ԰����Ұ�ގ�(���ޯ��p)
	if (controller.GetCtrl(KEY_TYPE_NOW)[KEY_INPUT_F] & (~controller.GetCtrl(KEY_TYPE_OLD)[KEY_INPUT_F]))
	{
		life -= 1;
	}
	if (DeathPrc())
	{
		pos = startPos;		// ؽ�߰ݏ���
		life = 5;
	}

	auto sidePos = [&](VECTOR2 pos, DIR dir, int speed, SIDE_CHECK sideFlag) {
		VECTOR2 side;
		offset = 20;
		switch (dir)
		{
		case DIR_DOWN:
			side = { 0,(offset + chipSize - sideFlag) + speed };
			break;
		case DIR_LEFT:
			side = { speed - (sideFlag ^ 1) + offset,0 };
			break;
		case DIR_RIGHT:
			side = { (offset + chipSize - sideFlag) + speed,0 };
			break;
		case DIR_UP:
			side = { 0,speed - (sideFlag ^ 1) };
			break;
		default:
			break;
		}
		return pos + side;
	};

	auto Move = [&, dir = Player::dir](DIR_TBL_ID id){
		if (inputTbl[plNum][keyIdTbl[DirTbl[dir][id]]])
		{
			Player::dir = DirTbl[dir][id];		// �����̾��

			if (!mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Player::dir, SpeedTbl[Player::dir][inputTbl[plNum][XINPUT_RUN_RB]], IN_SIDE),MAP_ID::WALL19))])
			{
				Player::dir = DirTbl[dir][id];
				// �ړ��s�̃I�u�W�F�N�g���ׂɂ������ꍇ
				return false;
			}

			// �ړ�����-----------------------------
			// �ύX���������W�̕ϐ��A�h���X += �ړ���
			(*PosTbl[Player::dir][TBL_MAIN]) += SpeedTbl[Player::dir][inputTbl[plNum][XINPUT_RUN_RB]];
//			scrollOffset += 
			return true;
		}
		return false;
	};

	// ��key����------------------------------------
	if (!(Move(static_cast<DIR_TBL_ID>(DIR_TBL_OPP1 - (afterKeyFlag << 1)))		// OPP1,OPP2�Ɉړ����Ȃ������ꍇ
	 ||   Move(static_cast<DIR_TBL_ID>(DIR_TBL_OPP2 - (afterKeyFlag << 1)))))	// (key���͂��Ȃ������ꍇ)
	{
		afterKeyFlag = false;
		if (!(Move(static_cast<DIR_TBL_ID>(DIR_TBL_MAIN + (afterKeyFlag << 1)))	// MAIN,REV�Ɉړ����Ȃ������ꍇ
		 ||   Move(static_cast<DIR_TBL_ID>(DIR_TBL_REV  + (afterKeyFlag << 1)))))// (key���͂��Ȃ������ꍇ)
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

bool Player::CheckObjType(OBJ_TYPE type)
{
	return (type == OBJ_PLAYER);

}

bool Player::DeathPrc(void)
{
	if (life < 0)
	{
		/*SetAnim("���S");*/
		return true;
	}
	return false;
}

void Player::GetItem(void)
{
	//auto ItemID = [=] {
	//	auto id = lpMapCtrl.GetMapData(pos, MAP_ID::WALL19);
	//	return (id == MAP_ID::MEAT ? static_cast<MAP_ID>(ITEM_ID_START /*+ GetRand(ITEM_MAX - 1))*/ ): id);
	//};

	//auto paramUP = [=](auto& paramFlag, auto limNum) {
	//	paramFlag += (paramFlag < limNum);
	//	lpMapCtrl.SetMapData(pos, MAP_ID::NONE);
	//};

	//switch (ItemID())
	//{
	//	case MAP_ID::POTION_1:
	//		paramUP(NotFlag, 1);
	//		break;
	//	case MAP_ID::POTION_2:
	//		paramUP(NotFlag, 1);
	//		break;
	//	case MAP_ID::POTION_3:
	//		paramUP(NotFlag, 1);
	//		break;
	//	case MAP_ID::POTION_4:
	//		paramUP(NotFlag, 1);
	//		break;

	//default:
	//	break;
	//}
}
