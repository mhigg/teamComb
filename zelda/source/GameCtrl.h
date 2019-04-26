// ｺﾝﾄﾛｰﾗｰ(ｷｰﾎﾞｰﾄﾞ)の入力情報を取得する

#pragma once
#include <array>
#include "INPUT_ID.h"

//別名定義
using KEY_ARY = std::array<char, 256>;
using INPUT_ARY = std::array<bool, static_cast<int>(INPUT_ID::MAX)>;

#define INPUT_DOWN	static_cast<int>(INPUT_ID::DOWN)
#define INPUT_LEFT	static_cast<int>(INPUT_ID::LEFT)
#define INPUT_RIGHT static_cast<int>(INPUT_ID::RIGHT)
#define INPUT_UP	static_cast<int>(INPUT_ID::UP)
#define INPUT_ACT_B static_cast<int>(INPUT_ID::ACT_B)
#define INPUT_ACT_X	static_cast<int>(INPUT_ID::ACT_X)
#define INPUT_GET_LB static_cast<int>(INPUT_ID::GET_LB)
#define INPUT_RUN_RB static_cast<int>(INPUT_ID::RUN_RB)
#define INPUT_START static_cast<int>(INPUT_ID::START)
#define INPUT_PAUSE static_cast<int>(INPUT_ID::PAUSE)


enum KEY_TYPE
{
	KEY_TYPE_NOW,	//現在のｷｰ情報
	KEY_TYPE_OLD,	//1ﾌﾚｰﾑ前の情報
	KEY_TYPE_MAX
};

class GameCtrl
{
public:
	GameCtrl();
	~GameCtrl();
	const KEY_ARY &GetCtrl(KEY_TYPE type) const;	//ｷｰ情報取得用関数
	const INPUT_ARY &GetInputState(KEY_TYPE type) const;	// ｹﾞｰﾑﾊﾟｯﾄﾞとｷｰﾎﾞｰﾄﾞの情報取得
	bool UpDate(void);		//ｷｰの押下状態を取得,更新する

private:
	KEY_ARY keyData;	//現在の押下状態
	KEY_ARY keyDataOld;	//1ﾌﾚｰﾑ前の押下状態

	XINPUT_STATE padData;	// 現在のｹﾞｰﾑﾊﾟｯﾄﾞ状態
	int padDataOld;			// 1ﾌﾚｰﾑ前のｹﾞｰﾑﾊﾟｯﾄﾞ状態

	INPUT_ARY inputState;	// ｷｰﾎﾞｰﾄﾞとﾊﾟｯﾄﾞの押下状態 trueなら押されている状態
	INPUT_ARY inputStateOld;
};

