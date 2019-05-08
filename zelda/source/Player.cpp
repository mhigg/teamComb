#include <DxLib.h>
#include "Player.h"
#include "StageMng.h"


Player::Player(PL_NUMBER plNum, VECTOR2 setUpPos, VECTOR2 drawOffset):Obj(drawOffset)
{
	pos = { 0,0 };
	speed = PL_DEF_SPEED;

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
	
	SpeedTbl = { PL_DEF_SPEED,	// ��
				-PL_DEF_SPEED,	// ��
				 PL_DEF_SPEED,	// �E
				-PL_DEF_SPEED	// ��
			   };

	//			MAIN		REV		OPP1	  OPP2
	DirTbl = { DIR_DOWN ,DIR_UP   ,DIR_LEFT ,DIR_RIGHT,	// ��(REV:��)(���E�E)
			   DIR_LEFT ,DIR_RIGHT,DIR_DOWN ,DIR_UP,	// ��(REV:�E)(��E��)
			   DIR_RIGHT,DIR_LEFT ,DIR_DOWN ,DIR_UP,	// �E(REV:��)(��E��)
			   DIR_UP   ,DIR_DOWN ,DIR_LEFT ,DIR_RIGHT	// ��(REV:��)(���E�E)
			  };

	mapMoveTbl = {	false,	// NONE
					true,	// WALL1
					true,	// WALL2
					true,	// WALL3
					true,	// WALL4
					true,	// WALL5
					true,	// WALL6
					true,	// WALL7
					true,	// WALL8
					true,	// WALL9
					false,	// FLOOR1
					false,	// FLOOR2
					false,	// DOOR1
					false,	// DOOR2
					false,	// DOOR3
					false,	// DOOR4
					
					
					
	};

	this->plNum = plNum;

	Init("image/ghost.png", VECTOR2(40,40), VECTOR2(1,1), setUpPos);
	Init("image/player.png", VECTOR2(80, 120), VECTOR2(4, 7), setUpPos);
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
	auto &inputTbl = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputTblOld = controller.GetInputState(KEY_TYPE_OLD);
	auto &chipSize = lpStageMng.GetChipSize().x;

	auto sidePos = [&](VECTOR2 pos, DIR dir, int speed, SIDE_CHECK sideFlag) {
		VECTOR2 side;
		switch (dir)
		{
		case DIR_DOWN:
			side = { 0,(chipSize - sideFlag) + speed };
			break;
		case DIR_LEFT:
			side = { speed - (sideFlag ^ 1) ,0 };
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

	auto Move = [&, dir = Player::dir](DIR_TBL_ID id){
		if (inputTbl[plNum][keyIdTbl[DirTbl[dir][id]]])			// �� ���l��0����ڲ԰ID�ɂ���
		{
			Player::dir = DirTbl[dir][id];		// �����̾��

			// if (/*mapMoveTbl*/)		// �ړ�����
			//{
				// Player::dir = DirTbl[dir][id];
				// return false;		// �ړ��ł��Ȃ��ꍇ(���؂Ȃǂ̵�޼ު�Ă�����Ƃ�)
			//}
			// �ړ�����-----------------------------
			(*PosTbl[Player::dir][TBL_MAIN]) += SpeedTbl[Player::dir];	// �ύX���������W�̕ϐ��A�h���X += �ړ���
			return true;
		}

		return false;
	};

	// ��key����------------------------------------
	if (!(Move((DIR_TBL_ID)(DIR_TBL_OPP1 - (afterKeyFlag << 1)))		// OPP1,OPP2�Ɉړ����Ȃ������ꍇ
		|| Move((DIR_TBL_ID)(DIR_TBL_OPP2 - (afterKeyFlag << 1)))))	// (key���͂��Ȃ������ꍇ)
	{
		afterKeyFlag = false;
		if (!(Move((DIR_TBL_ID)(DIR_TBL_MAIN + (afterKeyFlag << 1)))	// MAIN,REV�Ɉړ����Ȃ������ꍇ
			|| Move((DIR_TBL_ID)(DIR_TBL_REV + (afterKeyFlag << 1)))))// (key���͂��Ȃ������ꍇ)
		{
			SetAnim("��~");
			return;
		}
	}
	else
	{
		// OPP1��������OPP2��key���͂��������ꍇ�̏��
		afterKeyFlag = (bool)inputTbl[plNum][keyIdTbl[DirTbl[dir][DIR_TBL_OPP1]]];		// ��
		afterKeyFlag |= (bool)inputTbl[plNum][keyIdTbl[DirTbl[dir][DIR_TBL_OPP2]]];		// ��
		afterKeyFlag ^= (int)(GetAnim() == "��~");
	}
	SetAnim("����");

}

bool Player::CheckObjType(OBJ_TYPE type)
{
	return (type == OBJ_PLAYER);

}

bool Player::DeathPrc(void)
{
	return false;
}
