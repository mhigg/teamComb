#pragma once
#include "BaseScene.h"

constexpr auto CHARA_NUM = 4;

using SELECT_CHARA = std::array< bool, CHARA_NUM >;

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

	SELECT_CHARA selectChara;
	int nowChara;	// 今選択しているキャラ
};

