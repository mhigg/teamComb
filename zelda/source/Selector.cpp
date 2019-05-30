#include <DxLib.h>
#include "Selector.h"
#include "ImageMng.h"
#include "GameCtrl.h"
#include "InfoCtrl.h"

Selector::Selector()
{
}

Selector::Selector(PL_NUMBER plNum, VECTOR2 setUpPos, VECTOR2 drawOffset) :Obj(drawOffset)
{
	this->plNum = plNum;

	standImgTbl = {
		"image/stand.png",
		"image/stand2.png",
		"image/stand3.png",
		"image/stand3.png"
	};

	pNumImgTbl = {
		"image/p1.png",
		"image/p2.png",
		"image/p3.png",
		"image/p4.png"
	};

	Image = pNumImgTbl[plNum];

	Init(standImgTbl[plNum], VECTOR2(240, 360), VECTOR2(1, 1), setUpPos);

	selectChara = static_cast<CHARA_TYPE>(plNum);
}


Selector::~Selector()
{
}

bool Selector::CheckObjType(OBJ_TYPE type)
{
	return (type == OBJ_SELECTOR);
}

void Selector::Draw(void)
{
	VECTOR2 drawPos = lpMapCtrl.GetScreenPos(plNum);

	DrawGraph(drawPos.x + 20, drawPos.y + 20, IMAGE_ID(Image)[0], true);
	DrawGraph(pos.x, pos.y, IMAGE_ID(standImgTbl[selectChara])[0], true);
}

void Selector::SetMove(const GameCtrl & controller, weakListObj objList)
{
	auto &inputState = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputStateOld = controller.GetInputState(KEY_TYPE_OLD);

	// �I��
	if (inputState[plNum][XINPUT_RIGHT] & !inputStateOld[plNum][XINPUT_RIGHT])
	{
		if (selectChara < CHARA_MAX - 1)
		{
			selectChara = static_cast<CHARA_TYPE>(static_cast<int>(selectChara) + 1);
		}
	}
	if (inputState[plNum][XINPUT_LEFT] & !inputStateOld[plNum][XINPUT_LEFT])
	{
		if (selectChara > 0)
		{
			selectChara = static_cast<CHARA_TYPE>(static_cast<int>(selectChara) - 1);
		}
	}
	lpInfoCtrl.SetSelectChara(selectChara, static_cast<int>(plNum));
}
