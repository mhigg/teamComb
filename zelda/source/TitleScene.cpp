#include "DxLib.h"
#include "TitleScene.h"
#include "ImageMng.h"
#include "GameScene.h"
#include "MenuScene.h"
#include"GameCtrl.h"


TitleScene::TitleScene()
{
	TitleScene::Init();
}

TitleScene::~TitleScene()
{

}

uniqueBase TitleScene::UpDate(uniqueBase own, const GameCtrl & controller)
{
	auto &inputState = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputStateOld = controller.GetInputState(KEY_TYPE_OLD);
	auto cnt = controller.GetCtrl(KEY_TYPE_NOW);
	auto cntOld = controller.GetCtrl(KEY_TYPE_OLD);
	if ((cnt[KEY_INPUT_F1]) & (!cntOld[KEY_INPUT_F1]))
	{
		return std::make_unique<MenuScene>();
	}
	if (inputState[0][static_cast<int>(INPUT_ID::START)] & !inputStateOld[0][static_cast<int>(INPUT_ID::START)])
	{
		return std::make_unique<MenuScene>();
	}
	TitleDraw();
	TitleScene:: cnt++;
	return std::move(own);
}

void TitleScene::TitleDraw(void)
{
	ClsDrawScreen();
	DrawGraph(0, 0, IMAGE_ID("image/title.png")[0], true);
	if (cnt / 20 % 3)
	{

	}
	ScreenFlip();
}

int TitleScene::Init(void)
{
	cnt = 0;
	return 0;
}
