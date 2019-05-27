#include <DxLib.h>
#include "ResultScene.h"
#include "ImageMng.h"
#include "GameScene.h"
#include "ScoreBoard.h"

ResultScene::ResultScene()
{
	ResultScene::Init();
}

ResultScene::~ResultScene()
{
}

uniqueBase ResultScene::UpDate(uniqueBase own, const GameCtrl & controller)
{
	auto cnt = controller.GetCtrl(KEY_TYPE_NOW);
	auto cntOld = controller.GetCtrl(KEY_TYPE_OLD);
	auto &inputState = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputStateOld = controller.GetInputState(KEY_TYPE_OLD);

	/*bonusPoint[0] = lpScoreBoard.GetScore(DATA_BONUS);

	resultScore[0] = lpScoreBoard.GetScore(DATA_SCORE);*/

	ResultDraw();
	return move(own);
}

void ResultScene::ResultDraw(void)
{
	ClsDrawScreen();
	DrawGraph(220, 100, IMAGE_ID("image/p1.png")[0], true);
	DrawGraph(570, 100, IMAGE_ID("image/p2.png")[0], true);
	DrawGraph(920, 100, IMAGE_ID("image/p3.png")[0], true);
	DrawGraph(1270, 100, IMAGE_ID("image/p4.png")[0], true);
	DrawString(0, 0, "ResultScene", 0x00ff0000);

	int digit = 0;
	int numTemp = resultScore[0] * 100;
	if (numTemp == 0)
	{
		DrawGraph(300 - 50, 500, lpImageMng.GetID("image/number.png", { 40,30 }, { 10,1 })[0], true);
	}
	while (numTemp > 0)
	{
		DrawGraph(300 - (digit + 1) * 20 - (30), 500, lpImageMng.GetID("image/number.png", { 40,30 }, { 10,1 })[numTemp % 10], true);
		numTemp /= 10;
		digit++;
	}
	ScreenFlip();
}

int ResultScene::Init(void)
{
	bonusPoint = {
		0,0,0,0
	};
	resultScore = {
		0,0,0,0
	};
	return 0;
}
