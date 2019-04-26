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
	inputState[INPUT_DOWN] = (padData.ThumbLY > 20000) | padData.Buttons[XINPUT_BUTTON_DPAD_DOWN];
	inputState[INPUT_LEFT] = (padData.ThumbLX < -20000) | padData.Buttons[XINPUT_BUTTON_DPAD_LEFT];
	inputState[INPUT_RIGHT] = (padData.ThumbLX > 20000) | padData.Buttons[XINPUT_BUTTON_DPAD_RIGHT];
	inputState[INPUT_UP] = (padData.ThumbLY < -20000) | padData.Buttons[XINPUT_BUTTON_DPAD_UP];

	// ±¸¼®ÝŠÖ˜A
	inputState[INPUT_ACT_B] = 0;
	inputState[INPUT_ACT_X] = 0;
	// •¨’Í‚Ý/ÀÞ¯¼­(LB/RB)
	inputState[INPUT_GET_LB] = 0;
	inputState[INPUT_RUN_RB] = 0;

	// ‚»‚Ì‘¼(ÒÆ­°,Îß°½Þ‚È‚Ç)
	inputState[INPUT_START] = 0;
	inputState[INPUT_PAUSE] = 0;

	return true;
}
