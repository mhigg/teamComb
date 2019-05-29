#pragma once
#include <array>
#include "Obj.h"
#include "GameCtrl.h"

enum WEP_TYPE {
	WEP_KNIFE,
	WEP_PISTOL,
	WEP_MAX
};

using STR_IMG = std::array<std::array<std::string, WEP_MAX>, DIR_MAX>;

class Weapon :
	public Obj
{
public:
	Weapon();
	Weapon(WEP_TYPE weapon, DIR dir, VECTOR2 setUpPos, VECTOR2 scrollOffset, VECTOR2 drawOffset);
	~Weapon();

	int WeaponInit(WEP_TYPE weapon);
	bool initAnim(void);
	bool CheckDeath(void);				// ���S����@��{����łȂ����false
	bool CheckObjType(OBJ_TYPE type);	// �w�肵���l�Ɠ����^��������true��Ԃ�

private:
	void SetMove(const GameCtrl &controller, weakListObj objList);

	STR_IMG AtkImgTbl;

	WEP_TYPE weapon;	// ��������
};

