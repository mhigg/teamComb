#pragma once
#include "BaseScene.h"
#include <array>

constexpr auto MENU_NUM		= 4;
constexpr auto BOX_SIZE_X	= 250;
constexpr auto BOX_SIZE_Y	= 80;



using BOX_ARRAY = std::array< VECTOR2 , MENU_NUM >;
using MOVE_FLAG = std::array<   bool  , MENU_NUM >;

class MenuScene :
	public BaseScene
{
public:
	MenuScene();
	~MenuScene();
	uniqueBase UpDate(					// 更新
		uniqueBase own,					// 現在のｼｰﾝ
		const GameCtrl &controller		// ｷｰ取得
	);
private:
	void MenuDraw(void);	// 描画
	int Init(void);			// 初期化

	BOX_ARRAY movePos;		// Boxの座標を持つ配列
	MOVE_FLAG moveFlag;		// Boxの移動制御用配列

	unsigned int count;		// MenuScene中のｶｳﾝﾄ
	int add;
	VECTOR2		 size;		// Boxのｻｲｽﾞ
};

