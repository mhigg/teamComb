#pragma once
#include<array>
#include "Obj.h"
#include "MAP_ID.h"

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
	TRA,				// ’ÇÕ
	RETREAT,		// ‹¯‚İ
	DEATH,			// €–S
	MAX
};

// enemy‚Ìs“®
enum class ENEM_ACT
{
	DO_NOTHING,	// ‰½‚à‚µ‚È‚¢
	MOVE,				// ˆÚ“®
	TRA,					// ’ÇÕ
	MAX
};

// enemy‚ªplayer‚ğ’Tõ‚·‚é‚Æ‚«‚Ég‚¤
struct SearchParam
{
	// float ExploreDistance;		// ’Tõ‹——£
	float ExploreAngle;				// ’TõŠp“x
	float SignDistance;				// ‹C”z‚ğŠ´‚¶‚é‹——£
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

	bool CheckDeath(void);							// €–S”»’è,€‚ñ‚Å‚¢‚È‚¯‚ê‚Îfalse‚ğ•Ô‚·
	bool CheckObjType(OBJ_TYPE type);		// w’è‚µ‚½’l‚Æ“¯‚¶Œ^‚ª—ˆ‚½‚çtrue‚ğ•Ô‚·
	const OBJ_TYPE& GetObjType(void)const;
	void SetDeathFlag(bool deathFlag);
private:
	void SetMove(const GameCtrl &controller, weakListObj objList);
	bool initAnim(void);

	ENEMY_STATE state;		// ó‘Ô
	ENEMY name;				// “G‚Ìí—Ş
	ENEM_ACT action;			// “G‚Ìs“®

	int faintCnt;					// ‹¯‚İ¶³İÄ
	int timeCnt;					// Œo‰ßŠÔ‚Ì¶³İÄ
	bool oppFlag;					// ˆÚ“®”½“]Ì×¸Ş
	int behaviorCnt;				// s“®‚Ì¶³İÄ
	int enCnt;						// ©•ª©g‚ÌÅİÊŞ°
	int speed;						// “G‚ÌˆÚ“®‘¬“x
	VECTOR2 addCnt;			// “G‚ÌˆÚ“®—ÊŠÇ—
	DIR dir;							// “G‚ÌŒü‚«

	DIR_TBL_ARY keyIdTbl;				// ˆÚ“®•ûŒü
	DIR_TBL_PTR PosTbl;					// Îß²İÀ‚ğ’¼ÚŠi”[
	DIR_TBL_A2D SpeedTbl;			// ˆÚ“®‘¬“x
	MAP_MOVE_TBL mapMoveTbl;	// ˆÚ“®§Œä,ˆÚ“®‰Â”\µÌŞ¼Şª¸Ä‚È‚çtrue‚ğ•Ô‚·©±²ÃÑ‚âáŠQ•¨‚ğ’Ç‰Á‚µ‚½‚Æ‚«‚Ég‚¤

	bool flag;

protected:
	bool deathFlag;			// €–SÌ×¸Ş
};

