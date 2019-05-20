// ﾏｯﾌﾟID関連で、ﾏｯﾌﾟ上の情報を操作するｸﾗｽ

#pragma once
#include <vector>
#include <array>
#include "Player.h"
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
	bool SetMapData(const VECTOR2 & pos, MAP_ID id);
	bool SetItemData(const VECTOR2 & pos, MAP_ID id);

	MAP_ID GetMapData(const VECTOR2 & pos);
	MAP_ID GetItemData(const VECTOR2 & pos);

	// ﾏｯﾌﾟﾃﾞｰﾀのﾘｻｲｽﾞ・初期化
	bool SetUp(VECTOR2 chipSize, VECTOR2 drawOffset);

	// ﾏｯﾌﾟｾｰﾌﾞ←ｴﾃﾞｨｯﾄ
	bool MapSave(void);

	// ﾏｯﾌﾟﾛｰﾄﾞ
	bool MapLoad(sharedListObj objList, bool editFlag);

	// GameModeのみ、ﾌﾟﾚｲﾔｰをｲﾝｽﾀﾝｽする関数 1体ｲﾝｽﾀﾝｽしたら2体目以降はｲﾝｽﾀﾝｽされない
	// modeFlag:true→EditMode false→GameMode
	bool SetUpGameObj(sharedListObj objList, bool modeFlag);

	// ﾏｯﾌﾟ描画
	void Draw(bool flag);
	void ItemDraw(VECTOR2 offset);

	// ｽｸﾛｰﾙ値の加算
	void AddScroll(VECTOR2 scrollOffset, int plNum);

private:
	MapCtrl();
	~MapCtrl();

	template<typename mapType, typename idType>
	bool SetData(mapType maps, const VECTOR2 & pos, idType id);

	template<typename mapType, typename idType>
	idType GetData(mapType maps, const VECTOR2 & pos, idType defID);

	int lineColor;		// ﾗｲﾝｶﾗｰ

	std::vector<MAP_ID*>	mapData;				// ﾏｯﾌﾟ用の二次元ﾃﾞｰﾀ
	std::vector<MAP_ID>		mapData_Base;		// ﾏｯﾌﾟ用のﾃﾞｰﾀ
	std::vector<MAP_ID*>	itemData;				// ﾏｯﾌﾟのﾊﾟﾈﾙの二次元ﾃﾞｰﾀ
	std::vector<MAP_ID>		itemData_Base;		// ﾏｯﾌﾟのﾊﾟﾈﾙﾃﾞｰﾀ

	std::vector<VECTOR2> scrollTbl;			// ﾌﾟﾚｲﾔｰごとのｽｸﾛｰﾙｵﾌｾｯﾄを格納
	std::array<VECTOR2, 4> plScrTbl;			// 分割時の各画面の左上

	VECTOR2 stageSize;		// ｽﾃｰｼﾞのﾏｽ目数
	VECTOR2 chipSize;			// ﾏｽの大きさ
	VECTOR2 drawOffset;		// 描画ｵﾌｾｯﾄ
	VECTOR2 scrollOffset;	// ｽｸﾛｰﾙｵﾌｾｯﾄ

	bool flag;
};
