#pragma once
#include <list>
#include <array>
#include "BaseScene.h"
#include "Obj.h"
#include "ClassObj.h"

class EditScene :
	public BaseScene
{
public:
	EditScene();
	~EditScene();
	uniqueBase UpDate(						// �X�V
		uniqueBase own,					// ���݂̼��
		const GameCtrl &controller		// ���擾
	);
private:
	sharedListObj objList;					// ������߲���
	int Init(void);							// �ݽ�׸��ƂȂ�
	bool EditDraw(void);					// �`��
};

