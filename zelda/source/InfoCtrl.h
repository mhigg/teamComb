#pragma once
#include <vector>
#include <array>
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
	bool SetAddScroll(const VECTOR2 & offset, int num);					// ��ڲ԰�݂̂��Ă�
	bool SetScore(int val, int num);									// ������(ػ��ėp)
	bool SetBonus(int val, int num);									// �ްŽ���(ػ��ėp)
	VECTOR2 GetPlayerPos(int num);
	VECTOR2 GetEnemyPos(int num);
	bool GetPlayerFlag(int num);
	bool GetEnemyFlag(int num);
	VECTOR2 GetAddScroll(int num);							
	int GetScore(int num);												// ����擾(ػ��ėp)
	int GetBonus(int num);												// �ްŽ�擾(ػ��ėp)
private:
	InfoCtrl();
	~InfoCtrl();

	void Init(void);
	std::vector<VECTOR2> enPos;			// ���W�Ǘ�
	std::vector<bool> enFlag;					// ���݂��邩�ǂ���
	std::vector<VECTOR2>plPos;
	std::vector<bool> plFlag;
	std::vector<VECTOR2> scrNum;
	std::array<int, 4> plScore;
	std::array< int, 4 > plBonus;
};

