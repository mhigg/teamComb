#pragma once
#include "BaseScene.h"
#include "Selector.h"

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

	int plNumber;								// ��ڲ԰��
	std::array<CHARA_TYPE, 4> plSelChara;		// ��ڲ԰�̑I�񂾷��
	BONUS_POINT bonusPoint;						// ��ڲ԰�����ްŽ�l����
	RESULT_SCORE resultScore;					// �ްŽ���Z��̍ŏI���
	SCORE_RUNK scoreRunk;						// ��ڲ԰����
	int resultTemp;								// ���(�`��p)
	int waitFlag;								// �҂��׸�
};

