#pragma once
#include "BaseScene.h"
class ResultScene :
	public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	uniqueBase UpDate(						// �X�V
		uniqueBase own,					// ���݂̼��
		const GameCtrl &controller		// ���擾
	);
private:
	void ResultDraw(void);		// �`��
	int Init(void);				// ������ 
};

