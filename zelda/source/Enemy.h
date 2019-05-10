#pragma once
#include<array>
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
	FOUND,			// 発見
	ATT,				// 攻撃
	RETREAT,		// 怯み
	DEATH,			// 死亡
	MAX
};

// enemyの行動
enum class ENEMY_BEHAVIOR
{
	DO_NOTHING,	// 何もしない
	MOVE,				// 移動
	ATT,					// 攻撃
	MAX
};

enum class ENEMY_TBL_ID 
{
	MAIN,		// 移動方向
	OPP,			// 移動方向の逆の軸
	MAX
};

enum ENEMY_DIR_TBL_ID {
	MAIN,		// 移動方向
	REV,			// 移動している方向の逆
	OPP1,		// 移動方向の逆の軸�@
	OPP2,		// 移動方向の逆の軸�A
	MAX
};

// enemyがplayerを探索するときに使う
struct SearchParam
{
	float ExploreDistance;		// 探索距離
	float ExploreAngle;			// 探索角度
	float SignDistance;			// 気配を感じる距離
};

struct EnemyData
{
	std::string fileName;
	VECTOR2	divSize;
	VECTOR2	divCnt;
	ENEMY		name;
};

constexpr auto ENEMY_SPEED = 5;

using PRIORITY_ARRAY = std::array<int, static_cast<int>(ENEMY_BEHAVIOR::MAX)>;
using PRIORITY_TBL_ARRAY = std::array<PRIORITY_ARRAY, static_cast<int>(ENEMY_STATE::MAX)>;

using ENE_DIR_TBL_ARY = std::array<int, DIR_MAX>;
using ENE_DIR_TBL_A2D = std::array<int[2], DIR_MAX>;
using ENE_DIR_TBL_PTR = std::array<int*[static_cast<int>(ENEMY_TBL_ID::MAX)], DIR_MAX>;
using ENE_DIR_TBL_DIR   = std::array < DIR[static_cast<int>(ENEMY_DIR_TBL_ID::MAX)], DIR_MAX >;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(	std::string fileName, 
				VECTOR2	divSize,
				VECTOR2 divCnt,
				int Enum, 
				VECTOR2 setUpPos, 
				VECTOR2 drawOffset	);
	~Enemy();

	bool CheckDeath(void);							// 死亡判定,死んでいなければfalseを返す
	bool CheckObjType(OBJ_TYPE type);		// 指定した値と同じ型が来たらtrueを返す
	virtual const OBJ_TYPE& GetObjType(void)const;
	void SetDeathFlag(bool deathFlag);
private:
	void SetMove(const GameCtrl &controller, weakListObj objList);

	ENEMY_STATE state;								// 状態
	ENEMY_BEHAVIOR nowBehavior;			// 現在の行動
	EnemyData data;									// 敵の情報

	ENE_DIR_TBL_ARY keyIdTbl;		// 移動方向
	ENE_DIR_TBL_PTR PosTbl;			// ﾎﾟｲﾝﾀを直接格納
	ENE_DIR_TBL_A2D SpeedTbl;		// 移動速度
	ENE_DIR_TBL_DIR DirTbl;			// 移動制御

	int faintCnt;				// 怯みｶｳﾝﾄ
	int timeCnt;				// 経過時間のｶｳﾝﾄ
	bool oppFlag;				// 移動反転ﾌﾗｸﾞ
	int behaviorCnt;			// 行動時のｶｳﾝﾄ
	int moveSpeed;			// 敵の移動速度

protected:
	bool deathFlag;			// 死亡ﾌﾗｸﾞ
};

