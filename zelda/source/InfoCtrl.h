#pragma once
#include <vector>
#include "VECTOR2.h"
#include "MAP_ID.h"
#include "ClassObj.h"

#define lpInfoCtrl InfoCtrl::GetInstance()
constexpr auto ENEMY_MAX = 20;

class InfoCtrl
{
public:
	static InfoCtrl &GetInstance(void)
	{
		static InfoCtrl s_Instance;
		return s_Instance;
	}
	bool SetPlayerPos(const VECTOR2 & pos);
	bool SetEnemyPos(const VECTOR2 & pos);

	VECTOR2 GetPlayerPos(void);
	VECTOR2 GetEnemyPos(void);
private:
	InfoCtrl();
	~InfoCtrl();

	void Init(void);

	std::vector<VECTOR2> playerPos;			// Ãﬂ⁄≤‘∞ÇÃç¿ïWä«óù
	std::vector<VECTOR2> enemyPos;			// ¥»–∞ÇÃç¿ïWä«óù
};

