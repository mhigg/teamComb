#pragma once
#include <array>
#include "Obj.h"
#include "VECTOR2.h"
#include "MapCtrl.h"
#include "Player.h"

constexpr int MOVE_SPEED = 40;

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

	DIR_TBL_ARY dirTable;		// ���͂������̕����@speedTable�ƕ��������킹��
	DIR_TBL_ARY scrTable;		// ��۰ٗp
	DIR_TBL_ARY speedTable;		// ��ۯ��̈ړ���߰�� dirTable�ƕ��������킹��

	// �����������Ƃ��̏���
	/*
		��󷰉������ɶ��ق̏㉺���E�ړ����s������
		��󷰒��������Ɉړ����x���㏸���Ă�������
		Ctrl���������ɔz�u������ۯ���ύX���鏈��
		Space���������ɑI�����Ă�����ۯ���z�u���鏈��
	*/
	void SetMove(const GameCtrl &controller, weakListObj objList);
	bool MoveDec(VECTOR2 temp, VECTOR2 &dec);		// �����������̊֐���
	bool CheckObjType(OBJ_TYPE type);
};

