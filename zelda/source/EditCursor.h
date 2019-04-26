#pragma once
#include <array>
#include "Obj.h"
#include "VECTOR2.h"
#include "MapCtrl.h"
#include "Player.h"

#define MOVE_SPEED (20)

//class SceneMng;
class EditCursor :
	public Obj
{
public:
	EditCursor();						// MAP_ID,inputFlam,keyGetRng������������
	EditCursor(VECTOR2 drawOffset);		// MAP_ID,inputFlam,keyGetRng,drawOffset������������
	~EditCursor();
	void Draw(void);					// ���ق̓_�ŏ��� SetDrawBlendMode�֐��g�p

private:
	MAP_ID id;		// ϯ�߂������ް���ID

	int keyGetRng;	// ����ڰѐ��@���𗣂����珉����
	int inputFlam;	// ���������Ă����ڰѐ��@�����ĂȂ��Ƃ���۸ر

	DIR_TBL_ARR dirTable;		// ���͂������̕����@speedTable�ƕ��������킹��
	DIR_TBL_ARR speedTable;		// ��ۯ��̈ړ���߰�� dirTable�ƕ��������킹��

	// �����������Ƃ��̏���
	/*
		��󷰉������ɶ��ق̏㉺���E�ړ����s������
		��󷰒��������Ɉړ����x���㏸���Ă�������
		Ctrl���������ɔz�u������ۯ���ύX���鏈��
		Space���������ɑI�����Ă�����ۯ���z�u���鏈��
	*/
	void SetMove(const GameCtrl &controller, weakListObj objList);
	bool CheckObjType(OBJ_TYPE type);
};

