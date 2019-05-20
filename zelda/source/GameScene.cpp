#include <DxLib.h>
#include <memory>
#include "GameScene.h"
#include "EditScene.h"
#include "SceneMng.h"
#include "StageMng.h"
#include "ScoreBoard.h"
#include "GameCtrl.h"
#include "VECTOR2.h"
#include "ImageMng.h"


GameScene::GameScene()
{
	Init();
}


GameScene::~GameScene()
{
}

uniqueBase GameScene::UpDate(uniqueBase own, const GameCtrl & controller)
{
#ifdef _DEBUG	// ﾃﾞﾊﾞｯｸﾞ時のみ取得
	auto ctrl = controller.GetCtrl(KEY_TYPE_NOW);
	auto ctrlOld = controller.GetCtrl(KEY_TYPE_OLD);
	auto &inputState = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputStateOld = controller.GetInputState(KEY_TYPE_OLD);
#else
#endif

	auto pad = controller.GetInputState(KEY_TYPE_NOW);
	auto padOld = controller.GetInputState(KEY_TYPE_OLD);

#ifdef _DEBUG	// ﾃﾞﾊﾞｯｸﾞ時のみ実行
	if (ctrl[KEY_INPUT_F1] & ~ctrlOld[KEY_INPUT_F1])
	{
		lpScoreBoard.DataInit();
		return std::make_unique<EditScene>();
	}
	if (inputState[0][static_cast<int>(INPUT_ID::START)] & !inputStateOld[0][static_cast<int>(INPUT_ID::START)])
	{
		lpScoreBoard.DataInit();
		return std::make_unique<EditScene>();
	}
#else
#endif

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
// ※ 描画のｿｰﾄ処理
	(*objList).sort([](sharedObj& obj1, sharedObj& obj2) { return (*obj1).GetPos().y < (*obj2).GetPos().y; });

	ClsDrawScreen();
	
	lpMapCtrl.Draw(false);

// objListから画面外のｵﾌﾞｼﾞｪｸﾄを除外する
	//auto tmpList = (*objList);
	//tmpList.remove_if([&](sharedObj &tmp) {
	//	if (tmp->GetPos().x < plPos.x - CHIP_SIZE * 21
	//	 || tmp->GetPos().x > plPos.x + CHIP_SIZE * 21)
	//	{
	//		return true;
	//	}
	//	return false;
	//});

	for (auto& obj : (*objList))
	{
		obj->Draw();
	}


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

	DrawBox(640, 300, 960, 640, 0x00ffffff, true);

	// ｽｺｱﾎﾞｰﾄﾞ表示
	lpScoreBoard.Draw();

	for (int i = 0; i < 10; i++)
	{
		DrawGraph(640 + (i * 20),0, lpImageMng.GetID("image/number.png", { 40,30 }, { 10,1 })[i], true);
	}

	DrawString(0, 800, "GameScene", 0x00ff0000);

	DrawFormatString(1400, 930, 0xff, "frame / 60:%d", lpSceneMng.GetFram() / 60);

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