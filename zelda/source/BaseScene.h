#pragma once
#include <memory>
#include "GameCtrl.h"

constexpr int GAME_SCREEN_X = 0;			// µÌ¾¯Ä
constexpr int GAME_SCREEN_Y = 0;

constexpr int GAME_SCREEN_SIZE_X = 1200;	// ‰æ–Ê‰ð‘œ“x
constexpr int GAME_SCREEN_SIZE_Y = 880;

constexpr int CHIP_SIZE = 40;				// 1Ï½‚Ì’·‚³

class BaseScene;

using uniqueBase = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	virtual ~BaseScene();
	virtual uniqueBase UpDate(uniqueBase own, const GameCtrl &controller) = 0;

private:
	virtual int Init(void) = 0;
};

