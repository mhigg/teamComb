#pragma once
#include <array>
#include "VECTOR2.h"
#include "Obj.h"
#include "MapCtrl.h"
#include "ScoreBoard.h"
#include "GameCtrl.h"


enum PL_NUMBER {
	PL_1,
	PL_2,
	PL_3,
	PL_4,
	PL_MAX
};

struct State {
	int Power;
	int Guard;
	int Inv;
};

constexpr int PL_DEF_SPEED = 2;
constexpr int PL_DASH_SPEED = 4;
using UP_TIME = std::array < int, 2 >;


class Player :
	public Obj
{
public:
	Player(PL_NUMBER plNum, VECTOR2 setUpPos, VECTOR2 drawOffset);	// 引数付きｺﾝｽﾄﾗｸﾀｰ
	Player();
	~Player();
	bool initAnim(void);		// ｱﾆﾒｰｼｮﾝ管理
private:
	void PlInit(void);
	void SetMove(const GameCtrl &controller, weakListObj objList);
	bool CheckObjType(OBJ_TYPE type);
	bool DeathPrc(void);			// 関数化
	void GetItem(void);				// ｱｲﾃﾑ取得

// ---------- ﾌﾟﾚｲﾔｰの状態関数 ------------
	void Stop(const GameCtrl & controller);			// 停止状態
	void Move(const GameCtrl & controller);			// 歩き／走り状態
	void Attack(const GameCtrl & controller);		// 攻撃時
	void Damage(const GameCtrl & controller);		// ﾀﾞﾒｰｼﾞ時


	int speed;
	VECTOR2 startPos;				// ｽﾀｰﾄ地点(ﾘｽﾎﾟｰﾝ用)
	unsigned int NotFlag;
	State state;

	int score;
	int life;
	int invTime;				// inv減算用
	int damaCnt;				// ﾀﾞﾒｰｼﾞを受けてからのｶｳﾝﾄ
	std::array<int,SCORE_DATA::DATA_MAX> param;

// ---------- ﾃｰﾌﾞﾙ配列 ------------
	UP_TIME	upTime;				// ステータス(攻撃,防御)上昇時間
	DIR_TBL_ARY keyIdTbl;		// 移動方向
	DIR_TBL_PTR PosTbl;			// ﾎﾟｲﾝﾀを直接格納
	DIR_TBL_A2D SpeedTbl;		// 移動速度
	DIR_TBL_DIR DirTbl;			// 移動制御
	MAP_MOVE_TBL mapMoveTbl;	// 移動制御,移動可能ｵﾌﾞｼﾞｪｸﾄならtrueを返す←ｱｲﾃﾑや障害物を追加したときに使う

	bool afterKeyFlag;			// keyの後入力を優先させるﾌﾗｸﾞ
	PL_NUMBER plNum;

	void (Player::*_updater)(const GameCtrl & controller);		// 状態関数ﾎﾟｲﾝﾀ
};

