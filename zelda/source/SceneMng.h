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

	void Run(void);								// ¹Ş°ÑÙ°Ìß
	VECTOR2 GetDrawOffset(void);				// •`‰æµÌ¾¯Ä‚ğæ“¾
	void SetDrawOffset(VECTOR2 drawOffset);
	VECTOR2 GetPlayScreen(void);				// 4•ªŠ„‚Ì1‰æ–Ê‚Ì»²½Ş‚ğæ“¾
	int GetFram(void);							// ¹Ş°Ñ‹N“®‚©‚ç‚ÌÌÚ°Ñ”‚ğæ“¾

private:
	SceneMng();
	~SceneMng();
	bool Init(void);

	VECTOR2 drawOffset;
	int framCnt;

	uniqueBase activeScene;
	std::unique_ptr<GameCtrl> gameCtrl;
};

