#pragma once
#include<array>
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

// enemy�̏��
enum class ENEMY_STATE
{
	NORMAL,		// �ʏ�
	TRA,				// �ǐ�
	RETREAT,		// ����
	DEATH,			// ���S
	MAX
};

// enemy�̍s��
enum class ENEM_ACT
{
	DO_NOTHING,	// �������Ȃ�
	MOVE,				// �ړ�
	TRA,					// �ǐ�
	MAX
};

// enemy��player��T������Ƃ��Ɏg��
struct SearchParam
{
	// float ExploreDistance;		// �T������
	float ExploreAngle;				// �T���p�x
	float SignDistance;				// �C�z�������鋗��
};

constexpr auto ENEMY_SPEED = 5;
constexpr auto ENEMY_DASH_SPEED = 6;
constexpr auto ENEMY_LIM = 201;

using PRIORITY_ARRAY = std::array<int, static_cast<int>(ENEM_ACT::MAX)>;
using PRIORITY_TBL_ARRAY = std::array<PRIORITY_ARRAY, static_cast<int>(ENEMY_STATE::MAX)>;

using  ENEMY_POS = std::array<VECTOR2, 2>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(	
		int enemyNum, 
		VECTOR2 setUpPos, 
		VECTOR2 drawOffset,
		int enCnt	);
	~Enemy();

	bool CheckDeath(void);							// ���S����,����ł��Ȃ����false��Ԃ�
	bool CheckObjType(OBJ_TYPE type);		// �w�肵���l�Ɠ����^��������true��Ԃ�
	const OBJ_TYPE& GetObjType(void)const;
	void SetDeathFlag(bool deathFlag);
private:
	void SetMove(const GameCtrl &controller, weakListObj objList);
	bool initAnim(void);

	ENEMY_STATE state;		// ���
	ENEMY name;				// �G�̎��
	ENEM_ACT action;			// �G�̍s��

	int faintCnt;					// ���ݶ���
	int timeCnt;					// �o�ߎ��Ԃ̶���
	bool oppFlag;					// �ړ����]�׸�
	int behaviorCnt;				// �s�����̶���
	int enCnt;						// �������g�����ް
	int speed;						// �G�̈ړ����x
	VECTOR2 addCnt;			// �G�̈ړ��ʊǗ�
	DIR dir;							// �G�̌���

	DIR_TBL_ARY keyIdTbl;				// �ړ�����
	DIR_TBL_PTR PosTbl;					// �߲���𒼐ڊi�[
	DIR_TBL_A2D SpeedTbl;			// �ړ����x
	MAP_MOVE_TBL mapMoveTbl;	// �ړ�����,�ړ��\��޼ު�ĂȂ�true��Ԃ������т��Q����ǉ������Ƃ��Ɏg��

	bool flag;

protected:
	bool deathFlag;			// ���S�׸�
};

