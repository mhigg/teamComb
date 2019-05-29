#include "Weapon.h"



Weapon::Weapon()
{
}

Weapon::Weapon(WEP_TYPE weapon, DIR dir, VECTOR2 setUpPos, VECTOR2 scrollOffset, VECTOR2 drawOffset) :Obj(drawOffset)
{
	AtkImgTbl = { "image/�a��_DOWN.png",	"image/�a��_DOWN.png",
				  "image/�a��_Left.png",	"image/�a��_Left.png",
				  "image/�a��_Right.png",	"image/�a��_Right.png",
				  "image/�a��_UP.png",		"image/�a��_UP.png"
	};

	this->scrollOffset = scrollOffset;
	this->weapon = weapon;
	Init(AtkImgTbl[dir][weapon], VECTOR2(140, 130), VECTOR2(4, 10), setUpPos);
	initAnim();
	SetAnim("�a��");
}


Weapon::~Weapon()
{
}

int Weapon::WeaponInit(WEP_TYPE weapon)
{
	return 0;
}

bool Weapon::initAnim(void)
{
	AddAnim("�a��", 0, 0, 40, 1, false);
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
