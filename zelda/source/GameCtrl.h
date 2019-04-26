// ���۰װ(���ް��)�̓��͏����擾����

#pragma once
#include <array>
#include "INPUT_ID.h"

//�ʖ���`
using KEY_ARY = std::array<char, 256>;
using INPUT_ARY = std::array<bool, static_cast<int>(INPUT_ID::MAX)>;

#define INPUT_DOWN	static_cast<int>(INPUT_ID::DOWN)
#define INPUT_LEFT	static_cast<int>(INPUT_ID::LEFT)
#define INPUT_RIGHT static_cast<int>(INPUT_ID::RIGHT)
#define INPUT_UP	static_cast<int>(INPUT_ID::UP)
#define INPUT_ACT_B static_cast<int>(INPUT_ID::ACT_B)
#define INPUT_ACT_X	static_cast<int>(INPUT_ID::ACT_X)
#define INPUT_GET_LB static_cast<int>(INPUT_ID::GET_LB)
#define INPUT_RUN_RB static_cast<int>(INPUT_ID::RUN_RB)
#define INPUT_START static_cast<int>(INPUT_ID::START)
#define INPUT_PAUSE static_cast<int>(INPUT_ID::PAUSE)


enum KEY_TYPE
{
	KEY_TYPE_NOW,	//���̷݂����
	KEY_TYPE_OLD,	//1�ڰёO�̏��
	KEY_TYPE_MAX
};

class GameCtrl
{
public:
	GameCtrl();
	~GameCtrl();
	const KEY_ARY &GetCtrl(KEY_TYPE type) const;	//�����擾�p�֐�
	const INPUT_ARY &GetInputState(KEY_TYPE type) const;	// �ް��߯�ނƷ��ް�ނ̏��擾
	bool UpDate(void);		//���̉�����Ԃ��擾,�X�V����

private:
	KEY_ARY keyData;	//���݂̉������
	KEY_ARY keyDataOld;	//1�ڰёO�̉������

	XINPUT_STATE padData;	// ���݂̹ް��߯�ޏ��
	int padDataOld;			// 1�ڰёO�̹ް��߯�ޏ��

	INPUT_ARY inputState;	// ���ް�ނ��߯�ނ̉������ true�Ȃ牟����Ă�����
	INPUT_ARY inputStateOld;
};

