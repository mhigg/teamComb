#include <DxLib.h>
#include "GameCtrl.h"


GameCtrl::GameCtrl()
{
}


GameCtrl::~GameCtrl()
{
}

const KEY_ARY & GameCtrl::GetCtrl(KEY_TYPE type) const
{
	if (type == KEY_TYPE_NOW)
	{
		return keyData;
	}

	return keyDataOld;
}

const INPUT_ARY & GameCtrl::GetInputState(KEY_TYPE type) const
{
	if (type == KEY_TYPE_NOW)
	{
		return inputState;
	}

	return inputStateOld;
}

bool GameCtrl::UpDate(void)
{
	keyDataOld = keyData;
	GetHitKeyStateAll(&keyData[0]);
	
	GetJoypadXInputState(DX_INPUT_PAD1, &padData);

	inputStateOld = inputState;
	// �ړ��֘A
	inputState[XINPUT_DOWN] = (padData.ThumbLY > 20000) | padData.Buttons[XINPUT_BUTTON_DPAD_DOWN] | keyData[KEY_INPUT_DOWN];
	inputState[XINPUT_LEFT] = (padData.ThumbLX < -20000) | padData.Buttons[XINPUT_BUTTON_DPAD_LEFT];
	inputState[XINPUT_RIGHT] = (padData.ThumbLX > 20000) | padData.Buttons[XINPUT_BUTTON_DPAD_RIGHT];
	inputState[XINPUT_UP] = (padData.ThumbLY < -20000) | padData.Buttons[XINPUT_BUTTON_DPAD_UP];

	// ����݊֘A
	inputState[XINPUT_ATT] = padData.Buttons[XINPUT_BUTTON_B];
	inputState[XINPUT_MAP] = padData.Buttons[XINPUT_BUTTON_X];

	// ���͂�/�ޯ��(LB/RB)
	inputState[XINPUT_GET_LB] = padData.Buttons[XINPUT_BUTTON_LEFT_SHOULDER];
	inputState[XINPUT_RUN_RB] = padData.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER];

	// ���̑�(�ƭ�,�߰�ނȂ�)
	inputState[XINPUT_START] = padData.Buttons[XINPUT_BUTTON_START];
	inputState[XINPUT_PAUSE] = padData.Buttons[XINPUT_BUTTON_BACK];

	return true;
}
