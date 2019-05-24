#include <DxLib.h>
#include "GameScene.h"
#include "ScoreBoard.h"
#include "ImageMng.h"


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
		if (score >= 10000)
		{
			score = 10000;
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
	case DATA_POWER:
		power += val;
		if (power > 3)
		{
			power = 3;
		}
		break;
	case DATA_GUARD:
		guard += val;
		if (guard > 3)
		{
			guard = 3;
		}
		break;
	case DATA_INV:
		inv += val;
		break;
	case DATA_BONUS:
		bonus += val;
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
	case DATA_POWER:
		return power;
		break;
	case DATA_GUARD:
		return guard;
		break;
	case DATA_INV:
		return inv;
		break;
	case DATA_BONUS:
		return bonus;
		break;
	}
	return 0;
}

void ScoreBoard::DataInit(void)
{
	static int score = 0;
	life = PL_LIFE_MAX;
	power = 1;
	guard = 0;
	inv = 0;
	bonus = 0;
}

void ScoreBoard::Draw(void)
{
	int digit = 0;
	int additionTime = 30;
	if (oldScore < score)
	{
		oldScore++;
	}
	int numTemp = oldScore * 100;
	DrawBox(640, 0, 800, 300, GetColor(255, 255, 0), true);
	DrawFormatString(650, 0, GetColor(0, 0, 0), "SCORE");
	DrawFormatString(650, 50, GetColor(0, 0, 0), "LIFE  : %d", life);
	DrawFormatString(650, 100, GetColor(0, 0, 0), "POWER  : %d", power);
	DrawFormatString(650, 120, GetColor(0, 0, 0), "GUARD  : %d", guard);
	DrawFormatString(650, 140, GetColor(0, 0, 0), "INV  : %d", inv);
	DrawFormatString(650, 160, GetColor(0, 0, 0), "BONUS  : %d", bonus);
	if (numTemp == 0)
	{
		DrawGraph(GAME_SCREEN_SIZE_X / 2 - 50, 15, lpImageMng.GetID("image/number.png", { 40,30 }, { 10,1 })[0], true);
	}
	while (numTemp > 0)
	{
		DrawGraph(GAME_SCREEN_SIZE_X / 2 -(digit + 1) * 20 - (30),15, lpImageMng.GetID("image/number.png", { 40,30 }, { 10,1 })[numTemp % 10], true);
		numTemp /= 10;
		digit++;
	}
}
