// ��޼ު�Ă̲ݽ�ݽ�Eϯ�߂�۰�ނȂǁAMapCtrl�����Ƃ�ϯ�ߏ����Ǘ��E���p����

#pragma once
#include <memory>
#include <vector>
#include "MapCtrl.h"
#include "MAP_ID.h"
#include "VECTOR2.h"

#define lpStageMng StageMng::GetInstance()


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
	void MapLoad(void);

	const VECTOR2& GetChipSize(void);		// ChipSize�̎擾
	const VECTOR2& GetStageSize(void);		// StageSize�̎擾
	std::vector<MAP_ID> GetMap(void);

private:
	StageMng();
	~StageMng();

	bool Init(void);

//	std::unique_ptr<MapCtrl> mapCtrl;

	std::vector<MAP_ID> mapData;  // �ð��ϯ���ް�
	VECTOR2 stageSize;	// �ð�޻���
	VECTOR2 chipSize;	// �Q�[���T�C�Y
};

