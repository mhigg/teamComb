#pragma once
#include "BaseScene.h"
class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	uniqueBase UpDate(						// �X�V
		uniqueBase own,					// ���݂̼��
		const GameCtrl &controller		// ���擾
	);
private:
	void TitleDraw(void);	// �`��
	int Init(void);			// ������
};

