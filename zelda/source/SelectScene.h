#pragma once
#include "BaseScene.h"

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
	void SelectDraw(void);
	int Init(void);

	SELECT_CHARA selectChara;	// プレイヤー毎の今選択しているキャラ
	SELECT_POS selectPos;		// プレイヤー毎の立ち絵位置
};

