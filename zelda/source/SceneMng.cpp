#include <DxLib.h>
#include <memory>
#include "SceneMng.h"
#include "GameScene.h"
#include "GameCtrl.h"
#include "TitleScene.h"
#include "EditScene.h"
#include "MenuScene.h"

constexpr int SCREEN_SIZE_X = 1200;
constexpr int SCREEN_SIZE_Y = 880;

SceneMng::SceneMng()
{
	Init();
}

void SceneMng::Run(void)
{
	activeScene = std::make_unique<TitleScene>();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		gameCtrl->UpDate();
		activeScene = activeScene->UpDate(std::move(activeScene), (*gameCtrl));
	}
}

VECTOR2 SceneMng::GetDrawOffset(void)
{
	return drawOffset;
}

void SceneMng::SetDrawOffset(VECTOR2 drawOffset)
{
	this->drawOffset = drawOffset;
}

SceneMng::~SceneMng()
{
}

bool SceneMng::Init(void)
{
	// ｼｽﾃﾑ処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);				// true:window　false:ﾌﾙｽｸﾘｰﾝ
	SetWindowText("ZELDA");
	if (DxLib_Init() == -1) return false;
	SetDrawScreen(DX_SCREEN_BACK);

	gameCtrl = std::make_unique<GameCtrl>();	//ﾕﾆｰｸﾎﾟｲﾝﾀ

	return true;
}
