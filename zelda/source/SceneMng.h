// ¹Ş°Ñ“à‚Ì¼°İ‘JˆÚ‚ğŠÇ—‚·‚éE¹Ş°ÑÙ°Ìß

#pragma once
#include <memory>
#include "BaseScene.h"
#include "VECTOR2.h"

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
	VECTOR2 GetDrawOffset(void);
	void SetDrawOffset(VECTOR2 drawOffset);

private:
	SceneMng();
	~SceneMng();
	bool Init(void);

	VECTOR2 drawOffset;

	uniqueBase activeScene;
	std::unique_ptr<GameCtrl> gameCtrl;
};

