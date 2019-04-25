#pragma once
#include "VECTOR2.h"
#include "ClassObj.h"
#include "GameCtrl.h"

enum DIR {
	DIR_DOWN,	// ��
	DIR_LEFT,	// ��
	DIR_RIGHT,	// �E
	DIR_UP,		// ��
	DIR_MAX
};

class Obj
{
public:
	Obj();
	~Obj();

	void Update(const GameCtrl &controller, weekListObj objList);		// SetMove���Ăяo��

private:
	virtual void SetMove(const GameCtrl &controller, weekListObj objList) = 0;

protected:
	void SetPos(VECTOR2 pos);			// ���W�Z�b�g
	VECTOR2 pos;						// ���W
};

