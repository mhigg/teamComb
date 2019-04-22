#pragma once
#include <memory>
#include "GameCtrl.h"

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

