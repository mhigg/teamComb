#pragma once
#include <vector>
#include "VECTOR2.h"
#include "MAP_ID.h"
#include "ClassObj.h"

#define lpInfoCtrl InfoCtrl::GetInstance()
constexpr auto ENEMY_MAX = 20;

struct Info {
	std::vector<VECTOR2> pos;			// ç¿ïWä«óù
	std::vector<bool> flag;					// ë∂ç›Ç∑ÇÈÇ©Ç«Ç§Ç©
};

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
	VECTOR2 GetPlayerPos(int num);
	VECTOR2 GetEnemyPos(int num);
private:
	InfoCtrl();
	~InfoCtrl();

	void Init(void);
	template<typename objType>
	bool SetData(objType type, const VECTOR2 & pos, int num,bool flag);

	template<typename objType>
	VECTOR2 GetData(objType type,int num);

	Info player;
	Info enemy;
};

