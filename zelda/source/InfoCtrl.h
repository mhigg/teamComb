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
	bool SetPlayerPos(const VECTOR2 & pos, int num, bool flag);
	bool SetEnemyPos(const VECTOR2 & pos, int num, bool flag);
	bool SetAddScroll(const VECTOR2 & offset, int num);					// ﾌﾟﾚｲﾔｰのみが呼ぶ
	VECTOR2 GetPlayerPos(int num);
	VECTOR2 GetEnemyPos(int num);
	VECTOR2 GetAddScroll(int num);
private:
	InfoCtrl();
	~InfoCtrl();

	void Init(void);
	//struct Info {
	//	std::vector<VECTOR2> pos;			// 座標管理
	//	std::vector<bool> flag;					// 存在するかどうか
	//};
	//Info player;
	//Info enemy;
	std::vector<VECTOR2> enPos;			// 座標管理
	std::vector<bool> enFlag;					// 存在するかどうか
	std::vector<VECTOR2>plPos;
	std::vector<bool> plFlag;
	std::vector<VECTOR2> scrNum;
};

