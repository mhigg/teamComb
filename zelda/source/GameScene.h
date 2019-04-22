#pragma once
#include "BaseScene.h"
class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();

	uniqueBase UpDate(uniqueBase own, const GameCtrl &controller);
private:
	int Init(void);
	
};

