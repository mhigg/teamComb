#pragma once
#include <vector>
#include "VECTOR2.h"
#include "MAP_ID.h"
#include "ClassObj.h"

#define lpInfoCtrl InfoCtrl::GetInstance()
constexpr auto ENEMY_MAX = 4;

class InfoCtrl
{
public:
	static InfoCtrl &GetInstance(void)
	{
		static InfoCtrl s_Instance;
		return s_Instance;
	}
	bool SetPlayerPos(const VECTOR2 & pos, int num);
	bool SetPlayerFlag(bool flag, int num);
	bool SetEnemyPos(const VECTOR2 & pos, int num);
	bool SetEnemyFlag(bool flag, int num);
	bool SetAddScroll(const VECTOR2 & offset, int num);					// Ãﬂ⁄≤‘∞ÇÃÇ›Ç™åƒÇ‘
	VECTOR2 GetPlayerPos(int num);
	VECTOR2 GetEnemyPos(int num);
	bool GetPlayerFlag(int num);
	bool GetEnemyFlag(int num);
	VECTOR2 GetAddScroll(int num);
private:
	InfoCtrl();
	~InfoCtrl();

	void Init(void);
	std::vector<VECTOR2> enPos;			// ç¿ïWä«óù
	std::vector<bool> enFlag;					// ë∂ç›Ç∑ÇÈÇ©Ç«Ç§Ç©
	std::vector<VECTOR2>plPos;
	std::vector<bool> plFlag;
	std::vector<VECTOR2> scrNum;
};

