#pragma once
#include <memory>
#include "BaseScene.h"
#include "VECTOR2.h"
#include "ClassObj.h"

class Player;

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();

	uniqueBase UpDate(uniqueBase own, const GameCtrl &controller);
private:
	int Init(void);				// ������				
	void Draw(void);			// �`��

	sharedListObj objList;		// ������߲���
	int gameFrame;				// �ްђ��̌o�ߎ���
	int tile;
	int ghGameScreen[4];
	int gameScreen;
	std::shared_ptr<Player> player;
};

int DrawLine(VECTOR2 vec1, VECTOR2 vec2, unsigned int Color, int Thickness);
