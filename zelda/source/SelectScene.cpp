#include "SelectScene.h"
#include "GameScene.h"
#include "ImageMng.h"
#include "EditScene.h"

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
	if (inputState[0][static_cast<int>(INPUT_ID::START)] & !inputStateOld[0][static_cast<int>(INPUT_ID::START)])
	{
		return std::make_unique<EditScene>();
	}

	// �I��
	if (inputState[0][static_cast<int>(INPUT_ID::RIGHT)] & !inputStateOld[0][static_cast<int>(INPUT_ID::RIGHT)])
	{
		if (nowChara < CHARA_NUM - 1)
		{
			selectChara[nowChara] = false;
			selectChara[nowChara + 1] = true;
			nowChara += 1;
		}
	}
	if (inputState[0][static_cast<int>(INPUT_ID::LEFT)] & !inputStateOld[0][static_cast<int>(INPUT_ID::LEFT)])
	{
		if (nowChara > 0)
		{
			selectChara[nowChara] = false;
			selectChara[nowChara - 1] = true;
			nowChara -= 1;
		}
	}
	SelectDraw();
	return std::move(own);
}

void SelectScene::SelectDraw(void)
{
	ClsDrawScreen();
	DrawGraph(0, 0, IMAGE_ID("image/menu1.png")[0], true);
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
	DrawGraph(20, 20, IMAGE_ID("image/p1.png")[0], true);
	DrawGraph(820, 20, IMAGE_ID("image/p2.png")[0], true);
	if (selectChara[0])
	{
		DrawGraph(100, 100, IMAGE_ID("image/tatie.png")[0], true);
	}
	ScreenFlip();
}

int SelectScene::Init(void)
{
	selectChara = {
		true,false,false,false,
	};
	nowChara = 0;
	return 0;
}
