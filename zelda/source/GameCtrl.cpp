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

const int & GameCtrl::GetPadData(KEY_TYPE type) const
{
	if (type == KEY_TYPE_NOW)
	{
		return padData;
	}

	return padDataOld;
}

bool GameCtrl::UpDate(void)
{
	keyDataOld = keyData;
	GetHitKeyStateAll(&keyData[0]);

	padDataOld = padData;
	padData = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	return true;
}
