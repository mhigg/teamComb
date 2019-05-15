#include <DxLib.h>
#include "GameScene.h"
#include "ScoreBoard.h"


ScoreBoard::ScoreBoard()
{
	DataInit();
}

ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::SetScore(SCORE_DATA data,int val)
{
	switch (data)
	{
	case DATA_SCORE:
		score += val;
		if (score < 0)
		{
			score = 0;
		}
		break;
	case DATA_LIFE:
		if (life + val >= PL_LIFE_MAX)
		{
			life = PL_LIFE_MAX;
		}
		else
		{
			life += val;
		}
		break;
	}
}

int ScoreBoard::GetScore(SCORE_DATA data)
{
	switch (data)
	{
	case DATA_SCORE:
		return score;
		break;
	case DATA_LIFE:
		return life;
		break;
	}
	return -1;
}

void ScoreBoard::DataInit(void)
{
	score = 0;
	life = PL_LIFE_MAX;
}

void ScoreBoard::Draw(void)
{
	DrawBox(640, 0, 800, 300, GetColor(255, 255, 0), true);
	DrawFormatString(650, 10, GetColor(0, 0, 0), "SCORE : %d", score);
	DrawFormatString(650, 50, GetColor(0, 0, 0), "LIFE  : %d", life);
}
