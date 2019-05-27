#pragma once
#include "BaseScene.h"

constexpr int PLAYER_MAX = 4;

using BONUS_POINT = std::array< int, PLAYER_MAX >;

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

	BONUS_POINT bonusPoint;		// ��ڲ԰�����ްŽ�l����
};

