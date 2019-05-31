#include "DxLib.h"
#include "TitleScene.h"
#include "ImageMng.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "GameCtrl.h"
#include "SoundMng.h"


TitleScene::TitleScene()
{
	TitleScene::Init();
}

TitleScene::~TitleScene()
{

}

uniqueBase TitleScene::UpDate(uniqueBase own, const GameCtrl & controller)
{
	auto &inputState = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputStateOld = controller.GetInputState(KEY_TYPE_OLD);
	auto cnt = controller.GetCtrl(KEY_TYPE_NOW);
	auto cntOld = controller.GetCtrl(KEY_TYPE_OLD);
	if ((cnt[KEY_INPUT_F1]) & (!cntOld[KEY_INPUT_F1]))
	{
		PlaySoundMem(lpSoundMng.GetID("sound/Œˆ’è‰¹.wav"), DX_PLAYTYPE_NORMAL);
		StopSoundMem(lpSoundMng.GetID("sound/TitleBGM.mp3"));
		return std::make_unique<MenuScene>();
	}
	if (inputState[0][static_cast<int>(INPUT_ID::START)] & !inputStateOld[0][static_cast<int>(INPUT_ID::START)])
	{
		PlaySoundMem(lpSoundMng.GetID("sound/Œˆ’è‰¹.wav"), DX_PLAYTYPE_NORMAL);
		StopSoundMem(lpSoundMng.GetID("sound/TitleBGM.mp3"));
		return std::make_unique<MenuScene>();
	}
	TitleDraw();
	TitleScene:: cnt++;
	return std::move(own);
}

void TitleScene::TitleDraw(void)
{
	ClsDrawScreen();
	DrawGraph(0, 0, IMAGE_ID("image/title.png")[0], true);
	DrawGraph(1200, 700, IMAGE_ID("image/ƒRƒA‚Ì‚Ý.png")[0], true);
	if (cnt / 30 % 3)
	{
		DrawGraph(400, 750, IMAGE_ID("image/psk.png")[0], true);
	}
	ScreenFlip();
}

int TitleScene::Init(void)
{
	cnt = 0;
	PlaySoundMem(lpSoundMng.GetID("sound/TitleBGM.mp3"), DX_PLAYTYPE_LOOP);
	return 0;
}
