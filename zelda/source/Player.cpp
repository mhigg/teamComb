#include "DxLib.h"
#include "Player.h"



Player::Player(VECTOR2 setUpPos, VECTOR2 drawOffset)
{
	pos = { 0,0 };
	speed = PL_DEF_SPEED;

	keyIdTbl = {};

	PosTbl = { &pos.y,&pos.x,	// ��
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

	

}

Player::Player()
{
}


Player::~Player()
{
}

bool Player::initAnim(void)
{
	return false;
}

void Player::SetMove(const GameCtrl & controller, weekListObj objList)
{
	/*auto &chipSize = lpMapCtl.GetChipSize().x;

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
	};*/
}

bool Player::DeathPrc(void)
{
	return false;
}
