#pragma once
#include "BaseScene.h"
#include <array>

constexpr auto MENU_NUM		= 3;
constexpr auto BOX_SIZE_X	= 460;
constexpr auto SIZE_Y			= 90;			// 変えなくていいかも
constexpr auto PUSH_SIZE		= 40;			// 選択中のﾒﾆｭｰﾊﾞｰのｵﾌｾｯﾄ


using BOX_ARRAY = std::array< VECTOR2 , MENU_NUM >;
using MOVE_FLAG = std::array<   bool  , MENU_NUM >;
using SELECT_POINT = std::array<   int, MENU_NUM >;

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
	void MenuDraw(void);		// 描画
	int Init(void);						// 初期化

	BOX_ARRAY movePos;		// Boxの座標を持つ配列
	MOVE_FLAG moveFlag;		// Boxの移動制御用配列
	SELECT_POINT selectPoint; // 選んでいる奴の加算値
	int nowSelect;					 // どのモードを選択しているか
	bool pushFlag;

	unsigned int count;				// MenuScene中のｶｳﾝﾄ
	double add;						// ﾒﾆｭｰﾊﾞｰの加算値
	VECTOR2 size;					// Boxのｻｲｽﾞ
};

