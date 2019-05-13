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
	FOUND,			// ����
	ATT,				// �U��
	RETREAT,		// ����
	DEATH,			// ���S
	MAX
};

// enemy�̍s��
enum class ENEMY_BEHAVIOR
{
	DO_NOTHING,	// �������Ȃ�
	MOVE,				// �ړ�
	ATT,					// �U��
	MAX
};

// enemy��player��T������Ƃ��Ɏg��
struct SearchParam
{
	float ExploreDistance;		// �T������
	float ExploreAngle;			// �T���p�x
	float SignDistance;			// �C�z�������鋗��
};

struct EnemyData
{
	std::string fileName;
	VECTOR2	divSize;
	VECTOR2	divCnt;
	ENEMY		name;
};

constexpr auto ENEMY_SPEED = 3;
constexpr auto ENEMY__DASH_SPEED = 6;

using PRIORITY_ARRAY = std::array<int, static_cast<int>(ENEMY_BEHAVIOR::MAX)>;
using PRIORITY_TBL_ARRAY = std::array<PRIORITY_ARRAY, static_cast<int>(ENEMY_STATE::MAX)>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(	std::string fileName, 
				VECTOR2	divSize,
				VECTOR2 divCnt,
				int Enum, 
				VECTOR2 setUpPos, 
				VECTOR2 drawOffset	);
	~Enemy();

	bool CheckDeath(void);							// ���S����,����ł��Ȃ����false��Ԃ�
	bool CheckObjType(OBJ_TYPE type);		// �w�肵���l�Ɠ����^��������true��Ԃ�
	virtual const OBJ_TYPE& GetObjType(void)const;
	void SetDeathFlag(bool deathFlag);
private:
	void SetMove(const GameCtrl &controller, weakListObj objList);

	ENEMY_STATE state;							// ���
	ENEMY_BEHAVIOR nowBehavior;		// ���݂̍s��
	EnemyData data;								// �G�̏��

	int faintCnt;				// ���ݶ���
	int timeCnt;				// �o�ߎ��Ԃ̶���
	bool oppFlag;				// �ړ����]�׸�
	int behaviorCnt;			// �s�����̶���
	int speed;					// �G�̈ړ����x
	DIR dir;						// �G�̌���

	DIR_TBL_ARY keyIdTbl;				// �ړ�����
	DIR_TBL_PTR PosTbl;					// �߲���𒼐ڊi�[
	DIR_TBL_A2D SpeedTbl;			// �ړ����x
	DIR_TBL_DIR DirTbl;					// �ړ�����
	MAP_MOVE_TBL mapMoveTbl;	// �ړ�����,�ړ��\��޼ު�ĂȂ�true��Ԃ������т��Q����ǉ������Ƃ��Ɏg��
protected:
	bool deathFlag;			// ���S�׸�
};

