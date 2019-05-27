#pragma once
#include "BaseScene.h"

constexpr int PLAYER_MAX = 4;

using BONUS_POINT = std::array< int, PLAYER_MAX >;
using RESULT_SCORE = std::array< int, PLAYER_MAX >;

class ResultScene :
	public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	uniqueBase UpDate(						// 更新
		uniqueBase own,					// 現在のｼｰﾝ
		const GameCtrl &controller		// ｷｰ取得
	);
private:
	void ResultDraw(void);		// 描画
	int Init(void);				// 初期化 

	BONUS_POINT bonusPoint;		// ﾌﾟﾚｲﾔｰ毎のﾎﾞｰﾅｽ獲得数
	RESULT_SCORE resultScore;	// ﾎﾞｰﾅｽ加算後の最終ｽｺｱ
};

