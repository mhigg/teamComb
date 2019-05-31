#include <DxLib.h>
#include "ImageMng.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "MenuScene.h"
#include "TitleScene.h"
#include "GameCtrl.h"
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
	auto ctrl = controller.GetCtrl(KEY_TYPE_NOW);
	auto ctrlOld = controller.GetCtrl(KEY_TYPE_OLD);
	auto &inputState = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputStateOld = controller.GetInputState(KEY_TYPE_OLD);
	plNumber = GetJoypadNum();

	for (int i = 0; i < plNumber; i++)
	{
		resultScore[i] = lpInfoCtrl.GetScore(i);
		bonusPoint[i] = lpInfoCtrl.GetBonus(i);
	}

	if (ctrl[KEY_INPUT_F1] & ~ctrlOld[KEY_INPUT_F1])
	{
		return std::make_unique< TitleScene>();
	}
	if (inputState[0][XINPUT_START] & !inputStateOld[0][XINPUT_START])
	{
		return std::make_unique<TitleScene>();
	}

	ResultDraw();
	return move(own);
}

void ResultScene::ResultDraw(void)
{
	ClsDrawScreen();
	DrawGraph(0, 0, IMAGE_ID("image/menu1.png")[0], true);
	int digit = 0;
	// 1人ﾌﾟﾚｲの時
	if (plNumber == 1)
	{
		resultTemp = resultScore[0] * 10;
		DrawGraph(GAME_SCREEN_SIZE_X / 2 - 36, 200, IMAGE_ID("image/p1.png")[0], true);
		DrawGraph(GAME_SCREEN_SIZE_X / 2 - 66, 680, IMAGE_ID("image/score.png")[0], true);
		DrawGraph(GAME_SCREEN_SIZE_X / 2 - 120, 290, IMAGE_ID("image/stand.png")[0], true);
		if (resultTemp == 0)
		{
			DrawGraph(GAME_SCREEN_SIZE_X / 2 + 35, 720, lpImageMng.GetID("image/number.png", VECTOR2(40, 30), VECTOR2(10, 1))[0], true);
		}
		while (resultTemp > 0)
		{
			DrawGraph(- (digit + 1) * 20 + (GAME_SCREEN_SIZE_X / 2 + 55), 720, lpImageMng.GetID("image/number.png", VECTOR2(40, 30), VECTOR2(10, 1))[resultTemp % 10], true);
			resultTemp /= 10;
			digit++;
		}
	}
	// 対戦(2人以上の時)
	if (plNumber > 1)
	{
		DrawGraph(220, 200, IMAGE_ID("image/p1.png")[0], true);
		DrawGraph(195, 680, IMAGE_ID("image/score.png")[0], true);
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

	for (int i = 0; i < plNumber; i++)
	{
		// 立ち絵表示
		if (plNumber > 1)
		{
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
			// ｽｺｱ表示
			resultTemp = resultScore[i] * 10;
			if (resultTemp == 0)
			{
				DrawGraph((i + 1) * 300, 720, lpImageMng.GetID("image/number.png", VECTOR2(40, 30), VECTOR2(10, 1))[0], true);
			}
			while (resultTemp > 0)
			{
				DrawGraph((0 + i) - (digit + 1) * 20 + (320), 720, lpImageMng.GetID("image/number.png", VECTOR2(40, 30), VECTOR2(10, 1))[resultTemp % 10], true);
				resultTemp /= 10;
				digit++;
			}
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

	plNumber = 0;
	resultTemp = 0;
	return 0;
}