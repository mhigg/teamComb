#pragma once
#include <array>
#include <vector>
#include "Obj.h"
#include "MAP_ID.h"

// enemy�̎��(���O�Ȃ�)
enum class ENEMY
{
	ENEMY_1,
	ENEMY_2,
	ENEMY_3,
	ENEMY_4,
	ENEMY_MAX
};

// enemy�̍s��
enum class ENEM_ACT
{
	WAIT,				// �������Ȃ�
	MOVE,				// �ړ�
	TRA,					// �ǐ�
	SERCH,				// �T��
	CONST_MOVE,	// ���̏ꏊ��p�j
	BACK,				// ������ɖ߂�
	DAMAGE,			//	��Ұ��
	MAX
};

constexpr auto ENEMY_SPEED = 2;
constexpr auto ENEMY_DASH_SPEED = 6;
constexpr auto ENEMY_LIM = 201;
constexpr auto PLAYER_DIS_X = 9;
constexpr auto PLAYER_DIS_Y = 5;
constexpr auto SERCH_LIM = 400;

using PRIORITY_ARRAY = std::array<int, static_cast<int>(ENEM_ACT::MAX)>;
using PASS_FLAG = std::array<bool, DIR_MAX * 3>;
using PASS_ARR_ALL = std::array<VECTOR2, DIR_MAX * 3>;
using DIR_PASS = std::array<DIR[3], DIR_MAX>;
using CHECK_ARR = std::vector<double>;

using OBJ_POS = std::array<VECTOR2, 4>;
using OBJ_INT = std::array<int, 4>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(	
		int enemyNum, 
		VECTOR2 setUpPos,
		VECTOR2 drawOffset,
		int enCnt
	);
	~Enemy();

	bool CheckDeath(void);								// ���S����,����ł��Ȃ����false��Ԃ�
	bool CheckObjType(OBJ_TYPE type);			// �w�肵���l�Ɠ����^��������true��Ԃ�
	const OBJ_TYPE& GetObjType(void)const;	// ��޼ު�Ė���Ԃ�
	void SetDeathFlag(bool deathFlag);				// ����ł����true��Ă���
private:
	// �ڰт��ƂɎ��s�������
	void SetMove(const GameCtrl &controller, weakListObj objList);
	// ���ޔ���
	VECTOR2 sidePos(VECTOR2 pos, DIR dir, int speed, int sideNum);
	bool initAnim(void);
	// ��а�̏�����
	void EnInit(void);
	// �s�x���������K�v�Ȃ���	
	void CheckFree(void);
	// ���z�߽�̒T��
	VECTOR2 Distance(DIR tmpDir,VECTOR2 pos);
	// �߂���ڲ԰�̌���
	int SerchPlayer(bool flag);

	// ---------- ��а�̏�Ԋ֐� ------------
	void Move(const GameCtrl & controller);			// �����
	void Track(const GameCtrl & controller);			// �ǐ�
	void Serch(const GameCtrl & controller);			// �T��
	void ConstMove(const GameCtrl & controller);	// �w��s��
	void Damage(const GameCtrl & controller);		// ��Ұ�ގ�
	void Escape(const GameCtrl & controller);		// ������
	void Wait(const GameCtrl & controller);			// �ҋ@
	void Back(const GameCtrl & controller);			// �A��

	//--------------�G�̎�ނ���-----------------
	void GateKeeper(void);		// ���
	void Undette(void);			// ���ޯ�
	void Zombie(void);				// �����

	ENEMY name;					// �G�̎��
	ENEM_ACT action;				// �G�̍s��
	int life;								// �e��ׂ�ײ�
	// ------------------�߂���ڲ԰�̌����p--------------------------
	OBJ_POS plPos;				// ��ڲ԰�̍��W
	OBJ_INT enPos;				// �G�̍��W
	VECTOR2 firstPos;			// �������p
	int nearP;						// �߂���ڲ԰

	int timeCnt;				// �o�ߎ��Ԃ̶���
	bool oppFlag;				// �ړ����]�׸�
	int behaviorCnt;			// �s�����̶���
	int enCnt;					// �������g�����ް
	int speed;					// �G�̈ړ����x
	int actNum[3];			// �s���\���ٰ�
	int actRoot;				// ���s����ٰ�
	int movePos;				// �ړ���	
	int actCnt;					// �������̑҂��ڰ�
	int deathCnt;				// �_�ŗp�̶���

	CHECK_ARR comPos;			// �D��x�̔�r�p�z��(����)
	VECTOR2 addCnt;				// �G�̈ړ��ʊǗ�
	DIR dir;								// �G�̌���
	PASS_FLAG passFlag;			// �ړ��ł����߽
	int comFlag;						// �D��z��Ɋi�[����Ă��鐔
	PASS_ARR_ALL checkPos;	// ����_
	DIR_PASS dirOpp;				// ��������

	VECTOR2 rootPos;			// �ڕW�_
	DIR_PASS rootPass;		// �A�����

	DIR_TBL_ARY keyIdTbl;				// �ړ�����
	DIR_TBL_PTR PosTbl;					// �߲���𒼐ڊi�[
	DIR_TBL_A2D SpeedTbl;			// �ړ����x
	MAP_MOVE_TBL mapMoveTbl;	// �ړ�����,�ړ��\��޼ު�ĂȂ�true��Ԃ������т��Q����ǉ������Ƃ��Ɏg��
	void (Enemy::*_updater)(const GameCtrl & controller);		// ��Ԋ֐��߲��
protected:
	bool deathFlag;			// ���S�׸�
};

