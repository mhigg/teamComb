#pragma once
#include "Obj.h"

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
	FOUND,		// 発見
	ATT,		// 攻撃
	RETREAT,	// 怯み
	DEATH,		// 死亡
	MAX
};

// enemyの行動
enum class ENEMY_BEHAVIOR
{
	DO_NOTHING,	// 何もしない
	MOVE,		// 移動
	ATT,		// 攻撃
	MAX
};

// enemyがplayerを探索するときに使う
struct SearchParam
{
	float ExploreDistance;	// 探索距離
	float ExploreAngle;		// 探索角度
	float SignDistance;		// 気配を感じる距離
};

// 移動時の方向ｷｰ操作
struct MoveParam
{
	bool down;
	bool left;
	bool right;
	bool up;
};

struct EnemyData
{
	std::string fileName;
	VECTOR2		divSize;
	VECTOR2		divCnt;
	ENEMY		name;
};

using PRIORITY_ARRAY = std::array<int, static_cast<int>(ENEMY_BEHAVIOR::MAX)>;
using PRIORITY_TBL_ARRAY = std::array<PRIORITY_ARRAY, static_cast<int>(ENEMY_STATE::MAX)>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyData data, VECTOR2 setUpPos, VECTOR2 drawOffset);
	~Enemy();

	bool CheckDeath(void);				// 死亡判定,死んでいなければfalseを返す
	bool CheckObjType(OBJ_TYPE type);	// 指定した値と同じ型が来たらtrueを返す
	virtual const OBJ_TYPE& GetObjType(void)const;
	void SetDeathFlag(bool deathFlag);
private:



	ENEMY_STATE state;				// 状態
	ENEMY_BEHAVIOR nowBehavior;		// 現在の行動
	MoveParam moveParam;			// 移動時の方向ｷｰ操作
	int faintCnt;			// 怯みｶｳﾝﾄ
	int timeCnt;			// 経過時間のｶｳﾝﾄ
	bool oppFlag;			// 移動反転ﾌﾗｸﾞ
	int behaviorCnt;		// 行動時のｶｳﾝﾄ

protected:
	bool deathFlag;			// 死亡ﾌﾗｸﾞ
};

