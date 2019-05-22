#pragma once
#include "BaseScene.h"
#include <array>

constexpr auto CHARA_NUM = 4;

using SELECT_CHARA = std::array< int, CHARA_NUM >;
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

	SELECT_CHARA selectChara;	// �v���C���[���̍��I�����Ă���L����
	SELECT_POS selectPos;		// �v���C���[���̗����G�ʒu
};

