#pragma once
#include<array>
#include <vector>
#include "Obj.h"
#include "MAP_ID.h"

// enemyの種類(名前など)
enum class ENEMY
{
	ENEMY_1,
	ENEMY_2,
	ENEMY_3,
	ENEMY_4,
	ENEMY_MAX
};

// enemyの状態
enum class ENEMY_STATE
{
	NORMAL,		// 通常
	TRA,				// 追跡
	RETREAT,		// 怯み
	DEATH,			// 死亡
	MAX
};

// enemyの行動
enum class ENEM_ACT
{
	DO_NOTHING,	// 何もしない
	MOVE,				// 移動
	TRA,					// 追跡
	SERCH,				// 探索
	MAX
};

constexpr auto ENEMY_SPEED = 2;
constexpr auto ENEMY_DASH_SPEED = 6;
constexpr auto ENEMY_LIM = 201;
constexpr auto PLAYER_DIS_X = 9;
constexpr auto PLAYER_DIS_Y = 5;

using PRIORITY_ARRAY = std::array<int, static_cast<int>(ENEM_ACT::MAX)>;
using PRIORITY_TBL_ARRAY = std::array<PRIORITY_ARRAY, static_cast<int>(ENEMY_STATE::MAX)>;
using PASS_FLAG = std::array<bool, DIR_MAX * 3>;
using PASS_ARR_ALL = std::array<VECTOR2, DIR_MAX * 3>;
using DIR_PASS = std::array<DIR[3], DIR_MAX>;
using CHECK_ARR = std::vector<int>;

using  OBJ_POS = std::array<VECTOR2, 4>;
using  OBJ_INT = std::array<int, 4>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(	
		int enemyNum, 
		VECTOR2 setUpPos, 
		VECTOR2 drawOffset,
		int enCnt	);
	~Enemy();

	bool CheckDeath(void);							// 死亡判定,死んでいなければfalseを返す
	bool CheckObjType(OBJ_TYPE type);		// 指定した値と同じ型が来たらtrueを返す
	const OBJ_TYPE& GetObjType(void)const;
	void SetDeathFlag(bool deathFlag);
private:
	// ﾌﾚｰﾑごとに実行するもの
	void SetMove(const GameCtrl &controller, weakListObj objList);
	// ｻｲﾄﾞ判定
	VECTOR2 sidePos(VECTOR2 pos, DIR dir, int speed, int sideNum);
	bool initAnim(void);
	// ｴﾈﾐｰの初期化
	void EnInit(void);
	// 都度初期化が必要なもの	
	void CheckFree(void);
	// 仮想ﾊﾟｽの探索
	VECTOR2 Distance(DIR tmpDir,VECTOR2 pos);
	// 近いﾌﾟﾚｲﾔｰの検索
	int SerchPlayer(void);

	// ---------- ｴﾈﾐｰの状態関数 ------------
	void Move(const GameCtrl & controller);			// ﾗﾝﾀﾞﾑ
	void Track(const GameCtrl & controller);			// 追跡
	void Serch(const GameCtrl & controller);			// 探索
	void SpMove(const GameCtrl & controller);		// 指定行動
	void Damage(const GameCtrl & controller);		// ﾀﾞﾒｰｼﾞ時
	void Escape(const GameCtrl & controller);		// 逃げる
	void Wait(const GameCtrl & controller);			// 待機ﾄ

	ENEMY_STATE state;			// 状態
	ENEMY name;					// 敵の種類
	ENEM_ACT action;				// 敵の行動
	// ------------------近いﾌﾟﾚｲﾔｰの検索用--------------------------
	OBJ_POS plPos;					// ﾌﾟﾚｲﾔｰの座標
	OBJ_INT enPos;					// 敵の座標
	int nearP;							// 近いﾌﾟﾚｲﾔｰ

	int faintCnt;						// 怯みｶｳﾝﾄ
	int timeCnt;						// 経過時間のｶｳﾝﾄ
	bool oppFlag;						// 移動反転ﾌﾗｸﾞ
	int behaviorCnt;					// 行動時のｶｳﾝﾄ
	int enCnt;							// 自分自身のﾅﾝﾊﾞｰ
	int speed;							// 敵の移動速度
	int actNum[3];					// 行動予定のﾙｰﾄ
	int actRoot;						// 実行するﾙｰﾄ
	int movePos;						// 移動量		

	CHECK_ARR comPos;			// 優先度の比較用配列(昇順)
	CHECK_ARR comNum;		// 優先度の配列
	VECTOR2 addCnt;				// 敵の移動量管理
	DIR dir;								// 敵の向き
	PASS_FLAG passFlag;			// 移動できるﾊﾟｽ
	int comFlag;						// 優先配列に格納されている数
	PASS_ARR_ALL checkPos;	// 分岐点
	DIR_PASS dirOpp;				// 垂直方向

	DIR_TBL_ARY keyIdTbl;				// 移動方向
	DIR_TBL_PTR PosTbl;					// ﾎﾟｲﾝﾀを直接格納
	DIR_TBL_A2D SpeedTbl;			// 移動速度
	MAP_MOVE_TBL mapMoveTbl;	// 移動制御,移動可能ｵﾌﾞｼﾞｪｸﾄならtrueを返す←ｱｲﾃﾑや障害物を追加したときに使う
	void (Enemy::*_updater)(const GameCtrl & controller);		// 状態関数ﾎﾟｲﾝﾀ
protected:
	bool deathFlag;			// 死亡ﾌﾗｸﾞ
};

