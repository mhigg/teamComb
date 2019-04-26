// ｵﾌﾞｼﾞｪｸﾄのｲﾝｽﾀﾝｽ・ﾏｯﾌﾟのﾛｰﾄﾞなど、MapCtrlをもとにﾏｯﾌﾟ情報を管理・利用する

#pragma once
#include <memory>
#include <vector>
#include "MapCtrl.h"
#include "MAP_ID.h"
#include "VECTOR2.h"

#define lpStageMng StageMng::GetInstance()


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
	void MapLoad(void);

	const VECTOR2& GetChipSize(void);		// ChipSizeの取得
	const VECTOR2& GetStageSize(void);		// StageSizeの取得
	std::vector<MAP_ID> GetMap(void);

private:
	StageMng();
	~StageMng();

	bool Init(void);

//	std::unique_ptr<MapCtrl> mapCtrl;

	std::vector<MAP_ID> mapData;  // ｽﾃｰｼﾞﾏｯﾌﾟﾃﾞｰﾀ
	VECTOR2 stageSize;	// ｽﾃｰｼﾞｻｲｽﾞ
	VECTOR2 chipSize;	// ゲームサイズ
};

