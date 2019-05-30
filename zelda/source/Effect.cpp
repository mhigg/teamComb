#include "Effect.h"
#include "EffekseerForDXLib.h"
#include "EffectMng.h"


Effect::Effect()
{
}

Effect::Effect(VECTOR2 setUpPos, int lastingTime, VECTOR2 scrollOffset, VECTOR2 drawOffset) :Obj(drawOffset)
{
	SetPos(setUpPos);
	this->lastingTime = lastingTime;
	efkImg = lpEffectMng.GetID("image/aura_RED2.efk", 12.0f)[0];
}


Effect::~Effect()
{
}

bool Effect::CheckDeath(void)
{
	return (lastingTime <= 0);
}

bool Effect::CheckObjType(OBJ_TYPE type)
{
	return (type == OBJ_EFFECT);
}

void Effect::Draw(void)
{
	DrawEffekseer2D();
}

void Effect::SetMove(const GameCtrl & controller, weakListObj objList)
{
//	int playingEffectHandle = -1;

	//if (time % 60 == 0)
	//{
		// エフェクトを再生する。
		int playingEffectHandle = PlayEffekseer2DEffect(efkImg);
	//}

	SetPosPlayingEffekseer2DEffect(playingEffectHandle, pos.x - scrollOffset.x, pos.y - scrollOffset.y, 0);

	UpdateEffekseer2D();

	lastingTime--;
}
