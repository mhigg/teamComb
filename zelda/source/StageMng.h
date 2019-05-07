// ｵﾌﾞｼﾞｪｸﾄのｲﾝｽﾀﾝｽ・ﾏｯﾌﾟのﾛｰﾄﾞなど、MapCtrlをもとにﾏｯﾌﾟ情報を管理・利用する

#pragma once
#include <memory>
#include <vector>
#include "MapCtrl.h"
#include "MAP_ID.h"
#include "VECTOR2.h"

#define lpStageMng StageMng::GetInstance()

constexpr int GAME_AREA_SIZE_X = 800;		// ﾏｯﾌﾟ全体のｻｲｽﾞ
constexpr int GAME_AREA_SIZE_Y = 600;

class StageMng
{
public:
	static StageMng & GetInstance(void)
	{
		static StageMng s_instance;
		return s_instance;
	}

	// ﾏｯﾌﾟｾｰﾌﾞ←ｴﾃﾞｨｯﾄ
	void MapSave(void);

	// ﾏｯﾌﾟﾛｰﾄﾞ
	void MapLoad(sharedListObj objList, bool editFlag);

	const VECTOR2& GetChipSize(void);		// ChipSizeの取得
	const VECTOR2& GetStageSize(void);		// StageSizeの取得
	const VECTOR2& GetDrawOffset(void);		// drawOffsetの取得


private:
	StageMng();
	~StageMng();

	bool Init(void);


	std::vector<MAP_ID*> mapData;  // ｽﾃｰｼﾞﾏｯﾌﾟﾃﾞｰﾀ
	std::vector<MAP_ID> mapData_Base;
	VECTOR2 stageSize;	// ｽﾃｰｼﾞｻｲｽﾞ
	VECTOR2 chipSize;	// 1ﾏｽのｻｲｽﾞ
	VECTOR2 drawOffset;
};

