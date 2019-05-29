#include "SelectScene.h"
#include "GameScene.h"
#include "ImageMng.h"
#include "EditScene.h"
#include "MenuScene.h"
#include "GameCtrl.h"

SelectScene::SelectScene()
{
	SelectScene::Init();
}


SelectScene::~SelectScene()
{
}

uniqueBase SelectScene::UpDate(uniqueBase own, const GameCtrl & controller)
{
	auto &inputState = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputStateOld = controller.GetInputState(KEY_TYPE_OLD);
	auto cnt = controller.GetCtrl(KEY_TYPE_NOW);
	auto cntOld = controller.GetCtrl(KEY_TYPE_OLD);

	if ((cnt[KEY_INPUT_F1]) & (!cntOld[KEY_INPUT_F1]))
	{
		return std::make_unique<EditScene>();
	}
	if (inputState[0][XINPUT_START] & !inputStateOld[0][XINPUT_START])
	{
		return std::make_unique<EditScene>();
	}
	// BACK(ç∂SHIFT)Ç≈“∆≠∞Ç÷ñﬂÇÈ
	if ((cnt[KEY_INPUT_LSHIFT]) & (!cntOld[KEY_INPUT_LSHIFT]))
	{
		return std::make_unique<MenuScene>();
	}
	if (inputState[0][XINPUT_PAUSE] & !inputStateOld[0][XINPUT_PAUSE])
	{
		return std::make_unique<MenuScene>();
	}

	// ëIë
	for (int i = 0; i < GetJoypadNum(); i++)
	{
	if (inputState[i][XINPUT_RIGHT] & !inputStateOld[i][XINPUT_RIGHT])
		{
			if (selectChara[i] < CHARA_NUM - 1)
			{
				selectChara[i] += 1;
			}
		}
	if (inputState[i][XINPUT_LEFT] & !inputStateOld[i][XINPUT_LEFT])		{
			if (selectChara[i] > 0)
			{
				selectChara[i] -= 1;
			}
		}
	}
	SelectDraw();
	return std::move(own);
}

void SelectScene::SelectDraw(void)
{
	ClsDrawScreen();
	DrawGraph(0, 0, IMAGE_ID("image/menu.png")[0], true);

	VECTOR2 tmp1(0, 0);
	VECTOR2 tmp2(0, GAME_SCREEN_SIZE_Y);

	for (; tmp1.x <= GAME_SCREEN_SIZE_X; tmp1.x += 800)
	{
		tmp2.x = tmp1.x;
		DrawLine(tmp1, tmp2, 0x00ffffff, true);
	}
	tmp1 = VECTOR2(0, 0);
	tmp2.x = GAME_SCREEN_SIZE_X;
	for (; tmp1.y <= GAME_SCREEN_SIZE_Y; tmp1.y += 480)
	{
		tmp2.y = tmp1.y;
		DrawLine(tmp1, tmp2, 0x00ffffff, true);
	}
	DrawString(0, 0, "SelectScene", 0x00ff0000);

	if (GetJoypadNum() > 0)
	{
		DrawGraph(20, 20, IMAGE_ID("image/p1.png")[0], true);
	}
	if (GetJoypadNum() > 1)
	{
		DrawGraph(820, 20, IMAGE_ID("image/p2.png")[0], true);
	}
	if (GetJoypadNum() > 2)
	{
		DrawGraph(20, 500, IMAGE_ID("image/p3.png")[0], true);
	}
	if (GetJoypadNum() > 3)
	{
		DrawGraph(820, 500, IMAGE_ID("image/p4.png")[0], true);
	}

	// Ãﬂ⁄≤‘∞ÇÃêîï™óßÇøäGï`âÊ
	for (int i = 0; i < GetJoypadNum(); i++)
	{
		if (selectChara[i] == 0)
		{
			DrawGraph(selectPos[i].x, selectPos[i].y, IMAGE_ID("image/stand.png")[0], true);
		}
		if (selectChara[i] == 1)
		{
			DrawGraph(selectPos[i].x, selectPos[i].y, IMAGE_ID("image/stand2.png")[0], true);
		}
		if (selectChara[i] == 2)
		{
			DrawGraph(selectPos[i].x, selectPos[i].y, IMAGE_ID("image/stand3.png")[0], true);
		}
	}
	ScreenFlip();
}

int SelectScene::Init(void)
{
	selectChara = {
		0,0,0,0,
	};
	selectPos = {
		VECTOR2(100,100),
		VECTOR2(900,100),
		VECTOR2(100,580),
		VECTOR2(900,580),
	};
	backChange = 0;
	return 0;
}
