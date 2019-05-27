#pragma once
#include "BaseScene.h"

constexpr int PLAYER_MAX = 4;

using BONUS_POINT = std::array< int, PLAYER_MAX >;

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
};

