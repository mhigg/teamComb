// ���۰װ(���ް��)�̓��͏����擾����

#pragma once
#include <DxLib.h>
#include <array>
#include <vector>
#include "VECTOR2.h"
#include "INPUT_ID.h"

//�ʖ���`
using KEY_ARY = std::array<char, 256>;
using INPUT_ARY = std::array<bool, static_cast<int>(INPUT_ID::MAX)>;

#define XINPUT_DOWN	static_cast<int>(INPUT_ID::DOWN)		// ��
#define XINPUT_LEFT	static_cast<int>(INPUT_ID::LEFT)		// ��
#define XINPUT_RIGHT static_cast<int>(INPUT_ID::RIGHT)		// �E
#define XINPUT_UP	static_cast<int>(INPUT_ID::UP)			// ��
#define XINPUT_ATT static_cast<int>(INPUT_ID::ATT)			// �U��
#define XINPUT_MAP	static_cast<int>(INPUT_ID::MAP)			// ϯ�ߕ\��
#define XINPUT_GET_LB static_cast<int>(INPUT_ID::GET_LB)	// ����͂�,����u��,�ړ�key + ����͂�ł��Ԃ�LBkey������ = ���𓊂���
#define XINPUT_RUN_RB static_cast<int>(INPUT_ID::RUN_RB)	// �ޯ��
#define XINPUT_START static_cast<int>(INPUT_ID::START)		// ����
#define XINPUT_PAUSE static_cast<int>(INPUT_ID::PAUSE)		// �߰��


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
	const std::vector<INPUT_ARY> &GetInputState(KEY_TYPE type) const;	// �ް��߯�ނƷ��ް�ނ̏��擾
	bool UpDate(void);		//���̉�����Ԃ��擾,�X�V����

private:
	KEY_ARY keyData;	//���݂̉������
	KEY_ARY keyDataOld;	//1�ڰёO�̉������

	std::vector<XINPUT_STATE> padData;	// ���݂̹ް��߯�ޏ��
	int padDataOld;			// 1�ڰёO�̹ް��߯�ޏ��

	std::array<unsigned int, 4> padTbl;

	std::vector<INPUT_ARY> inputState;	// ���ް�ނ��߯�ނ̉������ true�Ȃ牟����Ă�����
	std::vector<INPUT_ARY> inputStateOld;
};

