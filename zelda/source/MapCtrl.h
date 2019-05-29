// Ï¯ÌßIDŠÖ˜A‚ÅAÏ¯Ìßã‚Ìî•ñ‚ğ‘€ì‚·‚é¸×½

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

	// Ï¯ÌßÃŞ°À‚ÌØ»²½ŞE‰Šú‰»
	bool SetUp(VECTOR2 chipSize, VECTOR2 drawOffset);

	// Ï¯Ìß¾°ÌŞ©´ÃŞ¨¯Ä
	bool MapSave(void);

	// Ï¯ÌßÛ°ÄŞ
	bool MapLoad(sharedListObj objList, bool editFlag);

	// modeFlag:true¨EditMode false¨GameMode
	bool SetUpGameObj(sharedListObj objList, bool modeFlag);

	bool SetUpEnemy(sharedListObj objList, int enemyNum,int x,int y);

	// Ï¯Ìß•`‰æ
	void Draw(bool flag);

	// ½¸Û°Ù’l‚Ì‰ÁZ
	void AddScroll(VECTOR2 scrollOffset, int plNum);

private:
	MapCtrl();
	~MapCtrl();

	void ItemDraw(VECTOR2 offset, VECTOR2 scrSize, VECTOR2 XYoffset, int pIdx);

	template<typename mapType, typename idType>
	bool SetData(mapType maps, const VECTOR2 & pos, idType id);

	template<typename mapType, typename idType>
	idType GetData(mapType maps, const VECTOR2 & pos, idType defID);

	int lineColor;		// ×²İ¶×°

	std::vector<MAP_ID*>	mapData;			// Ï¯Ìß—p‚Ì“ñŸŒ³ÃŞ°À
	std::vector<MAP_ID>		mapData_Base;		// Ï¯Ìß—p‚ÌÃŞ°À
	std::vector<MAP_ID*>	itemData;			// Ï¯Ìß‚ÌÊßÈÙ‚Ì“ñŸŒ³ÃŞ°À
	std::vector<MAP_ID>		itemData_Base;		// Ï¯Ìß‚ÌÊßÈÙÃŞ°À

	std::vector<VECTOR2> scrollTbl;				// ÌßÚ²Ô°‚²‚Æ‚Ì½¸Û°ÙµÌ¾¯Ä‚ğŠi”[
	std::array<VECTOR2, 4> plScrTbl;			// •ªŠ„‚ÌŠe‰æ–Ê‚Ì¶ã

	std::vector<int> mapImage;					// ÌßÚ²Ô°‚²‚Æ‚Ì— •`‰æ½¸Ø°İÊİÄŞÙ
	int drawHandle;			// 4l•ª‚ÌÏ¯Ìß•`‰æÊİÄŞÙ

	VECTOR2 stageSize;		// ½Ã°¼Ş‚ÌÏ½–Ú”
	VECTOR2 chipSize;		// Ï½‚Ì‘å‚«‚³
	VECTOR2 drawOffset;		// •`‰æµÌ¾¯Ä
};
