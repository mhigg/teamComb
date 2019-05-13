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
#ifdef _DEBUG	// √ﬁ ﬁØ∏ﬁéûÇÃÇ›éÊìæ
	auto ctrl = controller.GetCtrl(KEY_TYPE_NOW);
	auto ctrlOld = controller.GetCtrl(KEY_TYPE_OLD);
	auto &inputState = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputStateOld = controller.GetInputState(KEY_TYPE_OLD);
#else
#endif

	auto pad = controller.GetInputState(KEY_TYPE_NOW);
	auto padOld = controller.GetInputState(KEY_TYPE_OLD);

	if (ctrl[KEY_INPUT_F1] & ~ctrlOld[KEY_INPUT_F1])
	{
		return std::make_unique<EditScene>();
	}
	if (inputState[0][static_cast<int>(INPUT_ID::START)] & !inputStateOld[0][static_cast<int>(INPUT_ID::START)])
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
	lpMapCtrl.MapLoad(objList, false);
	return 0;
}

void GameScene::Draw(void)
{
// Å¶ ï`âÊÇÃø∞ƒèàóù
	(*objList).sort([](sharedObj& obj1, sharedObj& obj2) { return (*obj1).GetPos().y < (*obj2).GetPos().y; });

	ClsDrawScreen();

	lpMapCtrl.Draw(false);

	for (auto& obj : (*objList))
	{
		obj->Draw();
	}

	DrawString(0, 800, "GameScene", 0x00ff0000);

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