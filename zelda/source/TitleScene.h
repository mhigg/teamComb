#pragma once
#include "BaseScene.h"
class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	uniqueBase UpDate(						// XV
		uniqueBase own,					// Œ»İ‚Ì¼°İ
		const GameCtrl &controller		// ·°æ“¾
	);
private:
	void TitleDraw(void);	// •`‰æ
	int Init(void);			// ‰Šú‰»
};

