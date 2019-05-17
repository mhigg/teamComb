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
	auto &inputState = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputStateOld = controller.GetInputState(KEY_TYPE_OLD);
	
	for (int i = 0; i < MENU_NUM; i++)
	{
		add = -1.25 * ((count - (i * 1)*(i * 1) - 75)*(count - (i * 1)*(i * 1) - 75)) + 68;
		add >= -20 ? movePos[i].x += static_cast<int>(add) : movePos[i].x;
	}
	count++;
	if ((count > 80) && (!pushFlag))
	{
		selectPoint[0] = PUSH_SIZE;
		pushFlag = true;
	}

	// キー操作が可能になってからの処理
	if (pushFlag)
	{
		// 選択
		if (inputState[0][static_cast<int>(INPUT_ID::DOWN)] & !inputStateOld[0][static_cast<int>(INPUT_ID::DOWN)])
		{
			if (nowSelect < MENU_NUM - 1)
			{
				selectPoint[nowSelect] = 0;
				selectPoint[nowSelect + 1] = PUSH_SIZE;
				nowSelect += 1;

			}
		}
		else if (inputState[0][static_cast<int>(INPUT_ID::UP)] & !inputStateOld[0][static_cast<int>(INPUT_ID::UP)])
		{
			if (nowSelect > 0)
			{
				selectPoint[nowSelect] = 0;
				selectPoint[nowSelect - 1] = PUSH_SIZE;
				nowSelect -= 1;
			}
		}

		// ｼｰﾝ移行
		if (nowSelect != 2)
		{
			if ((cnt[KEY_INPUT_F1]) & (!cntOld[KEY_INPUT_F1]))
			{
				return std::make_unique<EditScene>();
			}
			if (inputState[0][static_cast<int>(INPUT_ID::START)] & !inputStateOld[0][static_cast<int>(INPUT_ID::START)])
			{
				return std::make_unique<EditScene>();
			}
		}
		else
		{
			if ((cnt[KEY_INPUT_F1]) & (!cntOld[KEY_INPUT_F1]))
			{
				descriptionFlag = true;
			}
			if (inputState[0][static_cast<int>(INPUT_ID::START)] & !inputStateOld[0][static_cast<int>(INPUT_ID::START)])
			{
				descriptionFlag = true;
			}
		}
		
		if (descriptionFlag)
		{
			if ((cnt[KEY_INPUT_Z]) & (!cntOld[KEY_INPUT_Z]))
			{
				selectPoint[nowSelect] = 0;
				nowSelect = 0;
				selectPoint[nowSelect] = 20;
				descriptionFlag = false;
			}
			if (inputState[0][static_cast<int>(INPUT_ID::ATT)] & !inputStateOld[0][static_cast<int>(INPUT_ID::ATT)])
			{
				selectPoint[nowSelect] = 0;
				nowSelect = 0;
				selectPoint[nowSelect] = 20;
				descriptionFlag = false;
			}
		}
	}
	MenuDraw();
	return std::move(own);
}

void MenuScene::MenuDraw(void)
{
	ClsDrawScreen();
	if(!descriptionFlag)
	{
		DrawGraph(0, 0, IMAGE_ID("image/menu1.png")[0], true);
		for (int i = 0; i < MENU_NUM; i++)
		{
			DrawGraph(movePos[i].x - size.x + selectPoint[i], movePos[i].y + (i * size.y), lpImageMng.GetID("image/menu2.png", {460,180}, {1,3})[i], true);
		}
	}
	else
	{
		DrawGraph(0, 0, IMAGE_ID("image/haikei.png")[0], true);
		DrawGraph(0, 0, IMAGE_ID("image/setumei.png")[0], true);
	}
	ScreenFlip();
}

int MenuScene::Init(void)
{
	movePos = {
		VECTOR2(0,130),
		VECTOR2(0,290),
		VECTOR2(0,450),
	};
	moveFlag = {
		true,false,false
	};
	selectPoint = {
		0,0,0
	};
	count = 0;
	size = { BOX_SIZE_X,SIZE_Y };
	add = 0;
	nowSelect = 0;
	descriptionFlag = false;
	pushFlag = false;
	return 0;
}
