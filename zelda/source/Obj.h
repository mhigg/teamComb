#pragma once
#include "VECTOR2.h"
#include "ClassObj.h"
#include "GameCtrl.h"

enum DIR {
	DIR_DOWN,	// 下
	DIR_LEFT,	// 左
	DIR_RIGHT,	// 右
	DIR_UP,		// 上
	DIR_MAX
};

class Obj
{
public:
	Obj();
	~Obj();

	void Update(const GameCtrl &controller, weekListObj objList);		// SetMoveを呼び出す

private:
	virtual void SetMove(const GameCtrl &controller, weekListObj objList) = 0;

protected:
	void SetPos(VECTOR2 pos);			// 座標セット
	VECTOR2 pos;						// 座標
};

