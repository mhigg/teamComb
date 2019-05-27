#pragma once
#include "BaseScene.h"
#include <array>

constexpr auto CHARA_NUM = 4;

using SELECT_CHARA = std::array< int, CHARA_NUM >;
using SELECT_POS = std::array< VECTOR2, CHARA_NUM >;

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
	void SelectDraw(void);		// 描画
	int Init(void);				// 初期化

	SELECT_CHARA selectChara;	// ﾌﾟﾚｲﾔｰ毎の今選択しているｷｬﾗ
	SELECT_POS selectPos;		// ﾌﾟﾚｲﾔｰ毎の立ち絵位置
	int selectMode;				// 選んだﾓｰﾄﾞ
	int backChange;				// 背景切り替えの時間
};

