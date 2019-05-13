#pragma once
#include <array>
#include "VECTOR2.h"
#include "Obj.h"
#include "MapCtrl.h"
#include "GameCtrl.h"

enum PL_NUMBER {
	PL_1,
	PL_2,
	PL_3,
	PL_4,
	PL_MAX
};

constexpr int PL_DEF_SPEED = 7;
constexpr int PL_DASH_SPEED = 15;
constexpr int PL_LIFE_MAX = 5;


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

	int speed;
	int life;
	VECTOR2 startPos;				// ｽﾀｰﾄ地点(ﾘｽﾎﾟｰﾝ用)
	unsigned int NotFlag;

// ---------- ﾃｰﾌﾞﾙ配列 ------------
	DIR_TBL_ARY keyIdTbl;				// 移動方向
	DIR_TBL_PTR PosTbl;					// ﾎﾟｲﾝﾀを直接格納
	DIR_TBL_A2D SpeedTbl;			// 移動速度
	DIR_TBL_DIR DirTbl;					// 移動制御
	MAP_MOVE_TBL mapMoveTbl;	// 移動制御,移動可能ｵﾌﾞｼﾞｪｸﾄならtrueを返す←ｱｲﾃﾑや障害物を追加したときに使う

	bool afterKeyFlag;			// keyの後入力を優先させるﾌﾗｸﾞ
	PL_NUMBER plNum;
};

