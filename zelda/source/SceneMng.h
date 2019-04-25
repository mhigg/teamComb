// �ްѓ��̼�ݑJ�ڂ��Ǘ�����E�ް�ٰ��

#pragma once
#include <memory>
#include "BaseScene.h"

#define lpSceneMng SceneMng::GetInstance()

class GameCtrl;

class SceneMng
{
public:
	static SceneMng & GetInstance(void)
	{
		static SceneMng s_instance;
		return s_instance;
	}

	void Run(void);


private:
	SceneMng();
	~SceneMng();
	bool Init(void);

	uniqueBase activeScene;
	std::unique_ptr<GameCtrl> gameCtrl;
};

