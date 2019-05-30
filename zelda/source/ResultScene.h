#pragma once
#include "BaseScene.h"

constexpr int PLAYER_MAX = 4;

enum SCORE_RUNK{
	RUNK1,
	RUNK2,
	RUNK3,
	RUNK4,
	RUNK_MAX
};

using BONUS_POINT = std::array< int, PLAYER_MAX >;
using RESULT_SCORE = std::array< int, PLAYER_MAX >;

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
	RESULT_SCORE resultScore;	// �ްŽ���Z��̍ŏI���
	int plNumber;				// ��ڲ԰��
	int resultTemp;				// ���(�`��p)
};

