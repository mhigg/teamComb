#include <DxLib.h>
#include <memory>
#include "SceneMng.h"
#include "EffectMng.h"
#include "TitleScene.h"
#include "GameCtrl.h"


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
		framCnt++;
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

VECTOR2 SceneMng::GetPlayScreen(bool singleFlag)
{
	return (singleFlag ? VECTOR2(SCREEN_SIZE_X, SCREEN_SIZE_Y) : VECTOR2(PL_SCREEN_SIZE_X, PL_SCREEN_SIZE_Y));
}

int SceneMng::GetFram(void)
{
	return framCnt;
}

SceneMng::~SceneMng()
{
}

bool SceneMng::Init(void)
{
	// ｼｽﾃﾑ処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536色ﾓｰﾄﾞに設定
	SetWindowSize(1500, 800);
	ChangeWindowMode(true);				// true:window　false:ﾌﾙｽｸﾘｰﾝ
	SetWindowText("TREASURE HUNTER");
	if (DxLib_Init() == -1) return false;

	lpEffectMng.SetUp();

	SetDrawScreen(DX_SCREEN_BACK);

	gameCtrl = std::make_unique<GameCtrl>();

	return true;
}
