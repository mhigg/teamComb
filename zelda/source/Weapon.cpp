#include "Weapon.h"



Weapon::Weapon()
{
}

Weapon::Weapon(WEP_TYPE weapon, DIR dir, VECTOR2 setUpPos, VECTOR2 drawOffset) :Obj(drawOffset)
{
	AtkImgTbl = { "image/ŽaŒ‚_DOWN.png",
				  "image/ŽaŒ‚_Left.png",
				  "image/ŽaŒ‚_Right.png",
				  "image/ŽaŒ‚_UP.png"
				};

	this->weapon = weapon;
	Init(AtkImgTbl[dir], VECTOR2(140, 130), VECTOR2(4, 10), setUpPos);
	initAnim();
	SetAnim("ŽaŒ‚");
}


Weapon::~Weapon()
{
}

bool Weapon::initAnim(void)
{
	AddAnim("ŽaŒ‚", 0, 0, 40, 1, false);
	return true;
}

bool Weapon::CheckDeath(void)
{
	return animEndFlag;
}

bool Weapon::CheckObjType(OBJ_TYPE type)
{
	return (type == OBJ_TYPE::OBJ_WEAPON);
}

void Weapon::SetMove(const GameCtrl & controller, weakListObj objList)
{
}
