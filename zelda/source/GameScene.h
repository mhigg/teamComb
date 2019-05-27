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
	int Init(void);				// 初期化				
	void Draw(void);			// 描画

	sharedListObj objList;		// ｼｪｱﾄﾞﾎﾟｲﾝﾀｰ
	int gameFrame;				// ｹﾞｰﾑ中の経過時間
};

int DrawLine(VECTOR2 vec1, VECTOR2 vec2, unsigned int Color, int Thickness);
