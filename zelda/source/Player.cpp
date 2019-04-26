#include <DxLib.h>
#include "Player.h"
#include "StageMng.h"



Player::Player(VECTOR2 setUpPos, VECTOR2 drawOffset)
{
	pos = { 0,0 };
	speed = PL_DEF_SPEED;

	keyIdTbl = {};

	PosTbl = { &pos.y,&pos.x,	// 下
				&pos.x,&pos.y,	// 左
				&pos.x,&pos.y,	// 右
				&pos.y,&pos.x	// 上
			 };
	
	SpeedTbl = { PL_DEF_SPEED,	// 下
				-PL_DEF_SPEED,	// 左
				 PL_DEF_SPEED,	// 右
				-PL_DEF_SPEED	// 上
			   };

	//			MAIN		REV		OPP1	  OPP2
	DirTbl = { DIR_DOWN ,DIR_UP   ,DIR_LEFT ,DIR_RIGHT,	// 下(REV:上)(左・右)
			   DIR_LEFT ,DIR_RIGHT,DIR_DOWN ,DIR_UP,	// 左(REV:右)(上・下)
			   DIR_RIGHT,DIR_LEFT ,DIR_DOWN ,DIR_UP,	// 右(REV:左)(上・下)
			   DIR_UP   ,DIR_DOWN ,DIR_LEFT ,DIR_RIGHT	// 上(REV:下)(左・右)
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
		// if(ｺﾝﾄﾛｰﾗｰの情報)
		{
			Player::dir = DirTbl[dir][id];		// 方向のｾｯﾄ

			// if (/*mapMoveTbl*/)		// 移動制御
			{
				Player::dir = DirTbl[dir][id];
				return false;		// 移動できない場合(岩や木などのｵﾌﾞｼﾞｪｸﾄがあるとき)
			}

			return true;
		}
		return false;
	};

}

bool Player::DeathPrc(void)
{
	return false;
}
