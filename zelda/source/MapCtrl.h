// ϯ��ID�֘A�ŁAϯ�ߏ�̏��𑀍삷��׽

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

	bool SetUp(VECTOR2 stageSize, VECTOR2 chipSize);
	bool SetMapData(VECTOR2 mapPos, MAP_ID id);

	const VECTOR2& GetChipSize(void);						// ChipSize�̎擾

private:
	VECTOR2 chipSize;	// �Q�[���T�C�Y
};
