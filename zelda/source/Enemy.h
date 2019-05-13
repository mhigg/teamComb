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
	TRA,				// 追跡
	RETREAT,		// 怯み
	DEATH,			// 死亡
	MAX
};

// enemyの行動
enum class ENEMY_BEHAVIOR
{
	DO_NOTHING,	// 何もしない
	MOVE,				// 移動
	TRA,					// 追跡
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

constexpr auto ENEMY_SPEED = 3;
constexpr auto ENEMY__DASH_SPEED = 6;

using PRIORITY_ARRAY = std::array<int, static_cast<int>(ENEMY_BEHAVIOR::MAX)>;
using PRIORITY_TBL_ARRAY = std::array<PRIORITY_ARRAY, static_cast<int>(ENEMY_STATE::MAX)>;

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

	ENEMY_STATE state;							// 状態
	ENEMY_BEHAVIOR nowBehavior;		// 現在の行動
	EnemyData data;								// 敵の情報

	int faintCnt;				// 怯みｶｳﾝﾄ
	int timeCnt;				// 経過時間のｶｳﾝﾄ
	bool oppFlag;				// 移動反転ﾌﾗｸﾞ
	int behaviorCnt;			// 行動時のｶｳﾝﾄ
	int speed;					// 敵の移動速度
	DIR dir;						// 敵の向き

	DIR_TBL_ARY keyIdTbl;				// 移動方向
	DIR_TBL_PTR PosTbl;					// ﾎﾟｲﾝﾀを直接格納
	DIR_TBL_A2D SpeedTbl;			// 移動速度
	DIR_TBL_DIR DirTbl;					// 移動制御
	MAP_MOVE_TBL mapMoveTbl;	// 移動制御,移動可能ｵﾌﾞｼﾞｪｸﾄならtrueを返す←ｱｲﾃﾑや障害物を追加したときに使う

protected:
	bool deathFlag;			// 死亡ﾌﾗｸﾞ
};

