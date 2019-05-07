// ��޼ު�Ă̲ݽ�ݽ�Eϯ�߂�۰�ނȂǁAMapCtrl�����Ƃ�ϯ�ߏ����Ǘ��E���p����

#pragma once
#include <memory>
#include <vector>
#include "MapCtrl.h"
#include "MAP_ID.h"
#include "VECTOR2.h"

#define lpStageMng StageMng::GetInstance()

constexpr int GAME_AREA_SIZE_X = 800;		// ϯ�ߑS�̻̂���
constexpr int GAME_AREA_SIZE_Y = 600;

class StageMng
{
public:
	static StageMng & GetInstance(void)
	{
		static StageMng s_instance;
		return s_instance;
	}

	// ϯ�߾��ށ���ި��
	void MapSave(void);

	// ϯ��۰��
	void MapLoad(sharedListObj objList, bool editFlag);

	const VECTOR2& GetChipSize(void);		// ChipSize�̎擾
	const VECTOR2& GetStageSize(void);		// StageSize�̎擾
	const VECTOR2& GetDrawOffset(void);		// drawOffset�̎擾


private:
	StageMng();
	~StageMng();

	bool Init(void);


	std::vector<MAP_ID*> mapData;  // �ð��ϯ���ް�
	std::vector<MAP_ID> mapData_Base;
	VECTOR2 stageSize;	// �ð�޻���
	VECTOR2 chipSize;	// 1Ͻ�̻���
	VECTOR2 drawOffset;
};

