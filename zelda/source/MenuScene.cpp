#include <DxLib.h>
#include "MenuScene.h"
#include "GameScene.h"
#include "EditScene.h"
#include "ImageMng.h"


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
	for (int i = 0; i < MENU_NUM; i++)
	{
		add = -1.25 * ((count - (i * 1)*(i * 1) - 50)*(count - (i * 1)*(i * 1) - 50)) + 40;
		add >= -20 ? movePos[i].x += add : movePos[i].x;
	}
	count++;
	MenuDraw();
	return std::move(own);
}

void MenuScene::MenuDraw(void)
{
	ClsDrawScreen();
	DrawGraph(0, 0, IMAGE_ID("image/menu.png")[0], true);
	for (int i = 0; i < MENU_NUM; i++)
	{
		DrawBox(movePos[i].x - size.x, movePos[i].y, movePos[i].x, movePos[i].y + size.y, 0x00ff0000, true);
	}
	ScreenFlip();
}

int MenuScene::Init(void)
{
	movePos = {
		VECTOR2(0,40),
		VECTOR2(0,160),
		VECTOR2(0,280),
	};
	moveFlag = { 
		true,false,false
	};
	count = 0;
	size = { BOX_SIZE_X,BOX_SIZE_Y };
	add = 0;
	return 0;
}
