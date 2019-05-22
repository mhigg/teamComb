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
	MAX
};

// enemyがplayerを探索するときに使う
struct SearchParam
{
	// float ExploreDistance;		// 探索距離
	float ExploreAngle;				// 探索角度
	float SignDistance;				// 気配を感じる距離
};

constexpr auto ENEMY_SPEED = 5;
constexpr auto ENEMY_DASH_SPEED = 6;
constexpr auto ENEMY_LIM = 201;

using PRIORITY_ARRAY = std::array<int, static_cast<int>(ENEM_ACT::MAX)>;
using PRIORITY_TBL_ARRAY = std::array<PRIORITY_ARRAY, static_cast<int>(ENEMY_STATE::MAX)>;

using  ENEMY_POS = std::array<VECTOR2, 2>;

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
	virtual const OBJ_TYPE& GetObjType(void)const;
	void SetDeathFlag(bool deathFlag);
private:
	void SetMove(const GameCtrl &controller, weakListObj objList);
	bool initAnim(void);

	ENEMY_STATE state;		// 状態
	ENEMY name;				// 敵の種類
	ENEM_ACT action;			// 敵の行動

	int faintCnt;					// 怯みｶｳﾝﾄ
	int timeCnt;					// 経過時間のｶｳﾝﾄ
	bool oppFlag;					// 移動反転ﾌﾗｸﾞ
	int behaviorCnt;				// 行動時のｶｳﾝﾄ
	int enCnt;						// 自分自身のﾅﾝﾊﾞｰ
	int speed;						// 敵の移動速度
	VECTOR2 addCnt;			// 敵の移動量管理
	DIR dir;							// 敵の向き

	DIR_TBL_ARY keyIdTbl;				// 移動方向
	DIR_TBL_PTR PosTbl;					// ﾎﾟｲﾝﾀを直接格納
	DIR_TBL_A2D SpeedTbl;			// 移動速度
	MAP_MOVE_TBL mapMoveTbl;	// 移動制御,移動可能ｵﾌﾞｼﾞｪｸﾄならtrueを返す←ｱｲﾃﾑや障害物を追加したときに使う
protected:
	bool deathFlag;			// 死亡ﾌﾗｸﾞ
};

