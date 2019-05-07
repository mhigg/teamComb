// ϯ��ID�֘A�ŁAϯ�ߏ�̏��𑀍삷��׽

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
	bool SetMapData(VECTOR2 mapPos, MAP_ID id);			// ϯ��ID�̐ݒ�(��̴�ި�ėp�H)
	MAP_ID GetMapData(VECTOR2 mapPos);					// �w�肵��Ͻ��ϯ��ID���擾

	// ϯ���ް���ػ��ށE������
	bool SetUp(VECTOR2 chipSize, VECTOR2 drawOffset);

	// GameMode�̂݁A��ڲ԰��ݽ�ݽ����֐� 1�̲ݽ�ݽ������2�̖ڈȍ~�Ͳݽ�ݽ����Ȃ�
	// modeFlag:true��EditMode false��GameMode
	bool SetUpGameObj(sharedListObj objList, bool modeFlag);

	// ϯ�ߕ`��
	void Draw(bool flag);

private:
	MapCtrl();
	~MapCtrl();

	int lineColor;		// ײݶװ

	std::vector<MAP_ID*> mapData;
	std::vector<MAP_ID> mapData_Base;
	VECTOR2 stageSize;
	VECTOR2 chipSize;
	VECTOR2 drawOffset;
};
