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
	void SetScore(SCORE_DATA data, int val);		// ½º±‰ÁZŒ¸Z—p
	int GetScore(SCORE_DATA data);					// ½º±æ“¾
	void DataInit(void);	// ‰Šú‰»
	void Draw(void);		// •`‰æ
private:
	ScoreBoard();
	~ScoreBoard();
	int score;			// “¾“_
	int life;			// ‘Ì—Í
	int power;			// UŒ‚—Í	
	int guard;			// –hŒä—Í	
	int inv;			// –³“G	
	int bonus;			// ÎŞ°Å½
	int oldScore;		// ’¼‘O‚Ì½º±
	int additionTime;	// ‰ÁZ‚·‚é‚Ü‚Å‚ÌŠÔ
};

