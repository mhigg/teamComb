#include "MenuScene.h"
#include "GameScene.h"


MenuScene::MenuScene()
{
}


MenuScene::~MenuScene()
{
}

uniqueBase MenuScene::UpDate(uniqueBase own, const GameCtrl & controller)
{
	auto cnt = controller.GetCtrl(KEY_TYPE_NOW);
	auto cntOld = controller.GetCtrl(KEY_TYPE_OLD);
	if ((cnt[KEY_INPUT_RETURN]) & (!cntOld[KEY_INPUT_RETURN]))
	{
		return std::make_unique<GameScene>();
	}
	MenuDraw();
	return std::move(own);
}

void MenuScene::MenuDraw(void)
{
	ClsDrawScreen();

	DrawString(0, 0, "MenuScene", 0x0000ff00);

	ScreenFlip();
}

int MenuScene::Init(void)
{
	return 0;
}
