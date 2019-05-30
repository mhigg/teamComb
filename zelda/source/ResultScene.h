#pragma once
#include "BaseScene.h"

constexpr int PLAYER_MAX = 4;

enum SCORE_RUNK{
	RUNK1,
	RUNK2,
	RUNK3,
	RUNK4,
	RUNK_MAX
};

using BONUS_POINT = std::array< int, PLAYER_MAX >;
using RESULT_SCORE = std::array< int, PLAYER_MAX >;

class ResultScene :
	public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	uniqueBase UpDate(						// XV
		uniqueBase own,					// Œ»İ‚Ì¼°İ
		const GameCtrl &controller		// ·°æ“¾
	);
private:
	void ResultDraw(void);		// •`‰æ
	int Init(void);				// ‰Šú‰» 

	BONUS_POINT bonusPoint;		// ÌßÚ²Ô°–ˆ‚ÌÎŞ°Å½Šl“¾”
	RESULT_SCORE resultScore;	// ÎŞ°Å½‰ÁZŒã‚ÌÅI½º±
	int plNumber;				// ÌßÚ²Ô°”
	int resultTemp;				// ½º±(•`‰æ—p)
};

