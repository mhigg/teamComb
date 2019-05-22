#include <DxLib.h>
#include <math.h>
#include "Player.h"
#include "StageMng.h"
#include "InfoCtrl.h"
#include "MapCtrl.h"


Player::Player(PL_NUMBER plNum, VECTOR2 setUpPos, VECTOR2 drawOffset):Obj(drawOffset)
{
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
					false,	// WALL1
					false,	// WALL2
					false,	// WALL3
					false,	// WALL4
					false,	// WALL5
					false,	// WALL6
					false,	// WALL7
					false,	// WALL8
					false,	// WALL9
					true,		// WALL10
					true,		// WALL11
					false,	// WALL12
					false,	// WALL13
					false,	// WALL14
					false,	// WALL15
					false,	// WALL16
					false,	// WALL17
					false,	// WALL18
					false,	// WALL19	// GetMapDataの固定ID
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
					false,	// WALL33
					false,	// WALL34
					false,	// WALL35
					false,	// WALL36
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
					false,	// BOX_1	// 宝箱
					false,	// BOX_2	// 空いている宝箱
					true,		// MOTH_1	// ﾂﾎﾞ
					false,	// MOTH_2	// 壊れたﾂﾎﾞ
					true,		// MOTH_3	// 樽
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

	hitRad = VECTOR2(20, 20);
	actOff = VECTOR2(40, 100);

	Init("image/playerAll.png", VECTOR2(960 / 12, 840 / 7), VECTOR2(12, 7), setUpPos);
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
	AddAnim("停止", 0, 0, 1, 6, true);
	AddAnim("移動", 0, 1, 6, 8, true);
	AddAnim("疾走", 4, 1, 6, 6, true);
	AddAnim("攻撃", 8, 1, 6, 3, false);
	AddAnim("死亡", 0, 0, 1, 6, false);	// falseでｱﾆﾒｰｼｮﾝをﾙｰﾌﾟさせない
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

	upTime = {
		0,0
	};
	invTime = 0;
	damaCnt = 0;
	afterKeyFlag = false;
	visible = true;
	lpInfoCtrl.SetAddScroll(scrollOffset, static_cast<int>(plNum));
	_updater = &Player::Move;				// 初期状態はMove状態
}

void Player::SetMove(const GameCtrl & controller, weakListObj objList)
{
	GetItem();
	invTime = state.Inv;

	auto &chipSize = lpStageMng.GetChipSize().x;

	(this->*_updater)(controller);

	// 時間経過によるステータス変更
	// 攻撃
	if (state.Power >= 2)
	{
		upTime[0]++;
	}
	if (upTime[0] / 600 == 1)
	{
		lpScoreBoard.SetScore(DATA_POWER, -1);
		upTime[0] -= 600;
	}
	// 防御
	if (state.Guard >= 1)
	{
		upTime[1]++;
	}
	if (upTime[1] > 600)
	{
		lpScoreBoard.SetScore(DATA_GUARD, - state.Guard);
		upTime[1] -= 600;
	}
	// 無敵
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
	if (lpScoreBoard.GetScore(DATA_LIFE) < 1)
	{
		/*SetAnim("死亡");*/
		return true;
	}
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
		case MAP_ID::POTION_1:	// 赤
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_POWER, 1);
			break;
		case MAP_ID::POTION_2:	// 青
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_GUARD, 1);
			break;
		case MAP_ID::POTION_3:	// 緑
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_LIFE, 2);
			break;
		case MAP_ID::POTION_4:	// 虹
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_INV, 180);
			break;
		case MAP_ID::COIN_1:	// 赤
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_SCORE, 300);
			break;
		case MAP_ID::COIN_2:	// 青
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_SCORE, 500);
			break;
		case MAP_ID::COIN_3:	// 緑
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_SCORE, 800);
			break;
		case MAP_ID::COIN_4:	// 黄
			paramUP(NotFlag, num);
			lpScoreBoard.SetScore(DATA_SCORE, 1000);
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
			break;
		case MAP_ID::SHIELD:
			paramUP(NotFlag, num);
			break;
		case MAP_ID::BOOK:
			paramUP(NotFlag, num);
			break;
		case MAP_ID::GOLD:
			paramUP(NotFlag, num);
			break;
		case MAP_ID::DIA:
			paramUP(NotFlag, num);
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

	// ﾌﾟﾚｲﾔｰのﾀﾞﾒｰｼﾞ受け(ﾃﾞﾊﾞｯｸﾞ用)
	if (inputTbl[plNum][XINPUT_MAP] & (~inputTblOld[plNum][XINPUT_MAP]))
	{
		_updater = &Player::Damage;
	}

	if (inputTbl[plNum][XINPUT_ATT] & (~inputTblOld[plNum][XINPUT_ATT]))
	{
		SetAnim("攻撃");
		_updater = &Player::Attack;
	}
}

