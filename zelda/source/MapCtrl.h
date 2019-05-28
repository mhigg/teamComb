// ϯ��ID�֘A�ŁAϯ�ߏ�̏��𑀍삷��׽

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

	// ϯ���ް���ػ��ށE������
	bool SetUp(VECTOR2 chipSize, VECTOR2 drawOffset);

	// ϯ�߾��ށ���ި��
	bool MapSave(void);

	// ϯ��۰��
	bool MapLoad(sharedListObj objList, bool editFlag);

	// modeFlag:true��EditMode false��GameMode
	bool SetUpGameObj(sharedListObj objList, bool modeFlag);

	bool SetUpEnemy(sharedListObj objList, int enemyNum,int x,int y);

	// ϯ�ߕ`��
	void Draw(bool flag);

	// ��۰ْl�̉��Z
	void AddScroll(VECTOR2 scrollOffset, int plNum);

private:
	MapCtrl();
	~MapCtrl();

	void ItemDraw(VECTOR2 offset, VECTOR2 scrSize, VECTOR2 XYoffset, int pIdx);

	template<typename mapType, typename idType>
	bool SetData(mapType maps, const VECTOR2 & pos, idType id);

	template<typename mapType, typename idType>
	idType GetData(mapType maps, const VECTOR2 & pos, idType defID);

	int lineColor;		// ײݶװ

	std::vector<MAP_ID*>	mapData;			// ϯ�ߗp�̓񎟌��ް�
	std::vector<MAP_ID>		mapData_Base;		// ϯ�ߗp���ް�
	std::vector<MAP_ID*>	itemData;			// ϯ�߂����ق̓񎟌��ް�
	std::vector<MAP_ID>		itemData_Base;		// ϯ�߂������ް�

	std::vector<VECTOR2> scrollTbl;				// ��ڲ԰���Ƃ̽�۰ٵ̾�Ă��i�[
	std::array<VECTOR2, 4> plScrTbl;			// �������̊e��ʂ̍���

	std::vector<int> mapImage;					// ��ڲ԰���Ƃ̗��`�潸ذ������
	int drawHandle;			// 4�l����ϯ�ߕ`�������

	VECTOR2 stageSize;		// �ð�ނ�Ͻ�ڐ�
	VECTOR2 chipSize;		// Ͻ�̑傫��
	VECTOR2 drawOffset;		// �`��̾��
};
