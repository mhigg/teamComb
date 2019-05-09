#include "DxLib.h"
#include "SceneMng.h"
#include "EditScene.h"
#include "Obj.h"
#include "EditCursor.h"
#include "GameCtrl.h"
#include "MapCtrl.h"
#include "StageMng.h"

// ���وړ��̑��x�ω��p
#define EDIT_KEY_GET_DEF_RNG (60)
#define MIN_KEY_RNG	(3)

EditCursor::EditCursor()
{
	id = MAP_ID::NONE;
	inputFlam = EDIT_KEY_GET_DEF_RNG;
	keyGetRng = EDIT_KEY_GET_DEF_RNG;

	dirTable = { KEY_INPUT_NUMPAD2, KEY_INPUT_NUMPAD4, KEY_INPUT_NUMPAD6, KEY_INPUT_NUMPAD8 };
	speedTable = { MOVE_SPEED, -MOVE_SPEED, MOVE_SPEED, -MOVE_SPEED };
}

EditCursor::EditCursor(VECTOR2 drawOffset) :Obj(drawOffset)
{
	id = MAP_ID::NONE;
	inputFlam = EDIT_KEY_GET_DEF_RNG;
	keyGetRng = EDIT_KEY_GET_DEF_RNG;

	dirTable = { KEY_INPUT_NUMPAD2, KEY_INPUT_NUMPAD4, KEY_INPUT_NUMPAD6, KEY_INPUT_NUMPAD8 };
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
	DIR_TBL_PTR tmpTable = { &tmpPos.y,0, &tmpPos.x,0, &tmpPos.x,0, &tmpPos.y,0 };

	auto Move = [&](DIR dir)
	{
		if (ctrl[dirTable[dir]])
		{
			(*tmpTable[dir][TBL_MAIN]) += speedTable[dir];
		}
	};

	// �ړ�����
	for (int j = 0; j < DIR_MAX; j++)
	{
		Move((DIR)j);
	}

	if ((tmpPos.x < lpStageMng.GetStageSize().x) & (tmpPos.x >= 0)
		&  (tmpPos.y < lpStageMng.GetStageSize().y) & (tmpPos.y >= 0))
	{
		if (tmpPos != pos)
		{
			inputFlam++;
			if (inputFlam >= keyGetRng)
			{
				// 1�񉟂���
				// �����ɗ��邽�тɾ�۸ر�Ɗ�ꐔ�̔���
				pos = tmpPos;
				inputFlam = 0;
				keyGetRng /= 2;
				if (keyGetRng < MIN_KEY_RNG)
				{
					keyGetRng = MIN_KEY_RNG;
				}
			}
		}
		else
		{
			// ���𗣂��Ă���Ƃ�
			inputFlam = EDIT_KEY_GET_DEF_RNG;
			keyGetRng = EDIT_KEY_GET_DEF_RNG;
		}
	}

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
		id = MAP_ID::WALL1;
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

bool EditCursor::CheckObjType(OBJ_TYPE type)
{
	return (type == OBJ_EDIT_CURSOR);
}

// ��Ŋy�����邽�߂ɐ�ɏ�����J����