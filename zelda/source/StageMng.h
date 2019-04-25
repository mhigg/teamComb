// ｵﾌﾞｼﾞｪｸﾄのｲﾝｽﾀﾝｽ・ﾏｯﾌﾟのﾛｰﾄﾞなど、MapCtrlをもとにﾏｯﾌﾟ情報を管理・利用する

#pragma once
#include <memory>
#include "VECTOR2.h"

#define lpStageMng StageMng::GetInstance()

class MapCtrl;

class StageMng
{
public:
	static StageMng & GetInstance(void)
	{
		static StageMng s_instance;
		return s_instance;
	}

	// ﾏｯﾌﾟｾｰﾌﾞ
	void MapSave(void);

	// ﾏｯﾌﾟﾛｰﾄﾞ
	void MapLoad(void);

	// ﾏｯﾌﾟ描画
	void MapDraw(void);

private:
	StageMng();
	~StageMng();

	bool Init(void);

	std::unique_ptr<MapCtrl> mapCtrl;

	int lineColor;		// ﾗｲﾝｶﾗｰ
	VECTOR2 stageSize;	// ｽﾃｰｼﾞｻｲｽﾞ
};

