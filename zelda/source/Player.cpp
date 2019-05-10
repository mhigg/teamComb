#include <DxLib.h>
#include "Player.h"
#include "StageMng.h"
#include "MapCtrl.h"


Player::Player(PL_NUMBER plNum, VECTOR2 setUpPos, VECTOR2 drawOffset):Obj(drawOffset)
{
	pos = { 0,0 };
	speed = PL_DEF_SPEED;
	life = 5;

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
	
	SpeedTbl = { PL_DEF_SPEED,  PL_DASH_SPEED,	// 下
				-PL_DEF_SPEED, -PL_DASH_SPEED,	// 左
				 PL_DEF_SPEED,  PL_DASH_SPEED,	// 右
				-PL_DEF_SPEED, -PL_DASH_SPEED	// 上
			   };

	//			MAIN		REV		OPP1	  OPP2
	DirTbl = { DIR_DOWN ,DIR_UP   ,DIR_LEFT ,DIR_RIGHT,	// 下(REV:上)(左・右)
			   DIR_LEFT ,DIR_RIGHT,DIR_DOWN ,DIR_UP,	// 左(REV:右)(上・下)
			   DIR_RIGHT,DIR_LEFT ,DIR_DOWN ,DIR_UP,	// 右(REV:左)(上・下)
			   DIR_UP   ,DIR_DOWN ,DIR_LEFT ,DIR_RIGHT	// 上(REV:下)(左・右)
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
					true,	// WALL19	// GetMapDataの固定ID
					true,	// WALL20
					true,	// WALL21				とおる
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
					false,	// BOX_1	// 宝箱
					false,	// BOX_2	// 空いている宝箱
					true,	// MOTH_1	// ﾂﾎﾞ
					false,	// MOTH_2	// 壊れたﾂﾎﾞ
					true,	// MOTH_3	// 樽
					false,	// MOTH_4	// 壊れた樽
					false,	// TREE_1	// 木
					false,	// TREE_2
					false,	// TREE_3
					false,	// TREE_4
					false,	// HOLL_1	// 井戸
					false,	// HOLL_2
					false,	// HOLL_3
					false,	// HOLL_4
					false,	// STONE_1	// 岩
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
	AddAnim("停止", 0, 0, 1, 6, true);
	AddAnim("移動", 0, 1, 6, 2, true);
	AddAnim("疾走", 0, 1, 6, 1, true);
	AddAnim("死亡", 4, 0, 4, 8, false);	// falseでｱﾆﾒｰｼｮﾝをﾙｰﾌﾟさせない
	return true;
}

void Player::SetMove(const GameCtrl & controller, weakListObj objList)
{
	GetItem();

	auto &inputTbl = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputTblOld = controller.GetInputState(KEY_TYPE_OLD);
	auto &chipSize = lpStageMng.GetChipSize().x;

	// ﾌﾟﾚｲﾔｰのﾀﾞﾒｰｼﾞ受け(ﾃﾞﾊﾞｯｸ用)
	if (controller.GetCtrl(KEY_TYPE_NOW)[KEY_INPUT_F] & (~controller.GetCtrl(KEY_TYPE_OLD)[KEY_INPUT_F]))
	{
		life -= 1;
	}
	if (DeathPrc())
	{
		pos = startPos;		// ﾘｽﾎﾟｰﾝ処理
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
			Player::dir = DirTbl[dir][id];		// 方向のｾｯﾄ

			if (!mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Player::dir, SpeedTbl[Player::dir][inputTbl[plNum][XINPUT_RUN_RB]], IN_SIDE),MAP_ID::WALL19))])
			{
				Player::dir = DirTbl[dir][id];
				// 移動不可のオブジェクトが隣にあった場合
				return false;
			}

			// 移動処理-----------------------------
			// 変更したい座標の変数アドレス += 移動量
			(*PosTbl[Player::dir][TBL_MAIN]) += SpeedTbl[Player::dir][inputTbl[plNum][XINPUT_RUN_RB]];
//			scrollOffset += 
			return true;
		}
		return false;
	};

	// 後key処理------------------------------------
	if (!(Move(static_cast<DIR_TBL_ID>(DIR_TBL_OPP1 - (afterKeyFlag << 1)))		// OPP1,OPP2に移動しなかった場合
	 ||   Move(static_cast<DIR_TBL_ID>(DIR_TBL_OPP2 - (afterKeyFlag << 1)))))	// (key入力がなかった場合)
	{
		afterKeyFlag = false;
		if (!(Move(static_cast<DIR_TBL_ID>(DIR_TBL_MAIN + (afterKeyFlag << 1)))	// MAIN,REVに移動しなかった場合
		 ||   Move(static_cast<DIR_TBL_ID>(DIR_TBL_REV  + (afterKeyFlag << 1)))))// (key入力がなかった場合)
		{
			SetAnim("停止");
			return;
		}
	}
	else
	{
		// OPP1もしくはOPP2にkey入力があった場合の情報
		afterKeyFlag = static_cast<bool>(inputTbl[plNum][keyIdTbl[DirTbl[dir][DIR_TBL_OPP1]]]);
		afterKeyFlag |= static_cast<bool>(inputTbl[plNum][keyIdTbl[DirTbl[dir][DIR_TBL_OPP2]]]);
		afterKeyFlag ^= static_cast<int>(GetAnim() == "停止");
	}
	// ﾌﾟﾚｲﾔｰが走っているときは疾走ｱﾆﾒｰｼｮﾝにする
	if (inputTbl[plNum][XINPUT_RUN_RB])
	{
		SetAnim("疾走");
		return;
	}
	SetAnim("移動");
}

bool Player::CheckObjType(OBJ_TYPE type)
{
	return (type == OBJ_PLAYER);

}

bool Player::DeathPrc(void)
{
	if (life < 0)
	{
		/*SetAnim("死亡");*/
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
