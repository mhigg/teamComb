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

enum PL_NUMBER {
	PL_1,
	PL_2,
	PL_3,
	PL_4,
	PL_MAX
};

constexpr int PL_DEF_SPEED = 5;
constexpr int PL_DASH_SPEED = 10;

using DIR_TBL_ARY = std::array<int, DIR_MAX>;
using DIR_TBL_A2D = std::array<int[2], DIR_MAX>;
using DIR_TBL_PTR = std::array<int*[TBL_MAX], DIR_MAX>;
using DIR_TBL_DIR = std::array<DIR[DIR_TBL_MAX], DIR_MAX>;
using MAP_MOVE_TBL = std::array<bool, static_cast<int>(MAP_ID::MAX)>; // �����т��Q����ǉ������Ƃ��Ɏg��


class Player :
	public Obj
{
public:
	Player(PL_NUMBER plNum, VECTOR2 setUpPos, VECTOR2 drawOffset);	// �����t���ݽ�׸��
	Player();
	~Player();
	bool initAnim(void);		// ��Ұ��݊Ǘ�
private:
	void SetMove(const GameCtrl &controller, weakListObj objList);
	bool CheckObjType(OBJ_TYPE type);
	bool DeathPrc(void);			// �֐���
	void GetItem(void);				// ���ю擾

	int offset;	// �l�w20�x���i�[����
	int speed;
	DIR dir;
	int life;
	VECTOR2 startPos;				// ���Ēn�_(ؽ�߰ݗp)
	unsigned int NotFlag;

// ---------- ð��ٔz�� ------------
	DIR_TBL_ARY keyIdTbl;		// �ړ�����
	DIR_TBL_PTR PosTbl;			// �߲���𒼐ڊi�[
	DIR_TBL_A2D SpeedTbl;		// �ړ����x
	DIR_TBL_DIR DirTbl;			// �ړ�����
	MAP_MOVE_TBL mapMoveTbl;	// �ړ�����,�ړ��\��޼ު�ĂȂ�true��Ԃ������т��Q����ǉ������Ƃ��Ɏg��

	bool afterKeyFlag;			// key�̌���͂�D�悳�����׸�
	PL_NUMBER plNum;
};

