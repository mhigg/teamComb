#pragma once
#include "BaseScene.h"
class SelectScene :
	public BaseScene
{
public:
	SelectScene();
	~SelectScene();
	uniqueBase UpDate(						// 更新
		uniqueBase own,					// 現在のｼｰﾝ
		const GameCtrl &controller		// ｷｰ取得
	);
private:
	void SelectDraw(void);
	int Init(void);
};

