#include "DxLib.h"
#include "Obj.h"
#include "SceneMng.h"
#include "ImageMng.h"

Obj::Obj()
{
	dir = DIR_DOWN; // (ｾﾞﾛの代わり)
	visible = true;
}

Obj::Obj(VECTOR2 drawOffset) :drawOffset(drawOffset)
{
	// このｺﾝｽﾄﾗｸﾀが呼び出された瞬間真っ先にdrawOffsetが初期化される

	dir = DIR_DOWN; // (ｾﾞﾛの代わり)
	visible = true;
}

// 初期化
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
			// 一定値を超える前の処理
			count %= animTable[animName][ANIM_TBL_FRAME];
		}
		else
		{
			// 一定値を超えた後の処理
			count = animTable[animName][ANIM_TBL_FRAME] - 1;
			animEndFlag = true;
			visible = false;
		}

		id = (animTable[animName][ANIM_TBL_START_ID]) + (int)dir + count * divCnt.x;
	}
	animCnt++;
	if (id < IMAGE_ID(imageName).size())
	{
		if (visible)
		{
			DrawGraph(
				drawOffset.x + pos.x,
				drawOffset.y + pos.y,
				IMAGE_ID(imageName)[id],
				true
			);
		}
	}
	SetFontSize(18);
	DrawFormatString(0, 0, 0x00ffffff, "posX:%d\nposY:%d", pos.x, pos.y);
}

void Obj::Draw(unsigned int id)
{
	if (id < IMAGE_ID(imageName).size())
	{
		if (visible)
		{
			DrawGraph(
				drawOffset.x + pos.x,
				drawOffset.y + pos.y,
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
	// 重複時
	if (Obj::animName == animName)
	{
		return true;
	}
	// ﾃﾞｰﾀが存在しない場合
	if (animTable.find(animName) == animTable.end())
	{
		return false;
	}
	Obj::animName = animName;
	Obj::animCnt = 0;	// ｱﾆﾒｰｼｮﾝ変更によるｺﾏ数のｸﾘｱ
	animEndFlag = false;
	return true;
}

std::string Obj::GetAnim(void)
{
	return animName;
}

