// ﾏｯﾌﾟID関連で、ﾏｯﾌﾟ上の情報を操作するｸﾗｽ

#pragma once
#include "VECTOR2.h"
#include "MAP_ID.h"

#define lpMapCtrl MapCtrl::GetInstance()

class MapCtrl
{
public:
	static MapCtrl &GetInstance(void)
	{
		static MapCtrl s_Instance;
		return s_Instance;
	}
	MapCtrl();
	~MapCtrl();

	bool SetUp(VECTOR2 stageSize, VECTOR2 chipSize);	// ﾏｯﾌﾟﾃﾞｰﾀのﾘｻｲｽﾞ・初期化
	bool SetMapData(VECTOR2 mapPos, MAP_ID id);			// ﾏｯﾌﾟIDの設定(大体ｴﾃﾞｨｯﾄ用？)
	MAP_ID GetMapData(VECTOR2 mapPos);					// 指定したﾏｽのﾏｯﾌﾟIDを取得

	// ﾏｯﾌﾟ描画
	void MapDraw(void);

private:
	int lineColor;		// ﾗｲﾝｶﾗｰ

	VECTOR2 stageSize;
};
