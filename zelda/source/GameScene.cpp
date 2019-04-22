#include "GameScene.h"


GameScene::GameScene()
{
	Init();
}


GameScene::~GameScene()
{
}

uniqueBase GameScene::UpDate(uniqueBase own, const GameCtrl & controller)
{
	return move(own);
}

int GameScene::Init(void)
{
	return 0;
}
