#pragma once
#include "BaseScene.h"
#include "Selector.h"

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
	uniqueBase UpDate(						// 更新
		uniqueBase own,					// 現在のｼｰﾝ
		const GameCtrl &controller		// ｷｰ取得
	);
private:
	void ResultDraw(void);		// 描画
	int Init(void);				// 初期化 

	BONUS_POINT bonusPoint;		// ﾌﾟﾚｲﾔｰ毎のﾎﾞｰﾅｽ獲得数
	RESULT_SCORE resultScore;	// ﾎﾞｰﾅｽ加算後の最終ｽｺｱ
	int beforeScore;			// 演出用の最終決定前ｽｺｱ
	int plNumber;				// ﾌﾟﾚｲﾔｰ数
	std::array<CHARA_TYPE,4> plSelChara;		// ﾌﾟﾚｲﾔｰの選んだｷｬﾗ
	int resultTemp;				// ｽｺｱ(描画用)
	int waitTime;				// 加算待ち時間
};

