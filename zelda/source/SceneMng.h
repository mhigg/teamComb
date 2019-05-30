// �ްѓ��̼�ݑJ�ڂ��Ǘ�����E�ް�ٰ��

#pragma once
#include <memory>
#include "BaseScene.h"
#include "VECTOR2.h"

constexpr int SCREEN_SIZE_X = 1600;
constexpr int SCREEN_SIZE_Y = 960;

constexpr int PL_SCREEN_SIZE_X = 800;
constexpr int PL_SCREEN_SIZE_Y = 480;

#define lpSceneMng SceneMng::GetInstance()

class GameCtrl;

class SceneMng
{
public:
	static SceneMng & GetInstance(void)
	{
		static SceneMng s_instance;
		return s_instance;
	}

	void Run(void);								// �ް�ٰ��
	VECTOR2 GetDrawOffset(void);				// �`��̾�Ă��擾
	void SetDrawOffset(VECTOR2 drawOffset);
	VECTOR2 GetPlayScreen(void);				// 4��������1��ʂ̻��ނ��擾
	int GetFram(void);							// �ްыN����������ڰѐ����擾

private:
	SceneMng();
	~SceneMng();
	bool Init(void);

	VECTOR2 drawOffset;
	int framCnt;

	uniqueBase activeScene;
	std::unique_ptr<GameCtrl> gameCtrl;
};

