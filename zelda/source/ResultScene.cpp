#include "DxLib.h"
#include "ImageMng.h"
#include "GameScene.h"
#include "ScoreBoard.h"
#include "ResultScene.h"

ResultScene::ResultScene()
{
	ResultScene::Init();
}

ResultScene::~ResultScene()
{
}

uniqueBase ResultScene::UpDate(uniqueBase own, const GameCtrl & controller)
{
	return std::move(own);
}

void ResultScene::ResultDraw(void)
{
	VECTOR2 tmp1(0, 0);
	VECTOR2 tmp2(0, GAME_SCREEN_SIZE_Y);

	for (; tmp1.x <= GAME_SCREEN_SIZE_X; tmp1.x += 800)
	{
		tmp2.x = tmp1.x;
		DrawLine(tmp1, tmp2, 0x00ffffff, true);
	}
	tmp1 = VECTOR2(0, 0);
	tmp2.x = GAME_SCREEN_SIZE_X;
	for (; tmp1.y <= GAME_SCREEN_SIZE_Y; tmp1.y += 480)
	{
		tmp2.y = tmp1.y;
		DrawLine(tmp1, tmp2, 0x00ffffff, true);
	}
}

int ResultScene::Init(void)
{
	bonusPoint = {
		0,0,0,0
	};
	return 0;
}