void Player::Move(const GameCtrl & controller)
{
	auto &inputTbl = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputTblOld = controller.GetInputState(KEY_TYPE_OLD);

	// ﾌﾟﾚｲﾔｰのﾀﾞﾒｰｼﾞ受け(ﾃﾞﾊﾞｯｸﾞ用)
	if (inputTbl[plNum][XINPUT_MAP] & (~inputTblOld[plNum][XINPUT_MAP]))
	{
		_updater = &Player::Damage;
		return;
	}

	if (inputTbl[plNum][XINPUT_ATT] & (~inputTblOld[plNum][XINPUT_ATT]))
	{
		SetAnim("攻撃");
		_updater = &Player::Attack;
		return;
	}

	auto sidePos = [&](VECTOR2 pos, DIR dir, int speed, int sideNum) {
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
	};

//--------- 敵に当たった時の処理 ----------
	
	bool damageFlag = false;
	for (int i = 0; (i < ENEMY_MAX) && (damageFlag == false); i++)
	{
		 VECTOR2 ePos = lpInfoCtrl.GetEnemyPos(i);
		if (ePos != VECTOR2(-1, -1))
		{
			 	VECTOR2 tmp = { ePos - pos };
			_RPTN(_CRT_WARN, "\n%d\t%d\t%d\t%d", ePos.x, ePos.y,pos.x,pos.y);
			if (sqrt(tmp.x * tmp.x) + sqrt(tmp.y * tmp.y) <= 50)
			{
				// 当たってるとき
				damageFlag = true;
			}
		}
	}


	if (damageFlag && (state.Inv <= 0))
	{
		SetAnim("死亡");
		_updater = &Player::Damage;
		return;
	}
// ----------------------------------------

	auto Move = [&, dir = Player::dir](DIR_TBL_ID id){
		if (inputTbl[plNum][keyIdTbl[DirTbl[dir][id]]])
		{
			Player::dir = DirTbl[dir][id];		// 方向のｾｯﾄ

			if (!mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Player::dir, SpeedTbl[Player::dir][inputTbl[plNum][XINPUT_RUN_RB]], -hitRad.x)))]
				|| !mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Player::dir, SpeedTbl[Player::dir][inputTbl[plNum][XINPUT_RUN_RB]], hitRad.x - 1)))])
			{
				Player::dir = DirTbl[dir][id];
				// 移動不可のオブジェクトが隣にあった場合
				return false;
			}

			// 移動処理-----------------------------
			// 変更したい座標の変数アドレス += 移動量
			(*PosTbl[Player::dir][TBL_MAIN]) += SpeedTbl[Player::dir][inputTbl[plNum][XINPUT_RUN_RB]];

			if ((pos.x >= SCROLL_AREA_X) && (pos.x <= (SCROLL_AREA_SIZE_X)))
			{
				scrollOffset.x = pos.x - SCROLL_AREA_X;
				lpMapCtrl.AddScroll(scrollOffset, static_cast<int>(plNum));
			}
			if ((pos.y >= SCROLL_AREA_Y) && (pos.y <= (SCROLL_AREA_SIZE_Y)))
			{
				scrollOffset.y = pos.y - SCROLL_AREA_Y;
				lpMapCtrl.AddScroll(scrollOffset, static_cast<int>(plNum));
			}
			lpInfoCtrl.SetAddScroll(scrollOffset, static_cast<int>(plNum));
			return true;
		}
		return false;
	};

	// 後key処理------------------------------------
	if (!(Move(static_cast<DIR_TBL_ID>(DIR_TBL_OPP1 - (afterKeyFlag << 1)))		// OPP1,OPP2に移動しなかった場合
		|| Move(static_cast<DIR_TBL_ID>(DIR_TBL_OPP2 - (afterKeyFlag << 1)))))	// (key入力がなかった場合)
	{
		afterKeyFlag = false;
		if (!(Move(static_cast<DIR_TBL_ID>(DIR_TBL_MAIN + (afterKeyFlag << 1)))	// MAIN,REVに移動しなかった場合
			|| Move(static_cast<DIR_TBL_ID>(DIR_TBL_REV + (afterKeyFlag << 1)))))// (key入力がなかった場合)
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

void Player::Attack(const GameCtrl & controller)
{
	if (!animEndFlag)
	{
		// 攻撃処理

		return;
	}

	// ｱﾆﾒｰｼｮﾝが終わったら元に戻す
	_updater = &Player::Move;
}

void Player::Damage(const GameCtrl & controller)
{
	auto &inputTbl = controller.GetInputState(KEY_TYPE_NOW);
	if (damaCnt)
	{
		if (damaCnt % 5 == 0)
		{
			(*PosTbl[Player::dir][TBL_MAIN]) -= SpeedTbl[Player::dir][inputTbl[plNum][0]] / 2 * 10;
			if ((pos.x >= SCROLL_AREA_X) && (pos.x <= (SCROLL_AREA_SIZE_X)))
			{
				scrollOffset.x = pos.x - SCROLL_AREA_X;
				lpMapCtrl.AddScroll(scrollOffset, static_cast<int>(plNum));
			}
			if ((pos.y >= SCROLL_AREA_Y) && (pos.y <= (SCROLL_AREA_SIZE_Y)))
			{
				scrollOffset.y = pos.y - SCROLL_AREA_Y;
				lpMapCtrl.AddScroll(scrollOffset, static_cast<int>(plNum));
			}
			lpInfoCtrl.SetAddScroll(scrollOffset, static_cast<int>(plNum));
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
			if (DeathPrc())
			{
				dir = DIR_DOWN;
				pos = startPos;		// ﾘｽﾎﾟｰﾝ処理
				lpScoreBoard.DataInit();
				InitScroll(static_cast<int>(plNum));
			}
			// ﾀﾞﾒｰｼﾞｱﾆﾒｰｼｮﾝが終わったら遷移(予定)
			_updater = &Player::Move;
			visible = true;
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
