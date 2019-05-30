#pragma once
#include "Obj.h"
#include "VECTOR2.h"

class Effect :
	public Obj
{
public:
	Effect();
	Effect(VECTOR2 setUpPos, int lastingTime, VECTOR2 scrollOffset, VECTOR2 drawOffset);
	~Effect();

	bool CheckDeath(void);
	bool CheckObjType(OBJ_TYPE type);
	void Draw(void);

private:
	void SetMove(const GameCtrl &controller, weakListObj objList);

	int efkImg;			// �̪���ް���:efķ��
	int lastingTime;	// �̪�Ă̎�������
};

