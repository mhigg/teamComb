#include <DxLib.h>
#include "MenuScene.h"
#include "GameScene.h"
#include "EditScene.h"
#include "ImageMng.h"
#include "SelectScene.h"
#include "MapCtrl.h"
#include "SoundMng.h"

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
	
	// �I�����Ă���Ӱ�މ摜�����o��
	for (int i = 0; i < MODE_MAX; i++)
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

	// �����삪�\�ɂȂ��Ă���̏���
	if (pushFlag)
	{
		// �I��
		if (inputState[0][XINPUT_DOWN] & !inputStateOld[0][XINPUT_DOWN])
		{
			if (nowMode < MODE_MAX - 1)
			{
				selectPoint[nowMode] = 0;
				selectPoint[nowMode + 1] = PUSH_SIZE;
				nowMode = static_cast<MODE>(static_cast<int>(nowMode) + 1);
			}
		}
		else if (inputState[0][XINPUT_UP] & !inputStateOld[0][XINPUT_UP])
		{
			if (nowMode > 0)
			{
				selectPoint[nowMode] = 0;
				selectPoint[nowMode - 1] = PUSH_SIZE;
				nowMode = static_cast<MODE>(static_cast<int>(nowMode) - 1);
			}
		}

		// ��݈ڍs
		if (!descriptionFlag)
		{
			if (nowMode < MODE_HOWTO)
			{
				if ((cnt[KEY_INPUT_F1]) & (!cntOld[KEY_INPUT_F1]))
				{
					lpMapCtrl.SetMode(nowMode);
					PlaySoundMem(lpSoundMng.GetID("sound/���艹.wav"), DX_PLAYTYPE_NORMAL);
					return std::make_unique<SelectScene>();
				}
				if (inputState[0][XINPUT_START] & !inputStateOld[0][XINPUT_START])
				{
					lpMapCtrl.SetMode(nowMode);
					PlaySoundMem(lpSoundMng.GetID("sound/���艹.wav"), DX_PLAYTYPE_NORMAL);
					return std::make_unique<SelectScene>();
				}
			}
			else if (nowMode == MODE_HOWTO)
			{
				if ((cnt[KEY_INPUT_F1]) & (!cntOld[KEY_INPUT_F1]))
				{
					PlaySoundMem(lpSoundMng.GetID("sound/���艹.wav"), DX_PLAYTYPE_NORMAL);
					descriptionFlag = true;
				}
				if (inputState[0][XINPUT_START] & !inputStateOld[0][XINPUT_START])
				{
					PlaySoundMem(lpSoundMng.GetID("sound/���艹.wav"), DX_PLAYTYPE_NORMAL);
					descriptionFlag = true;
				}
			}
		}
		// BACK���ƭ���ʂ֖߂�
		else
		{
			if (inputState[0][XINPUT_PAUSE] & !inputStateOld[0][XINPUT_PAUSE])
			{
				nowMode = MODE_HOWTO;
				selectPoint[nowMode] = 20;
				descriptionFlag = false;
				PlaySoundMem(lpSoundMng.GetID("sound/�L�����Z��.wav"), DX_PLAYTYPE_NORMAL);
			}
		}
	}
	MenuDraw();
	return std::move(own);
}

void MenuScene::MenuDraw(void)
{
	ClsDrawScreen();
	// �ƭ��摜�\��
	if(!descriptionFlag)
	{
		DrawGraph(0, 0, IMAGE_ID("image/menu1.png")[0], true);
		for (int i = 0; i < MODE_MAX; i++)
		{
			DrawGraph(movePos[i].x - size.x + selectPoint[i], movePos[i].y + (i * size.y), lpImageMng.GetID("image/menu2.png", { 460,180 }, { 1,3 })[i], true);
		}
		VECTOR2 tmp1(0, 0);
		VECTOR2 tmp2(0, GAME_SCREEN_SIZE_Y);
		for (; tmp1.x <= GAME_SCREEN_SIZE_X; tmp1.x += 800)
		{
			tmp2.x = tmp1.x;
			DrawLine(tmp1, tmp2, 0x00ffffff, true);
		}
		DrawGraph(0,GAME_SCREEN_SIZE_Y - 60, IMAGE_ID("image/idou.png")[0], true);
		DrawGraph(180, GAME_SCREEN_SIZE_Y - 60, IMAGE_ID("image/kettei.png")[0], true);
	}
	// ��������I���Ő����摜�\��
	else
	{
		SetDrawBright(128, 128, 128);
		DrawGraph(0, 0, IMAGE_ID("image/menu1.png")[0], true);
		SetDrawBright(255, 255, 255);
		DrawGraph(0, 120, IMAGE_ID("image/setumei.png")[0], true);
		DrawGraph(0,30 , IMAGE_ID("image/sousa.png")[0], true);
		DrawGraph(0, GAME_SCREEN_SIZE_Y - 60, IMAGE_ID("image/modoru.png")[0], true);
	}
	DrawString(0, 0, "MenuScene", 0x00ff0000);
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
	size = { BOX_SIZE_X,BOX_SIZE_Y };
	add = 0;
	nowMode = MODE_MALTI;
	descriptionFlag = false;
	pushFlag = false;
	return 0;
}