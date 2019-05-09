#pragma once
#include "Obj.h"

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
	FOUND,		// ����
	ATT,		// �U��
	RETREAT,	// ����
	DEATH,		// ���S
	MAX
};

// enemy�̍s��
enum class ENEMY_BEHAVIOR
{
	DO_NOTHING,	// �������Ȃ�
	MOVE,		// �ړ�
	ATT,		// �U��
	MAX
};

// enemy��player��T������Ƃ��Ɏg��
struct SearchParam
{
	float ExploreDistance;	// �T������
	float ExploreAngle;		// �T���p�x
	float SignDistance;		// �C�z�������鋗��
};

// �ړ����̕���������
struct MoveParam
{
	bool down;
	bool left;
	bool right;
	bool up;
};

struct EnemyData
{
	std::string fileName;
	VECTOR2		divSize;
	VECTOR2		divCnt;
	ENEMY		name;
};

using PRIORITY_ARRAY = std::array<int, static_cast<int>(ENEMY_BEHAVIOR::MAX)>;
using PRIORITY_TBL_ARRAY = std::array<PRIORITY_ARRAY, static_cast<int>(ENEMY_STATE::MAX)>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyData data, VECTOR2 setUpPos, VECTOR2 drawOffset);
	~Enemy();

	bool CheckDeath(void);				// ���S����,����ł��Ȃ����false��Ԃ�
	bool CheckObjType(OBJ_TYPE type);	// �w�肵���l�Ɠ����^��������true��Ԃ�
	virtual const OBJ_TYPE& GetObjType(void)const;
	void SetDeathFlag(bool deathFlag);
private:



	ENEMY_STATE state;				// ���
	ENEMY_BEHAVIOR nowBehavior;		// ���݂̍s��
	MoveParam moveParam;			// �ړ����̕���������
	int faintCnt;			// ���ݶ���
	int timeCnt;			// �o�ߎ��Ԃ̶���
	bool oppFlag;			// �ړ����]�׸�
	int behaviorCnt;		// �s�����̶���

protected:
	bool deathFlag;			// ���S�׸�
};

