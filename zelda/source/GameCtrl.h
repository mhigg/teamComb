#pragma once
#include <array>

//別名定義
using KEY_ARY = std::array<char, 256>;

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
	const int &GetPadData(KEY_TYPE type) const;	//ｷｰ情報取得用関数
	bool UpDate(void);		//ｷｰの押下状態を取得,更新する

private:
	KEY_ARY keyData;	//現在の押下状態
	KEY_ARY keyDataOld;	//1ﾌﾚｰﾑ前の押下状態

	int padData;
	int padDataOld;
};

