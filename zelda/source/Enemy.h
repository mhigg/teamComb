#pragma once
#include "Obj.h"

// enemy‚Ìí—Ş(–¼‘O‚È‚Ç)
enum class ENEMY
{
	ENEMY_1,
	ENEMY_2,
	ENEMY_3,
	ENEMY_4,
	ENEMY_MAX
};

// enemy‚Ìó‘Ô
enum class ENEMY_STATE
{
	NORMAL,		// ’Êí
	FOUND,		// ”­Œ©
	ATT,		// UŒ‚
	RETREAT,	// ‹¯‚İ
	DEATH,		// €–S
	MAX
};

// enemy‚Ìs“®
enum class ENEMY_BEHAVIOR
{
	DO_NOTHING,	// ‰½‚à‚µ‚È‚¢
	MOVE,		// ˆÚ“®
	ATT,		// UŒ‚
	MAX
};

// enemy‚ªplayer‚ğ’Tõ‚·‚é‚Æ‚«‚Ég‚¤
struct SearchParam
{
	float ExploreDistance;	// ’Tõ‹——£
	float ExploreAngle;		// ’TõŠp“x
	float SignDistance;		// ‹C”z‚ğŠ´‚¶‚é‹——£
};

// ˆÚ“®‚Ì•ûŒü·°‘€ì
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

	bool CheckDeath(void);				// €–S”»’è,€‚ñ‚Å‚¢‚È‚¯‚ê‚Îfalse‚ğ•Ô‚·
	bool CheckObjType(OBJ_TYPE type);	// w’è‚µ‚½’l‚Æ“¯‚¶Œ^‚ª—ˆ‚½‚çtrue‚ğ•Ô‚·
	virtual const OBJ_TYPE& GetObjType(void)const;
	void SetDeathFlag(bool deathFlag);
private:



	ENEMY_STATE state;				// ó‘Ô
	ENEMY_BEHAVIOR nowBehavior;		// Œ»İ‚Ìs“®
	MoveParam moveParam;			// ˆÚ“®‚Ì•ûŒü·°‘€ì
	int faintCnt;			// ‹¯‚İ¶³İÄ
	int timeCnt;			// Œo‰ßŠÔ‚Ì¶³İÄ
	bool oppFlag;			// ˆÚ“®”½“]Ì×¸Ş
	int behaviorCnt;		// s“®‚Ì¶³İÄ

protected:
	bool deathFlag;			// €–SÌ×¸Ş
};

