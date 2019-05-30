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
		beforeScore = resultScore[i] * 10;
		bonusPoint[i] = lpInfoCtrl.GetBonus(i);
	}

	ResultDraw();
	return move(own);
}

void ResultScene::ResultDraw(void)
{
	ClsDrawScreen();
	DrawGraph(0, 0, IMAGE_ID("image/menu1.png")[0], true);
	if (plNumber > 0)
	{
		DrawGraph(220, 200, IMAGE_ID("image/p1.png")[0], true);
		DrawGraph(195, 680, IMAGE_ID("image/score.png")[0], true);
	}
	if (plNumber > 1)
	{
		DrawGraph(570, 200, IMAGE_ID("image/p2.png")[0], true);
		DrawGraph(545, 680, IMAGE_ID("image/score.png")[0], true);
	}
	if (plNumber > 2)
	{
		DrawGraph(920, 200, IMAGE_ID("image/p3.png")[0], true);
		DrawGraph(895, 680, IMAGE_ID("image/score.png")[0], true);
	}
	if (plNumber > 3)
	{
		DrawGraph(1270, 200, IMAGE_ID("image/p4.png")[0], true);
		DrawGraph(1245, 680, IMAGE_ID("image/score.png")[0], true);
	}
	DrawGraph(525, 50, IMAGE_ID("image/result.png")[0], true);
	DrawString(0, 0, "ResultScene", 0x00ff0000);

	int digit = 0;

	for (int i = 0; i < plNumber; i++)
	{
		// —§‚¿ŠG•\Ž¦
		plSelChara[i] = lpInfoCtrl.GetSelectChara(i);
		if (plSelChara[i] == CHARA_MAFIA)
		{
			DrawGraph(140 + (i * 350), 290, IMAGE_ID("image/stand.png")[0], true);
		}
		if (plSelChara[i] == CHARA_GIRL)
		{
			DrawGraph(140 + (i * 350), 290, IMAGE_ID("image/stand2.png")[0], true);
		}
		if (plSelChara[i] == CHARA_OTHER)
		{
			DrawGraph(140 + (i * 350), 290, IMAGE_ID("image/stand3.png")[0], true);
		}
		if (plSelChara[i] == CHARA_OTHER2)
		{
			DrawGraph(140 + (i * 350), 290, IMAGE_ID("image/stand3.png")[0], true);
		}
		// ½º±•\Ž¦
		if (resultTemp == 0)
		{
			DrawGraph((1 + i) * 300, 720, lpImageMng.GetID("image/number.png", VECTOR2(40, 30), VECTOR2(10, 1))[0], true);
		}
		while (resultTemp > 0)
		{
			DrawGraph((0 + i) - (digit + 1) * 20 + (320), 720, lpImageMng.GetID("image/number.png", VECTOR2(40, 30), VECTOR2(10, 1))[resultTemp % 10], true);
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
	plSelChara = {
		CHARA_MAX,CHARA_MAX,CHARA_MAX,CHARA_MAX
	};
	beforeScore = 0;
	plNumber = 0;
	resultTemp = 0;
	return 0;
}