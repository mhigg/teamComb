#pragma once
#include <list>
#include <array>
#include "Obj.h"
#include "ClassObj.h"

class EditScene :
	public BaseScene
{
public:
	EditScene();
	~EditScene();
	uniqueBase Update(						// �X�V
		uniqueBase own,					// ���݂̼��
		const GameCtrl &controler		// ���擾
	);
	bool menuFlag;							// �ƭ���ʂ̐^�U
private:
	sharedListObj objList;					// ������߲���
	int Init(void);							// �ݽ�׸��ƂȂ�
	bool EditDraw(void);					// �`��
};

