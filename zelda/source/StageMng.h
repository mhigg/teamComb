// ｵﾌﾞｼﾞｪｸﾄのｲﾝｽﾀﾝｽ・ﾏｯﾌﾟのﾛｰﾄﾞなど、MapCtrlをもとにﾏｯﾌﾟ情報を管理・利用する

#pragma once
#include <memory>

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

	// ﾏｯﾌﾟﾛｰﾄﾞ

private:
	StageMng();
	~StageMng();

	bool Init(void);

	std::unique_ptr<MapCtrl> mapCtrl;
};

