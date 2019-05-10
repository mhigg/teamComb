#pragma once
#include <string>
#include <map>
#include "VECTOR2.h"
#include "classObj.h"

enum ANIM_TBL {
	ANIM_TBL_START_ID,		// ��Ұ��݂̊J�n
	ANIM_TBL_FRAME,			// ��Ұ��݂̺ϐ�
	ANIM_TBL_INV,			// �ς��Ƃ̊Ԋu
	ANIM_TBL_LOOP,			// ٰ�߂��邩�ǂ���
	ANIM_TBL_MAX
};

enum DIR {
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_MAX
};

enum OBJ_TYPE {
	OBJ_PLAYER,
	OBJ_ENEMY,
	OBJ_BOMB,
	OBJ_EDIT_CURSOR,
	OBJ_MAX
};

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

class GameCtrl;

using DIR_TBL_ARY = std::array<int, DIR_MAX>;
using DIR_TBL_A2D = std::array<int[2], DIR_MAX>;
using DIR_TBL_PTR = std::array<int*[TBL_MAX], DIR_MAX>;
using DIR_TBL_DIR = std::array<DIR[DIR_TBL_MAX], DIR_MAX>;
using MAP_MOVE_TBL = std::array<bool, static_cast<int>(MAP_ID::MAX)>; // �����т��Q����ǉ������Ƃ��Ɏg��

class Obj
{
public:
	Obj();

	// �󂯎����drawOffset�������̎���drawOffset�ɓ����
	Obj(VECTOR2 drawOffset);
	virtual ~Obj();

	bool Init(
		std::string fileName,		// �摜��̧�ٖ�
		VECTOR2 divSize,			// ��������
		VECTOR2 divCnt				// �������̏�����
	);
	bool Init(
		std::string fileName,		// �摜��̧�ٖ�
		VECTOR2 divSize,			// ��������
		VECTOR2 divCnt,				// �������̏�����
		VECTOR2 pos					// ���W
	);

	virtual bool initAnim(void) { return true; };	// ��Ұ��݂̐ݒ�@AddAnim�֐��ɒl��ݒ肷��
	void UpDate(
		const GameCtrl &controller,	// ���X�V
		weakListObj objList			// ���۰װ���̂��߲����n��
	);
	virtual bool CheckDeath(void) { return false; };	// ���S����@��{����łȂ����false
	virtual bool CheckObjType(OBJ_TYPE type) = 0;		// �w�肵���l�Ɠ����^��������true��Ԃ�
	virtual void Draw(void);		// �`��
	void Draw(unsigned int id);		// ID�w��`��
	const VECTOR2 &GetPos(void);	// ���W�擾�֐�

	bool AddAnim(
		std::string animName,		// ��Ұ��݂̖��O
		int id_x,					// ����
		int id_y,					// ���
		int frame,					// ���ϐ�
		int inv,					// ��Ұ���1�ς��Ƃ̊Ԋu
		bool loop					// ��Ұ��݂�ٰ�ߗL��(true:����,false:�Ȃ�)
	);

	// �������O�̱�Ұ��݂�Ă����Ƃ���true
	// ���݂��Ȃ���Ұ��ݖ���Ă����Ƃ���false
	// �ʂ̱�Ұ��݂�Ă����Ƃ��ͱ�Ұ��ݖ����Đݒ肵�A�ϐ��̶��Ă�animEndFlag��ؾ�Ă���
	bool SetAnim(std::string animName);

	std::string GetAnim(void);	// ���݂̱�Ұ��ݖ����擾����

private:
	virtual void SetMove(const GameCtrl &controller, weakListObj objList) = 0;

	std::string animName;	// �\�������Ұ��ݖ�
	std::map<std::string, int[ANIM_TBL_MAX]> animTable;	// ��Ұ��݂̐ݒ��ۑ�����z��

protected:
	void SetPos(VECTOR2 pos);	// ���W��ݒ�

	VECTOR2 pos;				// �\��������W
	const VECTOR2 drawOffset;	// �`��̾��
	VECTOR2 scrollOffset;		// ��۰قɂ��̾��

	std::string imageName;	// �\������摜��̧�ٖ�
	VECTOR2 divSize;		// �摜�̕�������
	VECTOR2 divCnt;			// �摜�̕�����

	OBJ_TYPE objType;		// ��޼ު�Ă̎��

	DIR dir;				// ��޼ު�Ă̌����Ă������

	unsigned int animCnt;	// ��Ұ��̶݂���
	bool animEndFlag;		// ��Ұ��݂̍ŏI�ϓ��B�׸�

	bool visible;
};