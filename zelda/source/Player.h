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

constexpr int PL_DEF_SPEED = 2;
constexpr int PL_DASH_SPEED = 4;


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
	void InitScroll(void);			// ﾌﾟﾚｲﾔｰの座標によってｽｸﾛｰﾙｵﾌｾｯﾄを初期化する

	int speed;
	VECTOR2 startPos;				// ｽﾀｰﾄ地点(ﾘｽﾎﾟｰﾝ用)
	unsigned int NotFlag;

	int score;
	int life;
	int power;
	int guard;
	int inv;	//	無敵時間	
	int upTime; // ステータス上昇時間

// ---------- ﾃｰﾌﾞﾙ配列 ------------
	DIR_TBL_ARY keyIdTbl;				// 移動方向
	DIR_TBL_PTR PosTbl;					// ﾎﾟｲﾝﾀを直接格納
	DIR_TBL_A2D SpeedTbl;				// 移動速度
	DIR_TBL_DIR DirTbl;					// 移動制御
	MAP_MOVE_TBL mapMoveTbl;	// 移動制御,移動可能ｵﾌﾞｼﾞｪｸﾄならtrueを返す←ｱｲﾃﾑや障害物を追加したときに使う

	bool afterKeyFlag;			// keyの後入力を優先させるﾌﾗｸﾞ
	PL_NUMBER plNum;
};

