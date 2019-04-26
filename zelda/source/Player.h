#pragma once
#include <array>
#include "VECTOR2.h"
#include "Obj.h"
#include "MapCtrl.h"
#include "GameCtrl.h"

enum TBL_ID {
	TBL_MAIN,		// 移動方向
	TBL_OPP,		// 移動方向の逆の軸
	TBL_MAX
};

enum DIR_TBL_ID {
	DIR_TBL_MAIN,	// 移動方向
	DIR_TBL_REV,	// 移動している方向の逆
	DIR_TBL_OPP1,	// 移動方向の逆の軸①
	DIR_TBL_OPP2,	// 移動方向の逆の軸②
	DIR_TBL_MAX
};

enum SIDE_CHECK {
	OUT_SIDE,	// 0
	IN_SIDE,	// 1
	SIDE_MAX
};

#define PL_DEF_SPEED 2

using DIR_TBL_ARRAY = std::array<int, DIR_MAX>;
using DIR_TBL_PTR = std::array<int*[TBL_MAX], DIR_MAX>;
using DIR_TBL_DIR = std::array<DIR[DIR_TBL_MAX], DIR_MAX>;
// using MAP_MOVE_TBL = std::array<bool, static_cast<int>(MAP_ID::MAX)>; ←アイテムや障害物を追加したときに使う


class Player :
	public Obj
{
public:
	Player(VECTOR2 setUpPos, VECTOR2 drawOffset);	// 引数付きコンストラクタ
	Player();
	~Player();
	bool initAnim(void);		// ｱﾆﾒｰｼｮﾝ管理
private:
	void SetMove(const GameCtrl &controller, weekListObj objList);

	bool DeathPrc(void);			// 関数化
	int speed;
	DIR dir;
	DIR_TBL_ARRAY keyIdTbl;		// 移動方向
	DIR_TBL_PTR PosTbl;			// ポインタを直接格納
	DIR_TBL_ARRAY SpeedTbl;		// 移動速度
	DIR_TBL_DIR DirTbl;			// 移動制御
	// MAP_MOVE_TBL mapMoveTbl;	// 移動制御,移動可能オブジェクトならtrueを返す←アイテムや障害物を追加したときに使う
};

