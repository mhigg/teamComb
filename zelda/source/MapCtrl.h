// ﾏｯﾌﾟID関連で、ﾏｯﾌﾟ上の情報を操作するｸﾗｽ

#pragma once
#include <vector>
#include "VECTOR2.h"
#include "MAP_ID.h"
#include "ClassObj.h"

#define lpMapCtrl MapCtrl::GetInstance()

class MapCtrl
{
public:
	static MapCtrl &GetInstance(void)
	{
		static MapCtrl s_Instance;
		return s_Instance;
	}
	bool SetMapData(VECTOR2 mapPos, MAP_ID id);			// ﾏｯﾌﾟIDの設定(大体ｴﾃﾞｨｯﾄ用？)
	MAP_ID GetMapData(VECTOR2 mapPos);					// 指定したﾏｽのﾏｯﾌﾟIDを取得

	// ﾏｯﾌﾟﾃﾞｰﾀのﾘｻｲｽﾞ・初期化
	bool SetUp(VECTOR2 chipSize, VECTOR2 drawOffset);

	// GameModeのみ、ﾌﾟﾚｲﾔｰをｲﾝｽﾀﾝｽする関数 1体ｲﾝｽﾀﾝｽしたら2体目以降はｲﾝｽﾀﾝｽされない
	// modeFlag:true→EditMode false→GameMode
	bool SetUpGameObj(sharedListObj objList, bool modeFlag);

	// ﾏｯﾌﾟ描画
	void Draw(bool flag);

private:
	MapCtrl();
	~MapCtrl();

	int lineColor;		// ﾗｲﾝｶﾗｰ

	std::vector<MAP_ID*> mapData;
	std::vector<MAP_ID> mapData_Base;
	VECTOR2 stageSize;
	VECTOR2 chipSize;
	VECTOR2 drawOffset;
};
