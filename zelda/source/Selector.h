#pragma once
#include <array>
#include "Obj.h"
#include "Player.h"

enum CHARA_TYPE {
	CHARA_MAFIA,
	CHARA_GIRL,
	CHARA_OTHER,
	CHARA_OTHER2,
	CHARA_MAX
};

#define lpSelector Selector::GetInstance()

using STR_CHR_IMG = std::array<std::string, CHARA_MAX>;

class Selector :
	public Obj
{
public:
	Selector();
	Selector(PL_NUMBER plNum, VECTOR2 setUpPos, VECTOR2 drawOffset);
	~Selector();

	bool CheckObjType(OBJ_TYPE type);
	void Draw(void);

	CHARA_TYPE GetSelChara(void);	
private:
	void SetMove(const GameCtrl &controller, weakListObj objList);

	CHARA_TYPE selectChara;		// ��ڲ԰���̍��I�����Ă��鷬�
	STR_CHR_IMG standImgTbl;	// �I��������ڲ԰�̉摜
	STR_CHR_IMG pNumImgTbl;		// ����ڲ԰�ڂ��̉摜
	
	std::string Image;
	PL_NUMBER plNum;
};

