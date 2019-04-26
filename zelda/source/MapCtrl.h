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

	bool SetUp(VECTOR2 stageSize, VECTOR2 chipSize);	// ϯ���ް���ػ��ށE������
	bool SetMapData(VECTOR2 mapPos, MAP_ID id);			// ϯ��ID�̐ݒ�(��̴�ި�ėp�H)
	MAP_ID GetMapData(VECTOR2 mapPos);					// �w�肵��Ͻ��ϯ��ID���擾

	// ϯ�ߕ`��
	void MapDraw(void);

private:
	int lineColor;		// ײݶװ

	VECTOR2 stageSize;
};
