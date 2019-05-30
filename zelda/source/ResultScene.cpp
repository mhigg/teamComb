#include <DxLib.h>
#include "ResultScene.h"
#include "ImageMng.h"
#include "GameScene.h"
#include "InfoCtrl.h"

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
	plNumber = GetJoypadNum();

	for (int i = 0; i < plNumber; i++)
	{
		resultScore[i] = lpInfoCtrl.GetScore(i);
		bonusPoint[i] = lpInfoCtrl.GetBonus(i);
	}

	ResultDraw();
	return move(own);
}

void ResultScene::ResultDraw(void)
{
	ClsDrawScreen();
	if (plNumber > 0)
	{
		DrawGraph(220, 200, IMAGE_ID("image/p1.png")[0], true);
	}
	if (plNumber > 1)
	{
		DrawGraph(570, 200, IMAGE_ID("image/p2.png")[0], true);
	}
	if (plNumber > 2)
	{
		DrawGraph(920, 200, IMAGE_ID("image/p3.png")[0], true);
	}
	if (plNumber > 3)
	{
		DrawGraph(1270, 200, IMAGE_ID("image/p4.png")[0], true);
	}
	DrawGraph(525, 50, IMAGE_ID("image/result.png")[0], true);
	DrawString(0, 0, "ResultScene", 0x00ff0000);

	int digit = 0;

	for (int i = 0; i < plNumber; i++)
	{
		resultTemp = resultScore[i] * 10;
		if (resultTemp == 0)
		{
			DrawGraph((1 + i) * 280, 700, lpImageMng.GetID("image/number.png", VECTOR2(40, 30), VECTOR2(10, 1))[0], true);
		}
		while (resultTemp > 0)
		{
			DrawGraph((0 + i) - (digit + 1) * 20 + (300), 700, lpImageMng.GetID("image/number.png", VECTOR2(40, 30), VECTOR2(10, 1))[resultTemp % 10], true);
			resultTemp /= 10;
			digit++;
		}
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
	plNumber = 0;
	resultTemp = 0;
	return 0;
}
