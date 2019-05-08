#include <DxLib.h>
#include "Player.h"
#include "StageMng.h"


Player::Player(PL_NUMBER plNum, VECTOR2 setUpPos, VECTOR2 drawOffset):Obj(drawOffset)
{
	pos = { 0,0 };
	speed = PL_DEF_SPEED;

	keyIdTbl = { XINPUT_DOWN,	// 下
				 XINPUT_LEFT,	// 左
				 XINPUT_RIGHT,	// 右
				 XINPUT_UP		// 上
				};

	PosTbl = {  &pos.y,&pos.x,	// 下
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
	AddAnim("停止", 0, 0, 1, 6, true);
	AddAnim("移動", 0, 1, 6, 2, true);
	AddAnim("疾走", 0, 1, 6, 1, true);
	AddAnim("死亡", 4, 0, 4, 8, false);	// falseでｱﾆﾒｰｼｮﾝをﾙｰﾌﾟさせない
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
		if (inputTbl[plNum][keyIdTbl[DirTbl[dir][id]]])			// ※ 直値の0をﾌﾟﾚｲﾔｰIDにする
		{
			Player::dir = DirTbl[dir][id];		// 方向のｾｯﾄ

			// if (/*mapMoveTbl*/)		// 移動制御
			//{
				// Player::dir = DirTbl[dir][id];
				// return false;		// 移動できない場合(岩や木などのｵﾌﾞｼﾞｪｸﾄがあるとき)
			//}
			// 移動処理-----------------------------
			(*PosTbl[Player::dir][TBL_MAIN]) += SpeedTbl[Player::dir];	// 変更したい座標の変数アドレス += 移動量
			return true;
		}

		return false;
	};

	// 後key処理------------------------------------
	if (!(Move((DIR_TBL_ID)(DIR_TBL_OPP1 - (afterKeyFlag << 1)))		// OPP1,OPP2に移動しなかった場合
		|| Move((DIR_TBL_ID)(DIR_TBL_OPP2 - (afterKeyFlag << 1)))))	// (key入力がなかった場合)
	{
		afterKeyFlag = false;
		if (!(Move((DIR_TBL_ID)(DIR_TBL_MAIN + (afterKeyFlag << 1)))	// MAIN,REVに移動しなかった場合
			|| Move((DIR_TBL_ID)(DIR_TBL_REV + (afterKeyFlag << 1)))))// (key入力がなかった場合)
		{
			SetAnim("停止");
			return;
		}
	}
	else
	{
		// OPP1もしくはOPP2にkey入力があった場合の情報
		afterKeyFlag = (bool)inputTbl[plNum][keyIdTbl[DirTbl[dir][DIR_TBL_OPP1]]];		// ※
		afterKeyFlag |= (bool)inputTbl[plNum][keyIdTbl[DirTbl[dir][DIR_TBL_OPP2]]];		// ※
		afterKeyFlag ^= (int)(GetAnim() == "停止");
	}
	SetAnim("疾走");

}

bool Player::CheckObjType(OBJ_TYPE type)
{
	return (type == OBJ_PLAYER);

}

bool Player::DeathPrc(void)
{
	return false;
}
