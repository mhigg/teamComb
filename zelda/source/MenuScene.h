#pragma once
#include "BaseScene.h"
class MenuScene :
	public BaseScene
{
public:
	MenuScene();
	~MenuScene();
	uniqueBase UpDate(						// 更新
		uniqueBase own,					// 現在のｼｰﾝ
		const GameCtrl &controller		// ｷｰ取得
	);
private:
	void MenuDraw(void); // 描画
	int Init(void);
};

