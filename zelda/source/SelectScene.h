#pragma once
#include "BaseScene.h"

constexpr auto CHARA_NUM = 4;

using SELECT_CHARA = std::array< bool, CHARA_NUM >;

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
	void SelectDraw(void);
	int Init(void);

	SELECT_CHARA selectChara;
	int nowChara;	// ���I�����Ă���L����
};

