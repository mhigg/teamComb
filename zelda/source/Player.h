#pragma once
#include <array>
#include "VECTOR2.h"
#include "Obj.h"
#include "MapCtrl.h"
#include "GameCtrl.h"

enum TBL_ID {
	TBL_MAIN,		// �ړ�����
	TBL_OPP,		// �ړ������̋t�̎�
	TBL_MAX
};

enum DIR_TBL_ID {
	DIR_TBL_MAIN,	// �ړ�����
	DIR_TBL_REV,	// �ړ����Ă�������̋t
	DIR_TBL_OPP1,	// �ړ������̋t�̎��@
	DIR_TBL_OPP2,	// �ړ������̋t�̎��A
	DIR_TBL_MAX
};

enum SIDE_CHECK {
	OUT_SIDE,	// 0
	IN_SIDE,	// 1
	SIDE_MAX
};

#define PL_DEF_SPEED 2

using DIR_TBL_ARRAY = std::array<int, DIR_MAX>;
using DIR_TBL_PTR = std::array<int*[TBL_MAX], DIR_MAX>;
using DIR_TBL_DIR = std::array<DIR[DIR_TBL_MAX], DIR_MAX>;
// using MAP_MOVE_TBL = std::array<bool, static_cast<int>(MAP_ID::MAX)>; ���A�C�e�����Q����ǉ������Ƃ��Ɏg��


class Player :
	public Obj
{
public:
	Player(VECTOR2 setUpPos, VECTOR2 drawOffset);	// �����t���R���X�g���N�^
	Player();
	~Player();
	bool initAnim(void);		// ��Ұ��݊Ǘ�
private:
	void SetMove(const GameCtrl &controller, weekListObj objList);

	bool DeathPrc(void);			// �֐���
	int speed;
	DIR dir;
	DIR_TBL_ARRAY keyIdTbl;		// �ړ�����
	DIR_TBL_PTR PosTbl;			// �|�C���^�𒼐ڊi�[
	DIR_TBL_ARRAY SpeedTbl;		// �ړ����x
	DIR_TBL_DIR DirTbl;			// �ړ�����
	// MAP_MOVE_TBL mapMoveTbl;	// �ړ�����,�ړ��\�I�u�W�F�N�g�Ȃ�true��Ԃ����A�C�e�����Q����ǉ������Ƃ��Ɏg��
};

