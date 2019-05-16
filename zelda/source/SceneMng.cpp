#include <DxLib.h>
#include <memory>
#include "SceneMng.h"
#include "GameScene.h"
#include "GameCtrl.h"
#include "TitleScene.h"
#include "EditScene.h"
#include "MenuScene.h"

constexpr int SCREEN_SIZE_X = 1600;
constexpr int SCREEN_SIZE_Y = 960;

constexpr int PL_SCREEN_SIZE_X = 800;
constexpr int PL_SCREEN_SIZE_Y = 480;

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

VECTOR2 SceneMng::GetPlayScreen(void)
{
	return VECTOR2(PL_SCREEN_SIZE_X, PL_SCREEN_SIZE_Y);
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
	// ºΩ√—èàóù
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536êF”∞ƒﬁÇ…ê›íË
	ChangeWindowMode(true);				// true:windowÅ@false:ÃŸΩ∏ÿ∞›
	SetWindowText("ZELDA");
	if (DxLib_Init() == -1) return false;
	SetDrawScreen(DX_SCREEN_BACK);

	gameCtrl = std::make_unique<GameCtrl>();	//’∆∞∏Œﬂ≤›¿

	return true;
}
