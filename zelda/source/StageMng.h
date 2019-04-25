// ��޼ު�Ă̲ݽ�ݽ�Eϯ�߂�۰�ނȂǁAMapCtrl�����Ƃ�ϯ�ߏ����Ǘ��E���p����

#pragma once
#include <memory>

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

	// ϯ��۰��

private:
	StageMng();
	~StageMng();

	bool Init(void);

	std::unique_ptr<MapCtrl> mapCtrl;
};

