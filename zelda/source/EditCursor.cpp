#include "DxLib.h"
#include "SceneMng.h"
#include "EditScene.h"
#include "Obj.h"
#include "EditCursor.h"
#include "GameCtrl.h"
#include "MapCtrl.h"
#include "StageMng.h"

// ���وړ��̑��x�ω��p
constexpr int EDIT_KEY_GET_DEF_RNG	= 60;
constexpr int MIN_KEY_RNG			= 3;

EditCursor::EditCursor()
{
	id = MAP_ID::NONE;
	inputFlam = EDIT_KEY_GET_DEF_RNG;
	keyGetRng = EDIT_KEY_GET_DEF_RNG;
	scrollOffset = { 0,0 };

	dirTable = { KEY_INPUT_NUMPAD2, KEY_INPUT_NUMPAD4, KEY_INPUT_NUMPAD6, KEY_INPUT_NUMPAD8 };
	scrTable = { KEY_INPUT_DOWN, KEY_INPUT_LEFT, KEY_INPUT_RIGHT, KEY_INPUT_UP };
	speedTable = { MOVE_SPEED, -MOVE_SPEED, MOVE_SPEED, -MOVE_SPEED };
}

EditCursor::EditCursor(VECTOR2 drawOffset) :Obj(drawOffset)
{
	id = MAP_ID::NONE;
	inputFlam = EDIT_KEY_GET_DEF_RNG;
	keyGetRng = EDIT_KEY_GET_DEF_RNG;
	scrollOffset = { 0,0 };

	dirTable = { KEY_INPUT_NUMPAD2, KEY_INPUT_NUMPAD4, KEY_INPUT_NUMPAD6, KEY_INPUT_NUMPAD8 };
	scrTable = { KEY_INPUT_DOWN, KEY_INPUT_LEFT, KEY_INPUT_RIGHT, KEY_INPUT_UP };
	speedTable = { MOVE_SPEED, -MOVE_SPEED, MOVE_SPEED, -MOVE_SPEED };
}

EditCursor::~EditCursor()
{
}

void EditCursor::Draw(void)
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	Obj::Draw(static_cast<int>(id));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs((int)(animCnt % 512) - 256));
	Obj::Draw(static_cast<int>(MAP_ID::NONE));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	animCnt += 16;
}

void EditCursor::SetMove(const GameCtrl &controller, weakListObj objList)
{
	auto ctrl = controller.GetCtrl(KEY_TYPE_NOW);
	auto ctrlOld = controller.GetCtrl(KEY_TYPE_OLD);

	VECTOR2 tmpPos(pos);
	VECTOR2 tmpScr(scrollOffset);
	DIR_TBL_PTR tmpTable = { &tmpPos.y,0, &tmpPos.x,0, &tmpPos.x,0, &tmpPos.y,0 };
	DIR_TBL_PTR tmpScrTable = { &tmpScr.y,0, &tmpScr.x,0, &tmpScr.x,0, &tmpScr.y,0 };

	auto TmpMove = [this, ctrl, tmpTable, tmpScrTable](DIR dir)
	{
		if (ctrl[dirTable[dir]])
		{
			(*tmpTable[dir][TBL_MAIN]) += speedTable[dir];
		}
		if (ctrl[scrTable[dir]])
		{
			(*tmpScrTable[dir][TBL_MAIN]) += speedTable[dir];
		}
	};

	// �ړ�����
	for (int j = 0; j < DIR_MAX; j++)
	{
		TmpMove((DIR)j);
	}

	if (!MoveDec(tmpPos, pos) && !MoveDec(tmpScr, scrollOffset))
	{
		// ���𗣂��Ă���Ƃ�
		inputFlam = EDIT_KEY_GET_DEF_RNG;
		keyGetRng = EDIT_KEY_GET_DEF_RNG;
	}

	lpMapCtrl.AddScroll(scrollOffset);

	// LCONTROL������ID++ WALL_BLUE������Z����MAX�̌�NON�֖߂�
	if (ctrl[KEY_INPUT_LCONTROL] & ~(ctrlOld[KEY_INPUT_LCONTROL]))
	{
		id = static_cast<MAP_ID>(static_cast<int>(id) + 1 >= static_cast<int>(MAP_ID::MAX) ? static_cast<int>(MAP_ID::NONE) : static_cast<int>(id) + 1);
	}
	if (ctrl[KEY_INPUT_RCONTROL] & ~(ctrlOld[KEY_INPUT_RCONTROL]))
	{
		id = static_cast<MAP_ID>(id <= MAP_ID::NONE ? (static_cast<int>(MAP_ID::MAX) - 1) : (static_cast<int>(id) - 1));
	}
	if (ctrl[KEY_INPUT_I] & ~(ctrlOld[KEY_INPUT_I]))
	{
		id = MAP_ID::POTION_1;
	}
	if (ctrl[KEY_INPUT_M] & ~(ctrlOld[KEY_INPUT_M]))
	{
		id = MAP_ID::WALL13;
	}
	if (ctrl[KEY_INPUT_P] & ~(ctrlOld[KEY_INPUT_P]))
	{
		id = MAP_ID::PLAYER;
	}

	// SPACE������SetMapData�Ăяo��
	if (ctrl[KEY_INPUT_SPACE] & ~(ctrlOld[KEY_INPUT_SPACE]))
	{
		lpMapCtrl.SetMapData(pos, id);
	}
}

bool EditCursor::MoveDec(VECTOR2 temp, VECTOR2 & dec)
{
	if ((temp.x < lpStageMng.GetStageSize().x) & (temp.x >= 0)
	 &  (temp.y < lpStageMng.GetStageSize().y) & (temp.y >= 0))
	{
		if (temp != dec)
		{
			inputFlam++;
			if (inputFlam >= keyGetRng)
			{
				// 1�񉟂���
				// �����ɗ��邽�тɾ�۸ر�Ɗ�ꐔ�̔���
				dec = temp;
				inputFlam = 0;
				keyGetRng /= 2;
				if (keyGetRng < MIN_KEY_RNG)
				{
					keyGetRng = MIN_KEY_RNG;
				}

			}
			return true;
		}
	}

	return false;
}

bool EditCursor::CheckObjType(OBJ_TYPE type)
{
	return (type == OBJ_EDIT_CURSOR);
}

// ��Ŋy�����邽�߂ɐ�ɏ�����J����