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
	// ˆÚ“®ŠÖ˜A
	inputState[XINPUT_DOWN] = (padData.ThumbLY > 20000) | padData.Buttons[XINPUT_BUTTON_DPAD_DOWN];
	inputState[XINPUT_LEFT] = (padData.ThumbLX < -20000) | padData.Buttons[XINPUT_BUTTON_DPAD_LEFT];
	inputState[XINPUT_RIGHT] = (padData.ThumbLX > 20000) | padData.Buttons[XINPUT_BUTTON_DPAD_RIGHT];
	inputState[XINPUT_UP] = (padData.ThumbLY < -20000) | padData.Buttons[XINPUT_BUTTON_DPAD_UP];

	// ±¸¼®ÝŠÖ˜A
	inputState[XINPUT_ACT_B] = 0;
	inputState[XINPUT_ACT_X] = 0;
	// •¨’Í‚Ý/ÀÞ¯¼­(LB/RB)
	inputState[XINPUT_GET_LB] = 0;
	inputState[XINPUT_RUN_RB] = 0;

	// ‚»‚Ì‘¼(ÒÆ­°,Îß°½Þ‚È‚Ç)
	inputState[XINPUT_START] = 0;
	inputState[XINPUT_PAUSE] = 0;

	return true;
}
