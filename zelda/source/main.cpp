using namespace std;
#include <stdlib.h>
#include <Dxlib.h>	// DxLibײ���؂��g�p����
#include "EffekseerForDXLib.h"
#include "SceneMng.h"

// ---------- WinMain�֐�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SceneMng::GetInstance().Run();

	Effkseer_End();
	DxLib_End();	// DXײ���؂̏I������
	return 0;
}