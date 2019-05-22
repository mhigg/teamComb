#pragma once
#include <array>
#include "VECTOR2.h"
#include "Obj.h"
#include "MapCtrl.h"
#include "ScoreBoard.h"
#include "GameCtrl.h"


enum PL_NUMBER {
	PL_1,
	PL_2,
	PL_3,
	PL_4,
	PL_MAX
};

struct State {
	int Power;
	int Guard;
	int Inv;
};

constexpr int PL_DEF_SPEED = 2;
constexpr int PL_DASH_SPEED = 4;
using UP_TIME = std::array < int, 2 >;


class Player :
	public Obj
{
public:
	Player(PL_NUMBER plNum, VECTOR2 setUpPos, VECTOR2 drawOffset);	// �����t���ݽ�׸��
	Player();
	~Player();
	bool initAnim(void);		// ��Ұ��݊Ǘ�
private:
	void PlInit(void);
	void SetMove(const GameCtrl &controller, weakListObj objList);
	bool CheckObjType(OBJ_TYPE type);
	bool DeathPrc(void);			// �֐���
	void GetItem(void);				// ���ю擾

// ---------- ��ڲ԰�̏�Ԋ֐� ------------
	void Stop(const GameCtrl & controller);			// ��~���
	void Move(const GameCtrl & controller);			// �����^������
	void Attack(const GameCtrl & controller);		// �U����
	void Damage(const GameCtrl & controller);		// ��Ұ�ގ�


	int speed;
	VECTOR2 startPos;				// ���Ēn�_(ؽ�߰ݗp)
	unsigned int NotFlag;
	State state;

	int score;
	int life;
	int invTime;				// inv���Z�p
	int damaCnt;				// ��Ұ�ނ��󂯂Ă���̶���
	std::array<int,SCORE_DATA::DATA_MAX> param;

// ---------- ð��ٔz�� ------------
	UP_TIME	upTime;				// �X�e�[�^�X(�U��,�h��)�㏸����
	DIR_TBL_ARY keyIdTbl;		// �ړ�����
	DIR_TBL_PTR PosTbl;			// �߲���𒼐ڊi�[
	DIR_TBL_A2D SpeedTbl;		// �ړ����x
	DIR_TBL_DIR DirTbl;			// �ړ�����
	MAP_MOVE_TBL mapMoveTbl;	// �ړ�����,�ړ��\��޼ު�ĂȂ�true��Ԃ������т��Q����ǉ������Ƃ��Ɏg��

	bool afterKeyFlag;			// key�̌���͂�D�悳�����׸�
	PL_NUMBER plNum;

	void (Player::*_updater)(const GameCtrl & controller);		// ��Ԋ֐��߲��
};

