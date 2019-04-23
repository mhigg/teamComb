#include <DxLib.h>
#include <memory>
#include "SceneMng.h"
#include "GameScene.h"
#include "GameCtrl.h"

constexpr int SCREEN_SIZE_X = 1000;
constexpr int SCREEN_SIZE_Y = 840;

SceneMng::SceneMng()
{
	Init();
}

void SceneMng::Run(void)
{
	activeScene = std::make_unique<GameScene>();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		gameCtrl->UpDate();
		activeScene = activeScene->UpDate(std::move(activeScene), (*gameCtrl));
	}
}

SceneMng::~SceneMng()
{
}

bool SceneMng::Init(void)
{
	// ���я���
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);				// true:window�@false:�ٽ�ذ�
	SetWindowText("ZELDA");
	if (DxLib_Init() == -1) return false;
	SetDrawScreen(DX_SCREEN_BACK);

	gameCtrl = std::make_unique<GameCtrl>();	//�ư��߲��

	return true;
}