#pragma once
#include <list>
#include <array>
#include "BaseScene.h"
#include "Obj.h"
#include "ClassObj.h"

class EditScene :
	public BaseScene
{
public:
	EditScene();
	~EditScene();
	uniqueBase UpDate(						// 更新
		uniqueBase own,					// 現在のｼｰﾝ
		const GameCtrl &controller		// ｷｰ取得
	);
private:
	sharedListObj objList;					// ｼｪｱﾄﾞﾎﾟｲﾝﾀｰ
	int Init(void);							// ｺﾝｽﾄﾗｸﾀとなる
	bool EditDraw(void);					// 描画
};

