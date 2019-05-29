#pragma once
#include <array>
#include "Obj.h"
#include "ScoreBoard.h"
#include "MapCtrl.h"
#include "GameCtrl.h"
#include "VECTOR2.h"

enum PL_NUMBER {
	PL_1,
	PL_2,
	PL_3,
	PL_4,
	PL_MAX
};

enum SCORE_DATA
{
	DATA_SCORE,
	DATA_LIFE,
	DATA_POWER,
	DATA_GUARD,
	DATA_INV,
	DATA_BONUS,
	DATA_MAX
};

struct State {
	int Power;	// �U����
	int Guard;	// �h���
	int Inv;	// ���G����
};

constexpr int PL_DEF_SPEED = 2;					// �����Ă���Ƃ��̈ړ����x
constexpr int PL_DASH_SPEED = 4;				// �����Ă���Ƃ��̈ړ����x
constexpr unsigned int PL_RESTART_CNT = 120U;	// ؽ�݂߰܂ł̎���
constexpr int PL_LIFE_MAX = 6;					// ��ڲ԰�̗̑͏��

using UP_TIME = std::array < int, 2 >;
using ACT_ARR = std::array<VECTOR2, DIR_MAX>;


class Player :
	public Obj
{
public:
	Player(PL_NUMBER plNum, VECTOR2 setUpPos, VECTOR2 drawOffset);	// �����t���ݽ�׸��
	Player();
	~Player();
	bool initAnim(void);						// ��Ұ��݊Ǘ�
	void SetData(SCORE_DATA data, int val);		// ��ڲ԰�̎����ް��̏W�v
	void StateDraw(void);						// �ð���̕`��
private:
	void PlInit(void);		// ؽ�݂߰̍ۂɂ��K�v�ȏ����������܂Ƃ�
	void SetMove(const GameCtrl &controller, weakListObj objList);
	bool CheckObjType(OBJ_TYPE type);
	void GetItem(void);		// ���ю擾
	void Draw(void);
	VECTOR2 sidePos			// ���ޔ���
	(
		VECTOR2 pos,		// ���݈ʒu���W
		DIR dir,			// �����Ă������
		int speed,			// �ړ���߰��
		int sideNum
	);

// ---------- ��ڲ԰�̏�Ԋ֐� ------------
	void Stop(const GameCtrl & controller);			// ��~���
	void Move(const GameCtrl & controller);			// �����^������
	void Attack(const GameCtrl & controller);		// �U����
	void Damage(const GameCtrl & controller);		// ��Ұ�ގ�

	int speed;
	VECTOR2 startPos;			// ���Ēn�_(ؽ�߰ݗp)
	ACT_ARR actAdd;				// �����蔻�蕪�̉��Z���Wð���
	unsigned int NotFlag;		// �g�����s��
	State state;				// ��ڲ԰�̍U����/�h���/���G����

	int score;					// �������
	int life;					// ��ڲ԰�̗̑�
	int invTime;				// inv���Z�p
	int damageCnt;				// ��Ұ�ނ��󂯂Ă���̶���
	bool damageFlag;			// ��Ұ�ނ������Ă����׸�
	int deathInv;				// ���S���|�ꂽ�܂܂̎���
	int bonus;					// �ްŽ
	int oldScore;				// ���O�̽��
	int additionTime;			// ���Z����܂ł̎���
	unsigned int reStartCnt;
	std::array<int,SCORE_DATA::DATA_MAX> param;

// ---------- ð��ٔz�� ------------
	UP_TIME	upTime;				// �X�e�[�^�X(�U��,�h��)�㏸����
	DIR_TBL_ARY keyIdTbl;		// �ړ�����
	DIR_TBL_PTR PosTbl;			// �߲���𒼐ڊi�[
	DIR_TBL_A2D SpeedTbl;		// �ړ����x
	DIR_TBL_DIR DirTbl;			// �ړ�����
	MAP_MOVE_TBL mapMoveTbl;	// �ړ�����,�ړ��\��޼ު�ĂȂ�true��Ԃ������т��Q����ǉ������Ƃ��Ɏg��

	bool afterKeyFlag;			// key�̌���͂�D�悳�����׸�
	PL_NUMBER plNum;			// ���������Ԗڂ���ڲ԰���̔ԍ�
	int randomBonus;			// �����_���Ƀ{�[�i�X�A�C�e�������߂�
	int numTemp;
	int digit;

	void (Player::*_updater)(const GameCtrl & controller);		// ��Ԋ֐��߲��
};

