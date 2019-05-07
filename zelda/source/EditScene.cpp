#include "DxLib.h"
#include <windows.h>
#include "SceneMng.h"
#include "EditScene.h"
#include "MapCtrl.h"
#include "ImageMng.h"
#include "EditCursor.h"
#include "GameCtrl.h"
#include "GameScene.h"
#include "StageMng.h"

EditScene::EditScene()
{
	menuFlag = false;
	EditScene::Init();
}

EditScene::~EditScene()
{
}

uniqueBase EditScene::UpDate(uniqueBase own, const GameCtrl & controller)
{
	auto cnt = controller.GetCtrl(KEY_TYPE_NOW);
	auto cntOld = controller.GetCtrl(KEY_TYPE_OLD);
	/*if (cnt[KEY_INPUT_M] & (!cntOld[KEY_INPUT_M]))
	{
		if (menuFlag)
		{
			menuFlag = false;
		}
		else
		{
			menuFlag = true;
		}
	}*/
	if (!menuFlag)
	{
		if (cnt[KEY_INPUT_F5])
		{
			// ﾛｰﾄﾞ
			if (MessageBox(
				NULL,
				"エディット内容をロードしますか？",
				"確認ダイアログ",
				MB_OKCANCEL
			) == IDOK)
			{
				lpStageMng.MapLoad(objList, true);
			}
		}
		if (cnt[KEY_INPUT_F6])
		{
			// ｾｰﾌﾞ
			if (MessageBox(
				NULL,
				"エディット内容をセーブしますか？",
				"確認ダイアログ",
				MB_OKCANCEL
			) == IDOK)
			{
				lpStageMng.MapSave();
			}
		}
		if (cnt[KEY_INPUT_F1] & (!cntOld[KEY_INPUT_F1]))
		{
			return std::make_unique<GameScene>();
		}
	}
	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpDate(controller, objList);
	}
	EditDraw();
	return std::move(own);
}

bool EditScene::EditDraw(void)
{
	ClsDrawScreen();
	if (menuFlag)
	{
		SetDrawBright(100, 100, 100);
	}
	else
	{
		SetDrawBright(255, 255, 255);
	}
	lpMapCtrl.Draw(true);
	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->Draw();
	}
	VECTOR2 tmp1(0, 0);
	VECTOR2 tmp2(0, GAME_SCREEN_SIZE_Y);
	VECTOR2 offset(VECTOR2(0, 0));

	for (; tmp1.x <= GAME_SCREEN_SIZE_X; tmp1.x += CHIP_SIZE)
	{
		tmp2.x = tmp1.x;
		DrawLine(offset + tmp1, offset + tmp2, 0x00ffffff, true);
	}
	tmp1 = VECTOR2(0, 0);
	tmp2.x = GAME_SCREEN_SIZE_X;
	for (; tmp1.y <= GAME_SCREEN_SIZE_Y; tmp1.y += CHIP_SIZE)
	{
		tmp2.y = tmp1.y;
		DrawLine(offset + tmp1, offset + tmp2, 0x00ffffff, true);
	}
	/*if (menuFlag)
	{
		SetDrawBright(255, 255, 255);
		DrawBox(130, 130, GAME_SCREEN_SIZE_X + 20, GAME_SCREEN_SIZE_Y + 20, RGB(0, 255, 255), true);
		DrawBox(150, 150, GAME_SCREEN_SIZE_X, GAME_SCREEN_SIZE_Y, RGB(255, 255, 255), true);
		SetFontSize(32);
		DrawString(300, 160, "キーガイド", RGB(255, 255, 0));
		SetFontSize(16);
		DrawString(170, 220, "SPACE…ブロック配置", RGB(0, 0, 0));
		DrawString(170, 240, "NUMPAD8…上移動", RGB(0, 0, 0));
		DrawString(170, 260, "NUMPAD2…下移動", RGB(0, 0, 0));
		DrawString(170, 280, "NUMPAD4…左移動", RGB(0, 0, 0));
		DrawString(170, 300, "NUMPAD6…右移動", RGB(0, 0, 0));
		DrawString(170, 340, "U…1つ戻る", RGB(0, 0, 0));
		DrawString(170, 360, "R…1つ進む", RGB(0, 0, 0));
		DrawString(170, 400, "左Ctrl…ブロックの変更", RGB(0, 0, 0));
		DrawString(400, 220, "A…右下まで埋める", RGB(0, 0, 0));
		DrawString(400, 240, "N…全て消去する", RGB(0, 0, 0));
		DrawString(400, 260, "Z…4マス選択状態", RGB(0, 0, 0));
		DrawString(400, 280, "X…4マス選択状態の解除", RGB(0, 0, 0));
		DrawString(400, 320, "F5…マップのロード", RGB(0, 0, 0));
		DrawString(400, 340, "F6…マップのセーブ", RGB(0, 0, 0));
		DrawString(400, 360, "F1…ゲームモードを始める", RGB(0, 0, 0));
		DrawString(400, 400, "Esc…ゲームを終了する", RGB(0, 0, 0));
		DrawString(400, 420, "M…キーガイドを閉じる", RGB(0, 0, 0));
	}
	else
	{
		SetFontSize(40);
		DrawString(75, 30, "M", RGB(255, 255, 255));
		SetFontSize(16);
		DrawString(115, 50, "キーガイドを開く", RGB(255, 255, 255));
	}*/
	DrawString(0, 0, "EditScene", 0x00ff0000);
	ScreenFlip();
	return true;
}

int EditScene::Init(void)
{
	if (!objList)
	{
		objList = std::make_shared<sharedList>();
	}
	objList->clear();
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	lpStageMng.SetUp(VECTOR2(GAME_SCREEN_SIZE_X, GAME_SCREEN_SIZE_Y), VECTOR2(CHIP_SIZE, CHIP_SIZE));
	auto obj = AddObjList()(objList, std::make_unique<EditCursor>(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y)));
	(*obj)->Init("image/map.png", VECTOR2(40, 40), VECTOR2(8, 6));
	return 0;
}