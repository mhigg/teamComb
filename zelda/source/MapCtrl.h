// ﾏｯﾌﾟID関連で、ﾏｯﾌﾟ上の情報を操作するｸﾗｽ

#pragma once
#include <vector>
#include <array>
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
	VECTOR2 GetItemPos(MAP_ID id,int num);

	// ﾏｯﾌﾟﾃﾞｰﾀのﾘｻｲｽﾞ・初期化
	bool SetUp(VECTOR2 chipSize, VECTOR2 drawOffset);

	// ﾏｯﾌﾟｾｰﾌﾞ←ｴﾃﾞｨｯﾄ
	bool MapSave(void);

	// ﾏｯﾌﾟﾛｰﾄﾞ
	bool MapLoad(sharedListObj objList, bool editFlag);

	// modeFlag:true→EditMode false→GameMode
	bool SetUpGameObj(sharedListObj objList, bool modeFlag);

	bool SetUpEnemy(sharedListObj objList, int enemyNum,int x,int y);

	// ﾏｯﾌﾟ描画
	void Draw(bool flag);

	// ｽｸﾛｰﾙ値の加算
	void AddScroll(VECTOR2 scrollOffset, int plNum);

private:
	MapCtrl();
	~MapCtrl();

	void ItemDraw(VECTOR2 offset, VECTOR2 scrSize, VECTOR2 XYoffset, int pIdx);

	template<typename mapType, typename idType>
	bool SetData(mapType maps, const VECTOR2 & pos, idType id);

	template<typename mapType, typename idType>
	idType GetData(mapType maps, const VECTOR2 & pos, idType defID);

	int lineColor;		// ﾗｲﾝｶﾗｰ

	std::vector<MAP_ID*>	mapData;			// ﾏｯﾌﾟ用の二次元ﾃﾞｰﾀ
	std::vector<MAP_ID>		mapData_Base;		// ﾏｯﾌﾟ用のﾃﾞｰﾀ
	std::vector<MAP_ID*>	itemData;			// ﾏｯﾌﾟのﾊﾟﾈﾙの二次元ﾃﾞｰﾀ
	std::vector<MAP_ID>		itemData_Base;		// ﾏｯﾌﾟのﾊﾟﾈﾙﾃﾞｰﾀ

	std::vector<VECTOR2> scrollTbl;				// ﾌﾟﾚｲﾔｰごとのｽｸﾛｰﾙｵﾌｾｯﾄを格納
	std::array<VECTOR2, 4> plScrTbl;			// 分割時の各画面の左上

	std::vector<int> mapImage;					// ﾌﾟﾚｲﾔｰごとの裏描画ｽｸﾘｰﾝﾊﾝﾄﾞﾙ
	int drawHandle;			// 4人分のﾏｯﾌﾟ描画ﾊﾝﾄﾞﾙ

	VECTOR2 stageSize;		// ｽﾃｰｼﾞのﾏｽ目数
	VECTOR2 chipSize;		// ﾏｽの大きさ
	VECTOR2 drawOffset;		// 描画ｵﾌｾｯﾄ
};
