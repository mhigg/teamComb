#pragma once
#include "Obj.h"


enum SCORE_DATA
{
	DATA_SCORE,
	DATA_LIFE,
	DATA_POWER,
	DATA_GUARD,
	DATA_INV,
	DATA_BONUS,
	DATA_MAX
};

#define lpScoreBoard ScoreBoard::GetInstance()

constexpr int PL_LIFE_MAX = 6;

class ScoreBoard 
{
public:
	static ScoreBoard &GetInstance(void)
	{
		static ScoreBoard s_Instance;
		return s_Instance;
	}
	void SetScore(SCORE_DATA data, int val);		// ｽｺｱ加算減算用
	int GetScore(SCORE_DATA data);					// ｽｺｱ取得
	void DataInit(void);	// 初期化
	void Draw(void);		// 描画
private:
	ScoreBoard();
	~ScoreBoard();
	int score;			// 得点
	int life;			// 体力
	int power;			// 攻撃力	
	int guard;			// 防御力	
	int inv;			// 無敵	
	int bonus;			// ﾎﾞｰﾅｽ
	int oldScore;		// 直前のｽｺｱ
	int additionTime;	// 加算するまでの時間
};

