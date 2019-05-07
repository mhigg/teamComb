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
			// ۰��
			if (MessageBox(
				NULL,
				"�G�f�B�b�g���e�����[�h���܂����H",
				"�m�F�_�C�A���O",
				MB_OKCANCEL
			) == IDOK)
			{
				lpStageMng.MapLoad(objList, true);
			}
		}
		if (cnt[KEY_INPUT_F6])
		{
			// ����
			if (MessageBox(
				NULL,
				"�G�f�B�b�g���e���Z�[�u���܂����H",
				"�m�F�_�C�A���O",
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
		DrawString(300, 160, "�L�[�K�C�h", RGB(255, 255, 0));
		SetFontSize(16);
		DrawString(170, 220, "SPACE�c�u���b�N�z�u", RGB(0, 0, 0));
		DrawString(170, 240, "NUMPAD8�c��ړ�", RGB(0, 0, 0));
		DrawString(170, 260, "NUMPAD2�c���ړ�", RGB(0, 0, 0));
		DrawString(170, 280, "NUMPAD4�c���ړ�", RGB(0, 0, 0));
		DrawString(170, 300, "NUMPAD6�c�E�ړ�", RGB(0, 0, 0));
		DrawString(170, 340, "U�c1�߂�", RGB(0, 0, 0));
		DrawString(170, 360, "R�c1�i��", RGB(0, 0, 0));
		DrawString(170, 400, "��Ctrl�c�u���b�N�̕ύX", RGB(0, 0, 0));
		DrawString(400, 220, "A�c�E���܂Ŗ��߂�", RGB(0, 0, 0));
		DrawString(400, 240, "N�c�S�ď�������", RGB(0, 0, 0));
		DrawString(400, 260, "Z�c4�}�X�I�����", RGB(0, 0, 0));
		DrawString(400, 280, "X�c4�}�X�I����Ԃ̉���", RGB(0, 0, 0));
		DrawString(400, 320, "F5�c�}�b�v�̃��[�h", RGB(0, 0, 0));
		DrawString(400, 340, "F6�c�}�b�v�̃Z�[�u", RGB(0, 0, 0));
		DrawString(400, 360, "F1�c�Q�[�����[�h���n�߂�", RGB(0, 0, 0));
		DrawString(400, 400, "Esc�c�Q�[�����I������", RGB(0, 0, 0));
		DrawString(400, 420, "M�c�L�[�K�C�h�����", RGB(0, 0, 0));
	}
	else
	{
		SetFontSize(40);
		DrawString(75, 30, "M", RGB(255, 255, 255));
		SetFontSize(16);
		DrawString(115, 50, "�L�[�K�C�h���J��", RGB(255, 255, 255));
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