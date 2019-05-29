#pragma once
#include <array>
#include "BaseScene.h"
#include "ClassObj.h"

constexpr auto CHARA_NUM = 4;

using SELECT_POS = std::array< VECTOR2, CHARA_NUM >;

class SelectScene :
	public BaseScene
{
public:
	SelectScene();
	~SelectScene();
	uniqueBase UpDate(						// �X�V
		uniqueBase own,					// ���݂̼��
		const GameCtrl &controller		// ���擾
	);
private:
	void SelectDraw(void);		// �`��
	int Init(void);				// ������

	SELECT_POS selectPos;		// ��ڲ԰���̗����G�ʒu
	int selectMode;				// �I��Ӱ��
	int backChange;				// �w�i�؂�ւ��̎���

	sharedListObj objList;
};

