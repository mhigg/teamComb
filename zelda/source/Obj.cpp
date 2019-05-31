#include "DxLib.h"
#include "Obj.h"
#include "SceneMng.h"
#include "ImageMng.h"
#include "StageMng.h"
//#include "InfoCtrl.h"
#include "MapCtrl.h"


Obj::Obj()
{
	dir = DIR_DOWN; // (��ۂ̑���)
	visible = true;
}

Obj::Obj(VECTOR2 drawOffset) :drawOffset(drawOffset)
{
	// ���̺ݽ�׸����Ăяo���ꂽ�u�Ԑ^�����drawOffset�������������
	dir = DIR_DOWN; // (��ۂ̑���)
	visible = true;
}

// ������
bool Obj::Init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt)
{
	lpImageMng.GetID(fileName, divSize, divCnt);
	imageName = fileName;
	this->divSize = divSize;
	this->divCnt = divCnt;
	return true;
}

bool Obj::Init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 pos)
{
	Init(fileName, divSize, divCnt);
	SetPos(pos);
	return true;
}

Obj::~Obj()
{

}

void Obj::UpDate(const GameCtrl &controller, weakListObj objList)
{
	SetMove(controller, objList);
}

void Obj::Draw(void)
{
//	scrollOffset = lpInfoCtrl.GetAddScroll(plNum);

	if (imageName.length() == 0)
	{
		return;
	}
	unsigned int id = 0;
	if (animTable.find(animName) != animTable.end())
	{
		int count = (animCnt / animTable[animName][ANIM_TBL_INV]);
		if (animTable[animName][ANIM_TBL_LOOP]
			|| count < animTable[animName][ANIM_TBL_FRAME])
		{
			// ���l�𒴂���O�̏���
			count %= animTable[animName][ANIM_TBL_FRAME];
		}
		else
		{
			// ���l�𒴂�����̏���
			count = animTable[animName][ANIM_TBL_FRAME] - 1;
			animEndFlag = true;
			// visible = false;
		}

		id = (animTable[animName][ANIM_TBL_START_ID]) + static_cast<int>(dir) + count * divCnt.x;
	}
	animCnt++;

	if (id < IMAGE_ID(imageName).size())
	{
		if (visible)
		{
			DrawGraph(
				drawOffset.x + pos.x - scrollOffset.x - actOff.x,
				drawOffset.y + pos.y - scrollOffset.y - actOff.y,
				IMAGE_ID(imageName)[id],
				true
			);
		}
	}
	SetFontSize(18);
	
//	DrawFormatString(pos.x - scrollOffset.x +drawOffset.x , pos.y - scrollOffset.y +drawOffset.y,0x00ffffff, "scrX:%d\nscrY:%d", pos.x, pos.y);
//	DrawCircle(pos.x - scrollOffset.x +drawOffset.x, pos.y - scrollOffset.y +drawOffset.y, hitRad.x, 0x00ffffff, false);
}
void Obj::Draw(unsigned int id)
{
	if (id < IMAGE_ID(imageName).size())
	{
		if (visible)
		{
			DrawGraph(
				drawOffset.x + pos.x - scrollOffset.x - actOff.x,
				drawOffset.y + pos.y - scrollOffset.y - actOff.y,
				IMAGE_ID(imageName)[id],
				true
			);
		}
	}
}

const VECTOR2 & Obj::GetPos(void)
{
	return pos;
}

void Obj::SetPos(VECTOR2 pos)
{
	Obj::pos = pos;
}

void Obj::InitScroll(int plNum)
{
	VECTOR2 scrollStart = lpStageMng.GetScrollValue(VALUE_UPPER_L, lpMapCtrl.GetMode());
	VECTOR2 scrollEnd = lpStageMng.GetScrollValue(VALUE_LOWER_R, lpMapCtrl.GetMode());

	scrollOffset = { 0,0 };

	if (pos.x >= scrollStart.x)
	{
		scrollOffset.x = pos.x - scrollStart.x;
		if (pos.x >= scrollEnd.x)
		{
			scrollOffset.x = scrollEnd.x;
		}
	}
	if (pos.y >= scrollStart.y)
	{
		scrollOffset.y = pos.y - scrollStart.y;
		if (pos.y >= scrollEnd.y)
		{
			scrollOffset.y = scrollEnd.y;
		}
	}

	lpMapCtrl.AddScroll(scrollOffset, plNum);
}

bool Obj::AddAnim(std::string animName, int id_x, int id_y, int frame, int inv, bool loop)
{
	animTable[animName][ANIM_TBL_START_ID] = id_y * divCnt.x + id_x;
	animTable[animName][ANIM_TBL_FRAME] = frame;
	animTable[animName][ANIM_TBL_INV] = inv;
	animTable[animName][ANIM_TBL_LOOP] = loop;
	return true;
}

bool Obj::SetAnim(std::string animName)
{
	// �d����
	if (Obj::animName == animName)
	{
		return true;
	}
	// �ް������݂��Ȃ��ꍇ
	if (animTable.find(animName) == animTable.end())
	{
		return false;
	}
	Obj::animName = animName;
	Obj::animCnt = 0;	// ��Ұ��ݕύX�ɂ��ϐ��̸ر
	animEndFlag = false;
	return true;
}

std::string Obj::GetAnim(void)
{
	return animName;
}

