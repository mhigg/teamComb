#include <DxLib.h>
#include <memory>
#include "GameScene.h"
#include "EditScene.h"
#include "SceneMng.h"
#include "StageMng.h"
#include "GameCtrl.h"
#include "VECTOR2.h"


GameScene::GameScene()
{
	Init();
}


GameScene::~GameScene()
{
}

uniqueBase GameScene::UpDate(uniqueBase own, const GameCtrl & controller)
{
#ifdef _DEBUG	// ÃÞÊÞ¯¸ÞŽž‚Ì‚ÝŽæ“¾
	auto ctrl = controller.GetCtrl(KEY_TYPE_NOW);
	auto ctrlOld = controller.GetCtrl(KEY_TYPE_OLD);
#else
#endif

	auto pad = controller.GetInputState(KEY_TYPE_NOW);
	auto padOld = controller.GetInputState(KEY_TYPE_OLD);

	if (ctrl[KEY_INPUT_F1] & ~ctrlOld[KEY_INPUT_F1])
	{
		return std::make_unique<EditScene>();
	}

	for (auto& obj : (*objList))
	{
		obj->UpDate(controller, objList);
	}

	Draw();

	return move(own);
}

int GameScene::Init(void)
{
	if (!objList)
	{
		objList = std::make_shared<sharedList>();
	}
	objList->clear();

	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	lpMapCtrl.SetUp(VECTOR2(CHIP_SIZE, CHIP_SIZE), lpSceneMng.GetDrawOffset());
	lpMapCtrl.SetMapData(VECTOR2(0, 0), MAP_ID::PLAYER);
	lpStageMng.MapLoad(objList, false);
	return 0;
}

void GameScene::Draw(void)
{
	ClsDrawScreen();

	lpMapCtrl.Draw(true);

	VECTOR2 tmp1(0, 0);
	VECTOR2 tmp2(0, GAME_SCREEN_SIZE_Y);
	VECTOR2 offset(VECTOR2(0,0));

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

	for (auto& obj : (*objList))
	{
		obj->Draw();
	}

	DrawString(0, 0, "GameScene", 0x00ff0000);

	ScreenFlip();
}

int	DrawLine(VECTOR2 vec1, VECTOR2 vec2, unsigned int Color, int Thickness)
{
	DxLib::DrawLine(
		vec1.x,
		vec1.y,
		vec2.x,
		vec2.y,
		Color,
		Thickness
	);
	return 0;
}