#include "DxLib.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "MenuScene.h"

TitleScene::TitleScene()
{

}

TitleScene::~TitleScene()
{

}

uniqueBase TitleScene::UpDate(uniqueBase own, const GameCtrl & controller)
{
	auto cnt = controller.GetCtrl(KEY_TYPE_NOW);
	auto cntOld = controller.GetCtrl(KEY_TYPE_OLD);
	if ((cnt[KEY_INPUT_F1]) & (!cntOld[KEY_INPUT_F1]))
	{
		return std::make_unique<MenuScene>();
	}
	TitleDraw();
	return std::move(own);
}

void TitleScene::TitleDraw(void)
{
	ClsDrawScreen();


	DrawString(0, 0, "TitleScene", 0x0000ff00);

	ScreenFlip();
}

int TitleScene::Init(void)
{
	return 0;
}
