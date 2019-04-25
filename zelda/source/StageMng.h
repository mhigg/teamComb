// ��޼ު�Ă̲ݽ�ݽ�Eϯ�߂�۰�ނȂǁAMapCtrl�����Ƃ�ϯ�ߏ����Ǘ��E���p����

#pragma once
#include <memory>
#include "VECTOR2.h"

#define lpStageMng StageMng::GetInstance()

class MapCtrl;

class StageMng
{
public:
	static StageMng & GetInstance(void)
	{
		static StageMng s_instance;
		return s_instance;
	}

	// ϯ�߾���
	void MapSave(void);

	// ϯ��۰��
	void MapLoad(void);

	// ϯ�ߕ`��
	void MapDraw(void);

private:
	StageMng();
	~StageMng();

	bool Init(void);

	std::unique_ptr<MapCtrl> mapCtrl;

	int lineColor;		// ײݶװ
	VECTOR2 stageSize;	// �ð�޻���
};

