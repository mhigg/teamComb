#pragma once
#include <list>
#include <array>
#include "Obj.h"
#include "ClassObj.h"

class EditScene :
	public BaseScene
{
public:
	EditScene();
	~EditScene();
	uniqueBase Update(						// 更新
		uniqueBase own,					// 現在のｼｰﾝ
		const GameCtrl &controler		// ｷｰ取得
	);
	bool menuFlag;							// ﾒﾆｭｰ画面の真偽
private:
	sharedListObj objList;					// ｼｪｱﾄﾞﾎﾟｲﾝﾀｰ
	int Init(void);							// ｺﾝｽﾄﾗｸﾀとなる
	bool EditDraw(void);					// 描画
};

