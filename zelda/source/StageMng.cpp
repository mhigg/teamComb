#include <memory>
#include "StageMng.h"
#include "MapCtrl.h"



StageMng::StageMng()
{
	Init();
}


StageMng::~StageMng()
{
}

bool StageMng::Init(void)
{
	mapCtrl = std::make_unique<MapCtrl>();

	return true;
}
