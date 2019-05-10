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

enum PL_NUMBER {
	PL_1,
	PL_2,
	PL_3,
	PL_4,
	PL_MAX
};

constexpr int PL_DEF_SPEED = 5;
constexpr int PL_DASH_SPEED = 10;

using DIR_TBL_ARY = std::array<int, DIR_MAX>;
using DIR_TBL_A2D = std::array<int[2], DIR_MAX>;
using DIR_TBL_PTR = std::array<int*[TBL_MAX], DIR_MAX>;
using DIR_TBL_DIR = std::array<DIR[DIR_TBL_MAX], DIR_MAX>;
using MAP_MOVE_TBL = std::array<bool, static_cast<int>(MAP_ID::MAX)>; // ←ｱｲﾃﾑや障害物を追加したときに使う


class Player :
	public Obj
{
public:
	Player(PL_NUMBER plNum, VECTOR2 setUpPos, VECTOR2 drawOffset);	// 引数付きｺﾝｽﾄﾗｸﾀｰ
	Player();
	~Player();
	bool initAnim(void);		// ｱﾆﾒｰｼｮﾝ管理
private:
	void SetMove(const GameCtrl &controller, weakListObj objList);
	bool CheckObjType(OBJ_TYPE type);
	bool DeathPrc(void);			// 関数化
	void GetItem(void);				// ｱｲﾃﾑ取得

	int offset;	// 値『20』を格納する
	int speed;
	DIR dir;
	int life;
	VECTOR2 startPos;				// ｽﾀｰﾄ地点(ﾘｽﾎﾟｰﾝ用)
	unsigned int NotFlag;

// ---------- ﾃｰﾌﾞﾙ配列 ------------
	DIR_TBL_ARY keyIdTbl;		// 移動方向
	DIR_TBL_PTR PosTbl;			// ﾎﾟｲﾝﾀを直接格納
	DIR_TBL_A2D SpeedTbl;		// 移動速度
	DIR_TBL_DIR DirTbl;			// 移動制御
	MAP_MOVE_TBL mapMoveTbl;	// 移動制御,移動可能ｵﾌﾞｼﾞｪｸﾄならtrueを返す←ｱｲﾃﾑや障害物を追加したときに使う

	bool afterKeyFlag;			// keyの後入力を優先させるﾌﾗｸﾞ
	PL_NUMBER plNum;
};

