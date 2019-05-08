#include <DxLib.h>
#include "MenuScene.h"
#include "GameScene.h"
#include "EditScene.h"


MenuScene::MenuScene()
{
	MenuScene::Init();
}


MenuScene::~MenuScene()
{
}

uniqueBase MenuScene::UpDate(uniqueBase own, const GameCtrl & controller)
{
	auto cnt = controller.GetCtrl(KEY_TYPE_NOW);
	auto cntOld = controller.GetCtrl(KEY_TYPE_OLD);
	if ((cnt[KEY_INPUT_F1]) & (!cntOld[KEY_INPUT_F1]))
	{
		return std::make_unique<EditScene>();
	}
	MenuDraw();
	return std::move(own);
}

void MenuScene::MenuDraw(void)
{
	auto move = [&]() {};
	ClsDrawScreen();

	DrawString(0, 0, "MenuScene", 0x0000ff00);

	DrawBox(100, 40, 300, 120, 0x00ff0000, true);

	ScreenFlip();
}

int MenuScene::Init(void)
{
	movePos = {
		VECTOR2(0,0),
		VECTOR2(0,0),
		VECTOR2(0,0),
		VECTOR2(0,0)
	};
	moveFlag = { true,false,false,false };
	return 0;
}
