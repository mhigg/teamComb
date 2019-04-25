#include "Obj.h"



Obj::Obj()
{
}


Obj::~Obj()
{
}

void Obj::Update(const GameCtrl & controller, weekListObj objList)
{
	SetMove(controller, objList);
}

void Obj::SetPos(VECTOR2 pos)
{
	Obj::pos = pos;
}
