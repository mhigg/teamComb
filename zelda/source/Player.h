#pragma once
#include <array>
#include "VECTOR2.h"
#include "Obj.h"
#include "MapCtrl.h"
#include "GameCtrl.h"

enum TBL_ID {
	TBL_MAIN,		// ˆÚ“®•ûŒü
	TBL_OPP,		// ˆÚ“®•ûŒü‚Ì‹t‚Ì²
	TBL_MAX
};

enum DIR_TBL_ID {
	DIR_TBL_MAIN,	// ˆÚ“®•ûŒü
	DIR_TBL_REV,	// ˆÚ“®‚µ‚Ä‚¢‚é•ûŒü‚Ì‹t
	DIR_TBL_OPP1,	// ˆÚ“®•ûŒü‚Ì‹t‚Ì²‡@
	DIR_TBL_OPP2,	// ˆÚ“®•ûŒü‚Ì‹t‚Ì²‡A
	DIR_TBL_MAX
};

enum SIDE_CHECK {
	OUT_SIDE,	// 0
	IN_SIDE,	// 1
	SIDE_MAX
};

enum PL_NUMBER {
	PL_1,
	PL_2,
	PL_3,
	PL_4,
	PL_MAX
};

constexpr int PL_DEF_SPEED = 5;
constexpr int PL_DASH_SPEED = 10;

using DIR_TBL_ARY = std::array<int, DIR_MAX>;
using DIR_TBL_A2D = std::array<int[2], DIR_MAX>;
using DIR_TBL_PTR = std::array<int*[TBL_MAX], DIR_MAX>;
using DIR_TBL_DIR = std::array<DIR[DIR_TBL_MAX], DIR_MAX>;
using MAP_MOVE_TBL = std::array<bool, static_cast<int>(MAP_ID::MAX)>; // ©±²ÃÑ‚âáŠQ•¨‚ğ’Ç‰Á‚µ‚½‚Æ‚«‚Ég‚¤


class Player :
	public Obj
{
public:
	Player(PL_NUMBER plNum, VECTOR2 setUpPos, VECTOR2 drawOffset);	// ˆø”•t‚«ºİ½Ä×¸À°
	Player();
	~Player();
	bool initAnim(void);		// ±ÆÒ°¼®İŠÇ—
private:
	void SetMove(const GameCtrl &controller, weakListObj objList);
	bool CheckObjType(OBJ_TYPE type);
	bool DeathPrc(void);			// ŠÖ”‰»

	int speed;
	DIR dir;

// ---------- Ã°ÌŞÙ”z—ñ ------------
	DIR_TBL_ARY keyIdTbl;		// ˆÚ“®•ûŒü
	DIR_TBL_PTR PosTbl;			// Îß²İÀ‚ğ’¼ÚŠi”[
	DIR_TBL_A2D SpeedTbl;		// ˆÚ“®‘¬“x
	DIR_TBL_DIR DirTbl;			// ˆÚ“®§Œä
	MAP_MOVE_TBL mapMoveTbl;	// ˆÚ“®§Œä,ˆÚ“®‰Â”\µÌŞ¼Şª¸Ä‚È‚çtrue‚ğ•Ô‚·©±²ÃÑ‚âáŠQ•¨‚ğ’Ç‰Á‚µ‚½‚Æ‚«‚Ég‚¤

	bool afterKeyFlag;			// key‚ÌŒã“ü—Í‚ğ—Dæ‚³‚¹‚éÌ×¸Ş
	PL_NUMBER plNum;
};

