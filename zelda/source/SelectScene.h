#pragma once
#include "BaseScene.h"
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
};

