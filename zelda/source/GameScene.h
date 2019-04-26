#pragma once
#include "BaseScene.h"
#include "VECTOR2.h"
#include "ClassObj.h"

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();

	uniqueBase UpDate(uniqueBase own, const GameCtrl &controller);
private:
	int Init(void);
	void Draw(void);

	sharedListObj objList;					// ������߲���
};

int DrawLine(VECTOR2 vec1, VECTOR2 vec2, unsigned int Color, int Thickness);
